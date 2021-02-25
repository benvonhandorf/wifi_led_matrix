/*
 * ControlTask.h
 *
 *  Created on: Jan 24, 2021
 *      Author: benvh
 */

#ifndef MAIN_CONTROLTASK_H_
#define MAIN_CONTROLTASK_H_

void controlTask(void *pvParameters);

class ControlTask {
public:
	ControlTask();
	virtual ~ControlTask();
	void Run();
};

#endif /* MAIN_CONTROLTASK_H_ */
