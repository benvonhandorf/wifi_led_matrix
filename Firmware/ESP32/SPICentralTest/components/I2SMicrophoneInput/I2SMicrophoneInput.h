/*
 * I2SMicrophoneInput.h
 *
 *  Created on: Jan 26, 2021
 *      Author: benvh
 */

#ifndef COMPONENTS_I2SMICROPHONEINPUT_I2SMICROPHONEINPUT_H_
#define COMPONENTS_I2SMICROPHONEINPUT_I2SMICROPHONEINPUT_H_

void i2sMicrophoneInputTask(void *pvParameters);

class I2SMicrophoneInput {
public:
	I2SMicrophoneInput();
	virtual ~I2SMicrophoneInput();
};

#endif /* COMPONENTS_I2SMICROPHONEINPUT_I2SMICROPHONEINPUT_H_ */
