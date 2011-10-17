/*
 * BandEntry.h
 *
 *  Created on: Jul 19, 2011
 *      Author: caioviel
 */

#ifndef BANDENTRY_H_
#define BANDENTRY_H_

#include <string>
using namespace std;

namespace tvmonitor {

class BandEntry {
public:
	BandEntry();
	BandEntry(BandEntry &bandEntry);
	BandEntry(string id, int freqKHz);
	virtual ~BandEntry();
    string getBandId() const;
    int getFrequency() const;
    void setBandId(string bandId);
    void setFrequency(int freqKHz);

private:
	int freqKHz;
	string bandId;
};

} /* namespace tvmonitor */
#endif /* BANDENTRY_H_ */
