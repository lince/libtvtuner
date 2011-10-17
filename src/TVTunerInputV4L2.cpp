/*
 * TVTunerInputV4L2.cpp
 *
 *  Created on: Jul 6, 2011
 *      Author: caioviel
 */

#include "../include/TVTunerInputV4L2.h"
#include "../include/TVMonitorException.h"

#include <cpputil/Functions.h>
using namespace cpputil;

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <linux/videodev2.h>
#include <cerrno>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>

using namespace std;

namespace tvmonitor {

static v4l2_std_id mapToV4l2Norm(Norm norm);

TVTunerInputV4L2::TVTunerInputV4L2(int deviceId, TunerSettings* tuner) {
	if (deviceId < 0) {
		//TODO: Throw InvalidArgumen Exception
	}
	string str = "/dev/video";
	str += Functions::numberToString(deviceId);
	TVTunerInputV4L2(str, tuner);
}

TVTunerInputV4L2::TVTunerInputV4L2(string devicePath, TunerSettings* tuner) {
	logger = Logger::getInstance();
	REGISTER(logger, "tvmonitor::TVTunerInputV4L2");

	TRACE(logger, "Begin TVTunerInputV4L2(string devicePath, TunerSettings* tuner)");
	this->tunerSettings = tuner;
	this->devicePath = devicePath;
	string aux = "Device connected: " + devicePath;
	INFO(logger, aux);
	this->norm = tunerSettings->getNorm();

	curframe = 0;
	//norm = norm;
	//volume = volume;
	amode = 0;
	//height = videoinput_get_norm_height( norm );
	//width = 0;
	//maxwidth = 0;
	//cur_tuner_state = TUNER_STATE_NO_SIGNAL;

	hasTuner = false;
	isTunerLow = false;
	numtuners = 0;
	tunerId = 0;

	isv4l2 = false;
	isbttv = false;
	isuyvy = false;

	signalRecoverWait = 0;
	signalAcquireWait = 0;
	hasChangeMuted = true;
	isUserMuted = false;
	isHardwareMuted = true;
	hasAudio = true;
	audiomode = 0;
	curinput = 0;
	haveMmap = false;
	isStreaming = false;

	inputname = "";
	drivername = "";
	shortdriver = "";

	/* Let's try open the device and get tuner configs */
	openDevice();
}

TVTunerInputV4L2::~TVTunerInputV4L2() {
	// TODO Auto-generated destructor stub
	TRACE(logger, "Destructor");
}

void TVTunerInputV4L2::openDevice() {
	TRACE(logger, "Begin openDevice()");
	int ret;
	struct v4l2_input videoInput;

	/* First, open the device. */
	ret = open(devicePath.c_str(), O_RDWR);
	if( ret < 0 ) {
		string str = "Cannot open capture device "
				+ this->devicePath + ": " + strerror( errno );

		TVMonitorException e("TVTunerInputV4L2", "openDevice()", str);
		throw e;
	}
	deviceFd  = ret;

	/**
	 * Next, ask for its capabilities.  This will also confirm it's a V4L2
	 * device.
	 */
	struct v4l2_capability caps_v4l2;
	if( ioctl(deviceFd, VIDIOC_QUERYCAP, &caps_v4l2 ) < 0 ) {
		isv4l2 = false;
		TVMonitorException e("TVTunerInputV4L2", "openDevice()",
				"Not a Video4Linux 2 Device!");
		throw e;
	}

	isv4l2 = true;


	/**
	 * We have to enumerate all of the inputs just to know how many
	 * there are.
	 */
	struct v4l2_input in;
	numinputs = 0;
	in.index = numinputs;

	while( ioctl( deviceFd, VIDIOC_ENUMINPUT, &in ) >= 0 ) {
		numinputs++;
		in.index = numinputs;
	}

	if (numinputs <= 0) {
		TVMonitorException e("TVTunerInputV4L2", "openDevice()",
				"Cannot find a valid input.");
		throw e;
	}

	/* On initialization, set to input 0.  This is just to start things up. */
	setInputNum(0);


	/*    if( input->isv4l2 ) {
	        struct v4l2_requestbuffers req;

	 *
	 * Ask Video Device for Buffers

	        req.count = 4;
	        req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	        req.memory = V4L2_MEMORY_MMAP;

	        if( ioctl( input->grab_fd, VIDIOC_REQBUFS, &req ) < 0 ) {
	            cerr << "videoinput: Card failed to allocate capture buffers:"
	                     << strerror( errno ) << endl;
	            //sprintf( error_string, "%s: %s", input->shortdriver, strerror( errno ) );
	            close( input->grab_fd );
	            delete input;
	            return 0;
	        }
	        input->numframes = req.count;

	        if( input->numframes < 1 ) {
	            cerr << "videoinput: No capture buffers available from card." << endl;
	            close( input->grab_fd );
	            delete input;
	            return 0;
	        } else if( input->numframes > 4 ) {
	             If we got more frames than we asked for, limit to 4 for now.
	            if( vidin->verbose ) {
	                fprintf( stderr, "videoinput: Capture card provides %d buffers, but we only need 4.\n",
	                         vidin->numframes );
	            }
	        	input->numframes = 4;
	        }

	 *
	 * Query each buffer and map it to the video device

	        for( int i = 0; i < input->numframes; i++ ) {
	            struct v4l2_buffer *vidbuf = &(input->capbuffers[ i ].vidbuf);

	            vidbuf->index = i;
	            vidbuf->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	            vidbuf->memory = V4L2_MEMORY_MMAP;
	            if( ioctl( input->grab_fd, VIDIOC_QUERYBUF, vidbuf ) < 0 ) {
	                cerr << "videoinput: Can't get information about buffer "<< i << ":"
	                         << strerror( errno ) << endl;
	                close( input->grab_fd );
	                delete input;
	                return 0;
	            }

	            input->capbuffers[ i ].data = (char*) mmap( 0, vidbuf->length,
	                                                PROT_READ | PROT_WRITE,
	                                                MAP_SHARED, input->grab_fd,
	                                                vidbuf->m.offset );

	            if( input->capbuffers[ i ].data == MAP_FAILED ) {
	                cerr << "videoinput: Can't map buffer "<< i << ":"
	                         << strerror( errno ) << endl;
	                close( input->grab_fd );
	                delete input;
	                return 0;
	            }
	            input->capbuffers[ i ].length = vidbuf->length;
	        }
	        videoinput_free_all_frames( input );

	        videoinput_start_capture_v4l2( input );
	    }*/

}

void TVTunerInputV4L2::setInputNum(int inputnum) {
	TRACE(logger, "Begin setInputNum()");
	v4l2_std_id std;
	int index = inputnum;

	if( ioctl(deviceFd, VIDIOC_S_INPUT, &index ) < 0 ) {
		string str = "Card refuses to set its input: ";
		str += strerror( errno );
		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	}

	struct v4l2_input input;

	if( ioctl( deviceFd, VIDIOC_G_INPUT, &input.index ) < 0 ) {
		string str = "Driver won't tell us its input: ";
		str += strerror( errno );
		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	} else if( input.index != inputnum ) {
		string str = "Driver refuses to switch input: ";
		str += strerror( errno );

		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	}

	curinput = inputnum;

	if( ioctl( deviceFd, VIDIOC_ENUMINPUT, &input ) < 0 ) {
		string str = "Driver won't tell us input info: ";
		str += strerror( errno );

		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	}

	hasTuner = (input.type == V4L2_INPUT_TYPE_TUNER);
	tunerId = input.tuner;

	if( ioctl( deviceFd, VIDIOC_G_STD, &std ) < 0 ) {
		string str = "Driver won't tell us its norm: ";
		str += strerror( errno );

		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	}

	std = mapToV4l2Norm(norm);


	if( std == V4L2_STD_PAL ) {
		cout << "std == V4L2_STD_PAL " << endl;
		/*if( in->amode == VIDEOINPUT_PAL_DK_AUDIO ) {
			std = V4L2_STD_PAL_DK;
		} else if( in->amode == VIDEOINPUT_PAL_I_AUDIO ) {
			std = V4L2_STD_PAL_I;
		}*/
	}

	if( ioctl( deviceFd, VIDIOC_S_STD, &std ) < 0 ) {
		string str = "Driver refuses to set norm: ";
		str += strerror( errno );

		TVMonitorException e("TVTunerInputV4L2", "setInputNum()", str);
		throw e;
	}

	/* Once we've set the input, go look for a tuner. */
	findAndSetTuner();
}

void TVTunerInputV4L2::findAndSetTuner() {
	TRACE(logger, "Begin findAndSetTuner()");
    if( isv4l2 ) {
        struct v4l2_tuner tuner;

        tuner.index = tunerId;
        if( ioctl( deviceFd, VIDIOC_G_TUNER, &tuner ) < 0 ) {
           string str = "Can't get tuner info: ";
           str += strerror( errno );
           TVMonitorException e("TVTunerInputV4L2", "findAndSetTuner()", str);
           throw e;
        }

	   if (tuner.capability & V4L2_TUNER_CAP_LOW != 0) {
		   isTunerLow = true;
	   } else {
		   isTunerLow = false;
	   }
       hasTuner = true;
    }
}

void TVTunerInputV4L2::setTunerFrequency(int freqKHz) {
	TRACE(logger, "Begin setTunerFrequency()");
    unsigned long frequency = freqKHz;

    if( !hasTuner ) {
        TVMonitorException e("TVTunerInputV4L2",
        		"setTunerFrequency()", "Device has no tuner.");

        throw e;
    }
    if( frequency < 0 ) {
    	/* Ignore bogus frequencies. */
    	cerr << "Invalid frequency value : " << frequency << endl;
    	//TODO: throw IllegalParamException();
    	return;
    }

    frequency += (finetune*1000)/16;

    frequency *= 16;

    if( !isTunerLow ) {
    	frequency /= 1000; /* switch to MHz */
    }

    hasChangeMuted = 1;
    //mixer_mute( 1 );
    //videoinput_do_mute( vidin, vidin->user_muted || vidin->change_muted );
    //vidin->cur_tuner_state = TUNER_STATE_SIGNAL_DETECTED;
    //vidin->signal_acquire_wait = SIGNAL_ACQUIRE_DELAY;
    //vidin->signal_recover_wait = 0;

    if( isv4l2 ) {
    	struct v4l2_frequency freqinfo;
    	//int wasstreaming = vidin->is_streaming;

    	memset( &freqinfo, 0, sizeof( struct v4l2_frequency ) );
    	freqinfo.tuner = tunerId;
    	freqinfo.type = V4L2_TUNER_ANALOG_TV;
    	freqinfo.frequency = frequency;

    	//videoinput_stop_capture_v4l2( vidin );

    	//cout << "tuner is low: " << isTunerLow << endl;
    	//cout << "valor do freqinfo.frequency: " << freqinfo.frequency << endl;

    	if( ioctl( deviceFd, VIDIOC_S_FREQUENCY, &freqinfo ) < 0 ) {
            string str = "Tuner present, but our request to change frequency has failed: ";
            str += strerror( errno );
            TVMonitorException e("TVTunerInputV4L2", "setTunerFrequency()", str);
            throw e;
    	}
    	//if( wasstreaming ) {
    		//videoinput_free_all_frames( vidin );
    		//videoinput_start_capture_v4l2( vidin );
    	//}
    }
}

int TVTunerInputV4L2::getTunerFrequency() {
	TRACE(logger, "Begin getTunerFrequency()");
	unsigned long frequency;

    if( !hasTuner ) {
        TVMonitorException e("TVTunerInputV4L2",
        		"getTunerFrequency()", "Device has no tuner.");

        throw e;
    }

    if( isv4l2 ) {
    	struct v4l2_frequency freqinfo;

    	freqinfo.tuner = tunerId;
    	freqinfo.type = V4L2_TUNER_ANALOG_TV;

    	if( ioctl( deviceFd, VIDIOC_G_FREQUENCY, &freqinfo ) < 0 ) {
            string str = "Tuner refuses to tell us the current frequency: ";
            str += strerror( errno );
            TVMonitorException e("TVTunerInputV4L2", "getTunerFrequency()", str);
            throw e;
    	}
    	frequency = freqinfo.frequency;
    } else {
    	return 0;
    }

    if (!isTunerLow) {
    	frequency *= 1000;
    }
    return frequency / 16;
}

bool TVTunerInputV4L2::isFrequencyPresent() {
	TRACE(logger, "Begin isFrequencyPresent()");
    if( !hasTuner ) {
        if( isv4l2 ) {
            struct v4l2_tuner tuner;

            tuner.index = tunerId;
            if( ioctl( deviceFd, VIDIOC_G_TUNER, &tuner ) < 0 ) {
                string str = "Cannot detect signal from tuner: ";
                str += strerror( errno );
                TVMonitorException e("TVTunerInputV4L2", "isFrequencyPresent()", str);
                throw e;
            } else if( !tuner.signal ) {
                return 0;
            }
        }
    }
    return 1;
}

Norm TVTunerInputV4L2::getNorm() {
	return norm;
}

int TVTunerInputV4L2::getVideoHeight() {
	//TODO: verificar se o valor voltado pelo tuner conferem com a norm
	return tunerSettings->getHeight();
}

int TVTunerInputV4L2::getVideoWidth() {
	//TODO: verificar se o valor voltado pelo tuner conferem com a norm
	return tunerSettings->getWidth();
}

v4l2_std_id mapToV4l2Norm(Norm norm) {
    if( norm == NTSC ) {
        return V4L2_STD_NTSC_M;
    } else if( norm == PAL ) {
        return V4L2_STD_PAL;
    } else if( norm == SECAM ) {
        return V4L2_STD_SECAM;
    } else if( norm == PAL_NC ) {
        return V4L2_STD_PAL_Nc;
    } else if( norm == PAL_M ) {
        return V4L2_STD_PAL_M;
    } else if( norm == PAL_N ) {
        return V4L2_STD_PAL_N;
    } else if( norm == NTSC_JP ) {
        return V4L2_STD_NTSC_M_JP;
    } else if( norm == PAL_60 ) {
        return V4L2_STD_PAL_60;
    } else {
        return 0;
    }
}

}
 /* namespace tvmonitor */
