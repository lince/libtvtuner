/*
 * TVMonitorException.cpp
 *
 *  Created on: Jul 8, 2011
 *      Author: caioviel
 */

#include "../include/TVMonitorException.h"

namespace tvmonitor {

TVMonitorException::TVMonitorException(
		string c, string m, string e) : classStr(c), methodStr(m), errorMsg(e) {

}

TVMonitorException::~TVMonitorException() throw() {

}


const char* TVMonitorException::what() const throw() {
	string fullMsg = "A TVMonitorException occurred on class <";
	fullMsg += classStr + "> at method <" + methodStr + ">\n";
	fullMsg += "\terror message: " + errorMsg;
	return fullMsg.c_str();
}

} /* namespace tvmonitor */
