#ifndef __TASKPARAMETERS_H
#define __TASKPARAMETERS_H

#include "driver/spi_master.h"

#include "Configuration.h"

struct TaskParameters {
	spi_device_handle_t spiDevice;

	Configuration *configuration;
};

#endif
