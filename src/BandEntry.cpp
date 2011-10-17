/*
 * BandEntry.cpp
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#include "../include/BandEntry.h"

namespace tvmonitor {

BandEntry::BandEntry() {
	freqKHz = -1;
	bandId = "";
}

BandEntry::BandEntry(BandEntry &bandEntry) {
	freqKHz = bandEntry.freqKHz;
	bandId = bandEntry.bandId;
}

BandEntry::BandEntry(string id, int freqKHz) {
	this->freqKHz = freqKHz;
	this->bandId = bandId;
}

BandEntry::~BandEntry() {
	// TODO Auto-generated destructor stub
}

string BandEntry::getBandId() const {
	return bandId;
}

int BandEntry::getFrequency() const {
	return freqKHz;
}

void BandEntry::setBandId(string bandId) {
	this->bandId = bandId;
}

void BandEntry::setFrequency(int freqKHz) {
	this->freqKHz = freqKHz;
}

} /* namespace tvmonitor */
