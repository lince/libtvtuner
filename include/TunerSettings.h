/*
 * TunerSettings.h
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#ifndef TUNERSETTINGS_H_
#define TUNERSETTINGS_H_

#include <string>
#include <vector>
using namespace std;

#include "BandEntry.h"

namespace tvmonitor {

enum Norm {
	UNSETED=-1,
	NTSC,
	PAL,
	SECAM,
	PAL_NC,
	PAL_M,
	PAL_N,
	NTSC_JP,
	PAL_60
};

class TunerSettings {

public:
	static TunerSettings* BRAZILIAN_ANALOG_TV;

public:
	static string normToStr(Norm norm);

public:
	TunerSettings();
	TunerSettings(Norm norm);
	TunerSettings(Norm norm, int deviceId);
	TunerSettings(Norm norm, string devicePath);

	virtual ~TunerSettings();
	void addBand(BandEntry* bandEntry);
	BandEntry* removeBandById(string bandId);
	BandEntry* removeBandByFrequency(int freqKHz);
	vector<BandEntry*>* getBands();
	bool hasBand(string bandId);
	bool hasBand(int freqKHz);
	BandEntry* getBand(string bandId);
	BandEntry* getBand(int freqKHz);
    int getHeight() const;
    Norm getNorm();
    int getWidth() const;
    void setHeight(int height);
    void setNorm(Norm norm);
    void setWidth(int width);
    int getFirstChannel() const;
    int getLastChannel() const;
    int getNumChannels() const;
    void setFirstChannel(int firstChannel);
    void setLastChannel(int lastChannel);
    void setNumChannels(int numChannels);

private:
    static TunerSettings* createBrazilianAnalogTV();


private:
	int height;
	int width;
	Norm norm;
	int numChannels;
	int firstChannel;
	int lastChannel;
	vector<BandEntry*>* bands;
};

} /* namespace tvmonitor */
#endif /* TUNERSETTINGS_H_ */
