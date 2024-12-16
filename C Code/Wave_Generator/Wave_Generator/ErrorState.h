/*
 * ErrorState.h
 *
 *  Created on: Jul 18, 2023
 *      Author: top
 */

#ifndef ERRORSTATE_H_
#define ERRORSTATE_H_


typedef enum
{
	ES_NOK,
	ES_OK,
	OUT_OF_RANGE,
	NULL_POINTER,
	StartConditionError,
	RepeatedStartError,
	SlaveAddressWithWriteError,
	SlaveAddressWithReadError,
	MasterWriteByteError,
	MasterReadByteError,

}ES_t;


#endif /* ERRORSTATE_H_ */
