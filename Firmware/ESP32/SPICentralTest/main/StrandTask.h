/*
 * StrandTask.h
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#ifndef MAIN_STRANDTASK_H_
#define MAIN_STRANDTASK_H_

void strandTask(void *pvParameters);

class StrandTask {
public:
	StrandTask();
	virtual ~StrandTask();
};

#endif /* MAIN_STRANDTASK_H_ */
