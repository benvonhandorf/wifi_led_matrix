/*
 * DisplayTask.h
 *
 *  Created on: Mar 7, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_M5DISPLAYTASK_M5DISPLAYTASK_H_
#define COMPONENTS_M5DISPLAYTASK_M5DISPLAYTASK_H_

#include "Configuration.h"
#include "DisplayBuffer.h"
#include "driver/spi_master.h"

void m5DisplayTask(void *pvParameters);

class M5DisplayTask {
public:
	M5DisplayTask();
	virtual ~M5DisplayTask();

	void Initialize(Configuration *configuration, spi_device_handle_t spi);

private:
	Configuration *configuration;
	spi_device_handle_t spiDevice;

	void Configure();
	void ProcessBuffer(DisplayBuffer *displayBuffer);
	void SendMessage(uint8_t *transmissionBuffer);
};

#endif /* COMPONENTS_M5DISPLAYTASK_M5DISPLAYTASK_H_ */
