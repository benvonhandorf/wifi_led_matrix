/*
 * DummyDisplayDriver.h
 *
 *  Created on: Dec 12, 2020
 *      Author: benvh
 */

#ifndef DUMMYDISPLAYDRIVER_H_
#define DUMMYDISPLAYDRIVER_H_

#include <DisplayDriver.h>

class DummyDisplayDriver: public DisplayDriver {
public:
	DummyDisplayDriver();
	virtual ~DummyDisplayDriver();
};

#endif /* DUMMYDISPLAYDRIVER_H_ */
