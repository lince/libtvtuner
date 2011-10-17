/*
 * TunerSettings.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#include "../include/TunerSettings.h"

#include <cstdlib>
#include <iostream>
using namespace std;

#include <cpputil/Functions.h>
using namespace cpputil;

namespace tvmonitor {
TunerSettings::TunerSettings() {
	bands = new vector<BandEntry*>();

	this->setNorm(UNSETED);

	firstChannel = -1;
	lastChannel = -1;
	numChannels = 0;
}

TunerSettings::TunerSettings(Norm _norm) {
	bands = new vector<BandEntry*>();

	this->setNorm(_norm);

	firstChannel = -1;
	lastChannel = -1;
	numChannels = 0;
}

TunerSettings::TunerSettings(Norm norm, int deviceId) {
	bands = new vector<BandEntry*>();

	this->setNorm(norm);

	firstChannel = -1;
	lastChannel = -1;
	numChannels = 0;
}

TunerSettings::TunerSettings(Norm norm, string devicePath) {
	bands = new vector<BandEntry*>();

	this->setNorm(norm);

	firstChannel = -1;
	lastChannel = -1;
	numChannels = 0;
}

TunerSettings::~TunerSettings() {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* bandEntry = *it;
		delete bandEntry;
		it++;
	}
	delete bands;
}

int TunerSettings::getFirstChannel() const {
	return firstChannel;
}

int TunerSettings::getLastChannel() const {
	return lastChannel;
}

int TunerSettings::getNumChannels() const {
	return numChannels;
}

void TunerSettings::setFirstChannel(int firstChannel) {
	this->firstChannel = firstChannel;
}

void TunerSettings::setLastChannel(int lastChannel) {
	this->lastChannel = lastChannel;
}

void TunerSettings::setNumChannels(int numChannels) {
	this->numChannels = numChannels;
}

string TunerSettings::normToStr(Norm norm) {

	switch (norm) {
		case NTSC: return "NTCS";
		case PAL: return "PAL";
		case SECAM: return "SECAM";
		case PAL_NC: return "PAL-NC";
		case PAL_M: return "PAL-M";
		case PAL_N: return "PAL-N";
		case NTSC_JP: return "NTSC-JP";
		case PAL_60: return "PAL-60";
		default: return "";
	}

}

TunerSettings* TunerSettings::BRAZILIAN_ANALOG_TV = createBrazilianAnalogTV();


TunerSettings* TunerSettings::createBrazilianAnalogTV() {
	TunerSettings* aux = new TunerSettings(PAL_M);
	aux->addBand(new BandEntry("1",    73250));
	aux->addBand(new BandEntry("2",    55250));
	aux->addBand(new BandEntry("3",    61250));
	aux->addBand(new BandEntry("4",    67250));
	aux->addBand(new BandEntry("5",    77250));
	aux->addBand(new BandEntry("6",    83250));
	aux->addBand(new BandEntry("7",    175250));
	aux->addBand(new BandEntry("8",    181250));
	aux->addBand(new BandEntry("9",    187250));
	aux->addBand(new BandEntry("10",    193250));
	aux->addBand(new BandEntry("11",    199250));
	aux->addBand(new BandEntry("12",    205250));
	aux->addBand(new BandEntry("13",    211250));
	aux->addBand(new BandEntry("14",    471250));
	aux->addBand(new BandEntry("15",    471250 + 600*1));
	aux->addBand(new BandEntry("16",    471250 + 600*2));
	aux->addBand(new BandEntry("17",    471250 + 600*3));
	aux->addBand(new BandEntry("18",    471250 + 600*4));
	aux->addBand(new BandEntry("19",    471250 + 600*5));
	aux->addBand(new BandEntry("20",    471250 + 600*6));
	aux->addBand(new BandEntry("21",    471250 + 600*7));
	aux->addBand(new BandEntry("22",    471250 + 600*8));
	aux->addBand(new BandEntry("23",    471250 + 600*9));
	aux->addBand(new BandEntry("24",    471250 + 600*10));
	aux->addBand(new BandEntry("25",    471250 + 600*11));
	aux->addBand(new BandEntry("26",    471250 + 600*12));
	aux->addBand(new BandEntry("27",    471250 + 600*13));
	aux->addBand(new BandEntry("28",    471250 + 600*14));
	aux->addBand(new BandEntry("29",    471250 + 600*15));
	aux->addBand(new BandEntry("30",    471250 + 600*16));
	aux->addBand(new BandEntry("31",    471250 + 600*17));
	aux->addBand(new BandEntry("32",    471250 + 600*18));
	aux->addBand(new BandEntry("33",    471250 + 600*19));
	aux->addBand(new BandEntry("34",    471250 + 600*20));
	aux->addBand(new BandEntry("35",    471250 + 600*21));
	aux->addBand(new BandEntry("36",    471250 + 600*22));
	aux->addBand(new BandEntry("37",    471250 + 600*23));
	aux->addBand(new BandEntry("38",    471250 + 600*24));
	aux->addBand(new BandEntry("39",    471250 + 600*25));
	aux->addBand(new BandEntry("40",    471250 + 600*26));
	aux->addBand(new BandEntry("41",    471250 + 600*27));
	aux->addBand(new BandEntry("42",    471250 + 600*28));
	aux->addBand(new BandEntry("43",    471250 + 600*29));
	aux->addBand(new BandEntry("44",    471250 + 600*30));
	aux->addBand(new BandEntry("45",    471250 + 600*31));
	aux->addBand(new BandEntry("46",    471250 + 600*32));
	aux->addBand(new BandEntry("47",    471250 + 600*33));
	aux->addBand(new BandEntry("48",    471250 + 600*34));
	aux->addBand(new BandEntry("49",    471250 + 600*35));
	aux->addBand(new BandEntry("50",    471250 + 600*36));
	aux->addBand(new BandEntry("51",    471250 + 600*37));
	aux->addBand(new BandEntry("52",    471250 + 600*38));
	aux->addBand(new BandEntry("53",    471250 + 600*39));
	aux->addBand(new BandEntry("54",    471250 + 600*40));
	aux->addBand(new BandEntry("55",    471250 + 600*41));
	aux->addBand(new BandEntry("56",    471250 + 600*42));
	aux->addBand(new BandEntry("57",    471250 + 600*43));
	aux->addBand(new BandEntry("58",    471250 + 600*44));
	aux->addBand(new BandEntry("59",    471250 + 600*45));
	aux->addBand(new BandEntry("60",    471250 + 600*46));
	aux->addBand(new BandEntry("61",    471250 + 600*47));
	aux->addBand(new BandEntry("62",    471250 + 600*48));
	aux->addBand(new BandEntry("63",    471250 + 600*49));
	aux->addBand(new BandEntry("64",    471250 + 600*50));
	aux->addBand(new BandEntry("65",    471250 + 600*51));
	aux->addBand(new BandEntry("66",    471250 + 600*52));
	aux->addBand(new BandEntry("67",    471250 + 600*53));
	aux->addBand(new BandEntry("68",    471250 + 600*54));
	aux->addBand(new BandEntry("69",    471250 + 600*55));
	aux->addBand(new BandEntry("70",    471250 + 600*56));
	aux->addBand(new BandEntry("71",    471250 + 600*57));
	aux->addBand(new BandEntry("72",    471250 + 600*58));
	aux->addBand(new BandEntry("73",    471250 + 600*59));
	aux->addBand(new BandEntry("74",    471250 + 600*60));
	aux->addBand(new BandEntry("75",    471250 + 600*61));
	aux->addBand(new BandEntry("76",    471250 + 600*62));
	aux->addBand(new BandEntry("77",    471250 + 600*63));
	aux->addBand(new BandEntry("78",    471250 + 600*64));
	aux->addBand(new BandEntry("79",    471250 + 600*65));
	aux->addBand(new BandEntry("80",    471250 + 600*66));
	aux->addBand(new BandEntry("81",    471250 + 600*67));
	aux->addBand(new BandEntry("82",    471250 + 600*68));
	aux->addBand(new BandEntry("83",    471250 + 600*69));
	aux->setFirstChannel(1);
	aux->setLastChannel(83);
	aux->setNumChannels(83);
	return aux;
}

int TunerSettings::getHeight() const {
	return height;
}

Norm TunerSettings::getNorm() {
	return norm;
}

int TunerSettings::getWidth() const {
	return width;
}

void TunerSettings::setHeight(int height) {
	this->height = height;
}

void TunerSettings::setNorm(Norm _norm) {
	this->norm = _norm;
	if (norm == UNSETED) {
		height = -1;
		width = -1;
	} else if( norm == NTSC || norm == NTSC_JP || norm == PAL_M || norm == PAL_60 ) {
		height = 480;
		width = 720;
	} else {
		height = 576;
		width = 768;
	}
}

void TunerSettings::addBand(BandEntry *bandEntry) {
	bands->push_back(bandEntry);
}

BandEntry *TunerSettings::removeBandById(string bandId) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getBandId() == bandId) {
			bands->erase(it);
			return entry;
		}
		it++;
	}
	return NULL;
}

BandEntry *TunerSettings::removeBandByFrequency(int freqKHz) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getFrequency() == freqKHz) {
			bands->erase(it);
			return entry;
		}
		it++;
	}
	return NULL;
}

vector<BandEntry*> *TunerSettings::getBands() {
	vector<BandEntry*>* copyBands = new vector<BandEntry*>();
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		copyBands->push_back(entry);
	}
	return copyBands;
}

bool TunerSettings::hasBand(string bandId) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getBandId() == bandId) {
			return true;
		}
		it++;
	}
	return false;
}

bool TunerSettings::hasBand(int freqKHz) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getFrequency() == freqKHz) {
			return true;
		}
		it++;
	}
	return false;
}

BandEntry *TunerSettings::getBand(string bandId) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getBandId() == bandId) {
			return new BandEntry(*entry);
		}
		it++;
	}
	return NULL;
}

BandEntry *TunerSettings::getBand(int freqKHz) {
	vector<BandEntry*>::iterator it;
	it = bands->begin();
	while (it != bands->end()) {
		BandEntry* entry = *it;
		if (entry->getFrequency() == freqKHz) {
			return new BandEntry(*entry);
		}
		it++;
	}
	return NULL;
}

void TunerSettings::setWidth(int width) {
	this->width = width;
}



} /* namespace tvmonitor */
