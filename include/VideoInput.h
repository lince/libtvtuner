/*
 * VideoInput.h
 *
 *  Created on: Jul 6, 2011
 *      Author: caioviel
 */

#ifndef VIDEOINPUT_H_
#define VIDEOINPUT_H_

#include <cstring>
#include <cstdlib>

using namespace std;

#include "TVMonitorException.h"
#include "TunerSettings.h"

namespace tvmonitor {

class VideoInput {
public:
	VideoInput() : finetune(0) {

	}

	virtual ~VideoInput() {

	}

	virtual void setInputNum(int inputnum) = 0;

	virtual void setTunerFrequency(int freqKHz) = 0;

	virtual int getTunerFrequency() = 0;

	virtual void incFinetune() {
		if (finetune != 50) {
			finetune++;
		}
		setTunerFrequency( getTunerFrequency() );
	}

	virtual void decFinetune() {
		if (finetune != -50) {
			finetune--;
		}
		setTunerFrequency( getTunerFrequency() );
	}

	virtual int getFineTune() {
		return finetune;
	}

	virtual bool isFrequencyPresent() = 0;

	virtual Norm getNorm() = 0;

	virtual int getVideoHeight() = 0;

	virtual int getVideoWidth() = 0;

protected:
	int finetune;

};

} /* namespace tvmonitor */
#endif /* VIDEOINPUT_H_ */
