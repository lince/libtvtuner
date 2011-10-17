/*
 * TVMonitorException.h
 *
 *  Created on: Jul 8, 2011
 *      Author: caioviel
 */

#ifndef TVMONITOREXCEPTION_H_
#define TVMONITOREXCEPTION_H_

#include <exception>
#include <string>
using namespace std;

namespace tvmonitor {

class TVMonitorException : public exception {
private:
	string classStr, methodStr, errorMsg;

public:
	TVMonitorException(
			string classStr,
			string methodStr,
			string errorMsg);

	virtual ~TVMonitorException() throw();

	virtual const char* what() const throw();
};

} /* namespace tvmonitor */
#endif /* TVMONITOREXCEPTION_H_ */
