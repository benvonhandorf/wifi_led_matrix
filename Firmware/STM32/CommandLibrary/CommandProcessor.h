/*
 * Command.h
 *
 *  Created on: Dec 6, 2020
 *      Author: benvh
 */

#ifndef COMMANDPROCESSOR_H_
#define COMMANDPROCESSOR_H_

#include "DisplayDriver.h"
#include "Request.h"

class CommandProcessor {
public:
	CommandProcessor();
	virtual ~CommandProcessor();

	void ProcessRequest(Request *request, DisplayDriver *display);
};

#endif /* COMMANDPROCESSOR_H_ */
