/*
 * DisplayTask.h
 *
 *  Created on: Mar 7, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_DISPLAYTASK_DISPLAYTASK_H_
#define COMPONENTS_DISPLAYTASK_DISPLAYTASK_H_

#include "Configuration.h"
#include "DisplayBuffer.h"
#include "driver/spi_master.h"

void displayTask(void *pvParameters);

class DisplayTask {
public:
	DisplayTask();
	virtual ~DisplayTask();

	void Initialize(Configuration *configuration, spi_device_handle_t spi);

private:
	Configuration *configuration;
	spi_device_handle_t spiDevice;

	void Configure();
	void ProcessBuffer(DisplayBuffer *displayBuffer);
	void SendMessage(uint8_t *transmissionBuffer);
};

#endif /* COMPONENTS_DISPLAYTASK_DISPLAYTASK_H_ */
