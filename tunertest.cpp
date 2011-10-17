#include <cstdlib>
#include <iostream>
using namespace std;

#include "include/TVTunerInputV4L2.h"
using namespace tvmonitor;

int main(int argc, char** argv) {
	VideoInput* input;

	try {
		input = new TVTunerInputV4L2("/dev/video0", TunerSettings::BRAZILIAN_ANALOG_TV);

		cout << "Frequência atual é: " << input->getTunerFrequency() << endl;

	    if (argc > 1) {
	    	int freq = atoi(argv[1]);
	    	cout << "Vamos tentar setar a frequência: " << freq << endl;
	    	input->setTunerFrequency(freq);
	    	cout << "Frequência atual: " << input->getTunerFrequency() << endl;
	    	cout << "Está apresentando algo: " << input->isFrequencyPresent() << endl;
	    }

	    usleep(1000000);

	} catch(TVMonitorException e) {
		cerr << e.what() << endl;
		return 1;
	}

	return 0;
}
