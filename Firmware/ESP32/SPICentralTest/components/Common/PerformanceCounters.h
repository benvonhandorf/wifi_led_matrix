/*
 * PerformanceCounters.h
 *
 *  Created on: Mar 12, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_COMMON_PERFORMANCECOUNTERS_H_
#define COMPONENTS_COMMON_PERFORMANCECOUNTERS_H_

#include <stdint.h>

void performanceCountersTask(void *pvParameters);

class PerformanceCounters {
public:
	PerformanceCounters();
	virtual ~PerformanceCounters();

	volatile uint32_t framesDrawn;
	volatile uint32_t packetsSent;
};

extern PerformanceCounters performanceCounters;

#endif /* COMPONENTS_COMMON_PERFORMANCECOUNTERS_H_ */
