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
#include "configuration.h"
#include "PixelMapping.h"

class CommandProcessor {
public:
	CommandProcessor();
	virtual ~CommandProcessor();

	void ProcessRequest(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping);

private:
	void SetPixelData(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping) ;

	void Clear(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping) ;

	void AssignPixelData(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping) ;

	void Commit(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping) ;

	void Configure(Request *request, DisplayDriver *display,
			Configuration *configuration, PixelMapping *pixelMapping) ;
};

#endif /* COMMANDPROCESSOR_H_ */
