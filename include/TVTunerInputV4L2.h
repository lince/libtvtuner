/*
 * TVTunerInputV4L2.h
 *
 *  Created on: Jul 6, 2011
 *      Author: caioviel
 */

#ifndef TVTUNERINPUTV4L2_H_
#define TVTUNERINPUTV4L2_H_

#include "VideoInput.h"

#include <cpputil/logger/Logger.h>
using namespace cpputil::logger;

#include <cstring>
using namespace std;

namespace tvmonitor {

class TVTunerInputV4L2: public VideoInput, Loggable {
public:
	TVTunerInputV4L2(int deviceId, TunerSettings* tuner);
	TVTunerInputV4L2(string devicePath, TunerSettings* tuner);

	virtual ~TVTunerInputV4L2();

	virtual void setInputNum(int inputnum);

	virtual void setTunerFrequency(int freqKHz);
	virtual int getTunerFrequency();
	virtual bool isFrequencyPresent();

	virtual Norm getNorm();

	virtual int getVideoHeight();

	virtual int getVideoWidth();

private:
	void openDevice();

	void findAndSetTuner();


private:
	Logger* logger;
	TunerSettings* tunerSettings;

	string devicePath;

	int deviceFd;
	string drivername;
	string shortdriver;

	int numinputs;
	int curinput;
	string inputname;

	int width;
	int height;
	int maxwidth;
	Norm norm;
	int volume;
	int amode;

	bool isbttv;
	bool isv4l2;
	bool isuyvy;

	int curframe;
	int numframes;

	bool hasAudio;
	int audiomode;
	bool hasChangeMuted;
	bool isUserMuted;
	bool isHardwareMuted;

	bool hasTuner;
	int numtuners;
	int tunerId;
	bool isTunerLow;

	int curTunerState;
	int signalRecoverWait;
	int signalAcquireWait;

	int framesSinceStart;

	bool isStreaming;
	bool haveMmap;
};

} /* namespace tvmonitor */
#endif /* TVTUNERINPUTV4L2_H_ */
