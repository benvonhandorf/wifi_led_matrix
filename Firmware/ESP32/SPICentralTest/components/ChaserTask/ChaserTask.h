/*
 * StrandTask.h
 *
 *  Created on: Jan 17, 2021
 *      Author: benvh
 */

#ifndef MAIN_STRANDTASK_H_
#define MAIN_STRANDTASK_H_

void chaserTask(void *pvParameters);

class ChaserTask {
public:
	ChaserTask();
	virtual ~ChaserTask();
};

#endif /* MAIN_STRANDTASK_H_ */
