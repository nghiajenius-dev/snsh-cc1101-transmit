/*
 * HostComm.h
 *
 *  Created on: Jul 15, 2015
 *      Author: Huan
 */

#ifndef HOSTCOMM_H_
#define HOSTCOMM_H_

typedef enum
{
	INCOMPLETE_MSG=0,
	LENGTH_ERROR,
	CRC_ERROR,
	ENDBYTE_ERROR,
	SUCCESS
}COMM_RESULT;

void HostCommInit();
COMM_RESULT HostComm_process(void);
void copyFromArray(uint8_t *data, uint8_t *x, int len);
void copyToArray(uint8_t *data, uint8_t *x, int len);
uint16_t prepareSpeedSet(uint8_t *data, uint32_t Module_num, uint32_t Value);

#endif /* HOSTCOMM_H_ */
