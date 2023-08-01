/**
  ******************************************************************************
  * @auther         : Mahmoud Abdelmoniem
  * @data           : 19/9/2022
  * @file           : Stack.c
  * @brief          : Stack program body
  ******************************************************************************
 */
#ifndef  __STACK_H__
#define __STACK_H__


/***************************************************************************/
/*******************************Section Includes****************************/
/***************************************************************************/

#include <stdio.h>
#include "StdTypes.h"
#include "DataStrucure_Config.h"

/***************************************************************************/
/************************Section Macro Declaration**************************/
/***************************************************************************/
#if  STACK_TYPE == STACK_BASED_ON_ARRAY

#define STACK_MAX_SIZE       6

#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY




#if  STACK_TYPE == STACK_BASED_ON_DYNAMIC_MEMORY

#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY



/***************************************************************************/
/*********************Section Data Types Declaration************************/
/***************************************************************************/
#if  STACK_TYPE == STACK_BASED_ON_ARRAY
typedef struct {
	sint32 StackPointer;                /*Point to the top of the stack*/
	uint32 Data[STACK_MAX_SIZE];		/*Array has the data stotred in the stack*/

}Stack_ds_t;


#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY



#if  STACK_TYPE == STACK_BASED_ON_DYNAMIC_MEMORY
typedef struct {
	void** StackArray;               /*points to the array that allocated in the heap*/
	sint32 ElementCount;			 /*has the actual number of elements in the stack*/
	sint32 StackMaxSize;			 /*has the max number of elements in the stack   */
	sint32 StackTop;	 			 /*has the index of the top element in the stack */
}Stack_ds_t;

#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY
typedef enum {
	STACK_NOK,
	STACK_OK,
	STACK_EMBTY,
	STACK_FULL,
	STACK_NOT_FULL,
	STACK_NULL_POINTER
}Stack_Status_t;

/***************************************************************************/
/***********************Section Funcions Declaration************************/
/***************************************************************************/
#if  STACK_TYPE == STACK_BASED_ON_ARRAY
Return_Status_t StackInit(Stack_ds_t *Stack);
Return_Status_t StackPush(Stack_ds_t* Stack, uint32 Data);
Return_Status_t StackPop(Stack_ds_t* Stack, uint32 *Data);
Return_Status_t StackTop(Stack_ds_t* Stack, uint32* Data);
Return_Status_t StackSize(Stack_ds_t* Stack, uint32* Data);
Return_Status_t StackDisplay(Stack_ds_t* Stack);
#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY


#if  STACK_TYPE == STACK_BASED_ON_DYNAMIC_MEMORY

Stack_ds_t* StackCreate(uint32 maxSize, Stack_Status_t* stakeStatus);
Stack_ds_t* StackDestroy(Stack_ds_t* stack, Stack_Status_t* stakeStatus);
Stack_Status_t StackPush(Stack_ds_t* stack, void* pdata);
void* StackPop(Stack_ds_t* stack, Stack_Status_t* stakeStatus);
void* StackTop(Stack_ds_t* stack, Stack_Status_t* stakeStatus);
Stack_Status_t StackCount(Stack_ds_t* stack, uint32* count);


#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY
#endif
