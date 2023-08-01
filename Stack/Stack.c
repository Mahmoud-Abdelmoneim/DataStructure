/**
  ******************************************************************************
  * @auther         : Mahmoud Abdelmoniem
  * @data           : 19/9/2022
  * @file           : Stack.c
  * @brief          : Stack program body
  ******************************************************************************
  */
#include "Stack.h"

#if  STACK_TYPE == STACK_BASED_ON_ARRAY
/**
*
*@brief  Check stack is full
*@param  Stack: pointer to stack
*@RetVal STACK_FULL :if the stack is full
*		 STACK_NOT_FULL : if the stack is not full	
*/
static Stack_Status_t StackFull(Stack_ds_t* Stack)
{
	if (Stack->StackPointer == STACK_MAX_SIZE - 1)
	{
		return STACK_FULL;
	}
	else
	{
		return STACK_NOT_FULL;
	}
}
/**
*
*@brief  Check stack is full
*@param  Stack: pointer to stack
*@RetVal  STACK_EMBTY :if the stack is embty
*		  STACK_NOT_FULL : if the stack is not full
*/
static Stack_Status_t StackEmbty(Stack_ds_t* Stack)
{
	if (Stack->StackPointer == - 1)
	{
		return STACK_EMBTY;
	}
	else
	{
		return STACK_NOT_FULL;
	}
}

/**
*
*@brief  Initilize the stack pointer 
*@param  Stack: pointer to stack
*@RetVal status of the initializtion process  
*/
Return_Status_t StackInit(Stack_ds_t* Stack)
{
	Return_Status_t RetVal = R_NOK;
	//varifiy if the user dosnt pass an pointer
	if (NULL == Stack)
	{
		RetVal = R_NOK;

	}
	else
	{
		Stack->StackPointer = -1;
		RetVal = R_OK;
	}


	return RetVal;

}

/**
*
*@brief  Push data in the stack
*@param  Stack: pointer to stack
*@param  Data: the data needed to push 
*@RetVal status of the initializtion process
*/
Return_Status_t StackPush(Stack_ds_t* Stack, uint32 Data)
{
	Return_Status_t RetVal = R_NOK;
	if (Stack == NULL || StackFull(Stack) == STACK_FULL)
	{
		RetVal = R_NOK;
#ifdef STACK_DEBUG
		printf("data (%i) Doesn't peshed in the satck may be the stack is full\n", Data);
#endif // STACK_DEBUG
	}
	else
	{
		Stack->StackPointer++;
		Stack->Data[Stack->StackPointer] = Data;
#ifdef STACK_DEBUG
		printf("data (%i) poshed in the satck\n", Data);
#endif // STACK_DEBUG
		RetVal = R_NOK;
	}
	return RetVal;

}

/**
*
*@brief  Push data in the stack
*@param  Stack: pointer to stack
*@param  Data: pointer to variable which contain the data was poped
*@RetVal status of the initializtion process
*/
Return_Status_t StackPop(Stack_ds_t* Stack, uint32* Data)
{
	Return_Status_t RetVal = R_NOK;
	if (Stack == NULL || Data == NULL || StackEmbty(Stack) == STACK_EMBTY)
	{
#ifdef STACK_DEBUG
		printf("data Doesn't poped from the satck may be the stack is embty\n");
#endif // STACK_DEBUG
		RetVal = R_NOK;
	}
	else
	{
		*Data = Stack->Data[Stack->StackPointer];
		Stack->StackPointer--;
#ifdef STACK_DEBUG
		printf("data (%i) poped from the satck\n", *Data);
#endif // STACK_DEBUG		

		RetVal = R_NOK;
	}
	return RetVal;
}
/**
*
*@brief  Get the top of the stack
*@param  Stack: pointer to stack
*@param  Data: pointer to variable which contain the top of stack
*@RetVal status of the initializtion process
*/
Return_Status_t StackTop(Stack_ds_t* Stack, uint32* Data)
{

	Return_Status_t RetVal = R_NOK;
	if (Stack == NULL || Data == NULL || StackEmbty(Stack) == STACK_EMBTY)
	{
#ifdef STACK_DEBUG
		printf("data Doesn't Got from the satck may be the stack is embty\n");
#endif // STACK_DEBUG
		RetVal = R_NOK;
	}
	else
	{
		*Data = Stack->Data[Stack->StackPointer];
#ifdef STACK_DEBUG
		printf("data (%i) Got from the satck\n", *Data);
#endif // STACK_DEBUG	
		RetVal = R_NOK;
	}
	return RetVal;
}
/**
*
*@brief  Get the size of the stack
*@param  Stack: pointer to stack
*@param  Data: pointer to variable which contain the size of stack
*@RetVal status of the initializtion process
*/
Return_Status_t StackSize(Stack_ds_t* Stack, uint32* Data)
{
	Return_Status_t RetVal = R_NOK;
	if (Stack == NULL || Data == NULL )
	{
		RetVal = R_NOK;
	}
	else
	{
		*Data = Stack->StackPointer + 1;
#ifdef STACK_DEBUG
		printf("\nThe stack size is (%i)\n", *Data);
#endif // STACK_DEBUG	
		RetVal = R_NOK;
	}
	return RetVal;
}
/**
*
*@brief	 Display the all data in the stack
*@param  Stack: pointer to stack
*@RetVal  status of the initializtion process
*/
Return_Status_t StackDisplay(Stack_ds_t* Stack)
{
	Return_Status_t RetVal = R_NOK;
	sint32 l_counter = ZERO_INIT;
	if (Stack == NULL || StackEmbty(Stack) == STACK_EMBTY)
	{
		RetVal = R_NOK;
#ifdef STACK_DEBUG
		printf("Error...the satck may be the stack is embty\n");
#endif // STACK_DEBUG
	}
	else
	{
		printf("the stake data:\n");
		for (l_counter = ZERO_INIT; l_counter <= Stack->StackPointer; l_counter++)
		{
			printf("%i	", Stack->Data[l_counter]);
		}
		RetVal = R_OK;
	}
	return RetVal;
}
#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY




#if  STACK_TYPE == STACK_BASED_ON_DYNAMIC_MEMORY


static Stack_Status_t StackEmbty(Stack_ds_t* Stack);
static Stack_Status_t StackFull(Stack_ds_t* Stack);



/**
*
*@brief  Create Stack
*@param  maxSize: Maximum size of the stack
*@param  stakeStatus: pointer to variable to get the status 
*@RetVal pointer to the created stack
*/
Stack_ds_t* l_Pstack = NULL;
Stack_ds_t* StackCreate(uint32 maxSize, Stack_Status_t* stakeStatus)
{
	//*stakeStatus = STACK_NOK;
	
	if (stakeStatus == NULL)
	{
		//*stakeStatus = STACK_NOK;
		l_Pstack = NULL;
	}
	else
	{

		l_Pstack = (Stack_ds_t*)malloc(sizeof(Stack_ds_t));
		if (!l_Pstack)
		{
			*stakeStatus = STACK_NOK;
			l_Pstack = NULL;
		}
		else
		{

			l_Pstack->StackTop = -1;			/*initiailize top of the stack*/
			l_Pstack->StackMaxSize = maxSize;	/*assign the maximum number of data in the stack*/
			l_Pstack->ElementCount = 0;			/*has the number of elements in the stack at this time*/
			l_Pstack->StackArray = (void**)calloc(l_Pstack->StackMaxSize, sizeof(void*));	
			if (!l_Pstack->StackArray)          /*cheack if dynamic allocation is done or not*/
			{
				*stakeStatus = STACK_NOK;      /*return value not ok if the daynamic allocation failed*/
				free(l_Pstack);				   /*free the memory of the structure due to un complete allocation*/
				l_Pstack = NULL;			   /*l_Pstack point to NULL*/
			}
			else
			{
				*stakeStatus = STACK_OK;	   /*return value ok if all daynamic allocation complete*/
			}
		}
		
	}
	return l_Pstack;
}

/**
*
*@brief  Destroy Stack
*@param  stack: Pointer to the stack needed to destroy
*@param  stakeStatus: pointer to variable to get the status
*@RetVal NULL pointer 
*/

Stack_ds_t* StackDestroy(Stack_ds_t* stack, Stack_Status_t* stakeStatus)
{

	
	if (stakeStatus == NULL || stack == NULL)
	{
		*stakeStatus = STACK_NULL_POINTER;
	}
	else
	{

		free(stack->StackArray);
		free(stack);
		*stakeStatus = STACK_OK;
	}


	return NULL;

}
/**
*
*@brief  Push data in the Stack
*@param  stack: Pointer to the stack
*@param  pdata: pointer to variable which wanted to store the pushed data in
*@RetVal  status of the initializtion process
*/

Stack_Status_t StackPush(Stack_ds_t* stack, void* pdata)
{

	Stack_Status_t RetVal = STACK_NOK;
	if (pdata == NULL || stack == NULL)
	{
#ifdef STACK_DEBUG == STACK_BASED_ON_DYNAMIC_MEMORY
		printf("data (%i) Doesn't peshed in the satck may be the stack is full\n", pdata);
#endif // STACK_DEBUG
		RetVal = STACK_NULL_POINTER;
	}
	else
	{
		if (StackEmbty(stack) == STACK_FULL)
		{
			RetVal = STACK_NOK;
		}
		else
		{
			stack->StackArray[stack->StackTop] = pdata;
			(stack->ElementCount)++;
			(stack->StackTop)++;
#ifdef STACK_DEBUG == STACK_BASED_ON_DYNAMIC_MEMORY
			printf("data (%i) poshed in the satck\n", pdata);
#endif // STACK_DEBUG
		}

		RetVal = STACK_OK;
	}


	return RetVal;

}
/**
*
*@brief  Pop data in the Stack
*@param  stack: Pointer to the stack
*@param  stakeStatus: pointer to variable to get the status
*@RetVal Pointer to the data was poped
*/
void* StackPop(Stack_ds_t* stack, Stack_Status_t* stakeStatus)
{
	void* l_pdata = 0;
	if (stakeStatus == NULL || stack == NULL)
	{
		*stakeStatus = STACK_NULL_POINTER;
		l_pdata = NULL;
	}
	else
	{
		if (StackEmbty(stack) == STACK_EMBTY)
		{
			*stakeStatus = STACK_NOK;
		}
		else
		{
			l_pdata =stack->StackArray[stack->StackTop] ;
			(stack->ElementCount)--;
			(stack->StackTop)--;
			*stakeStatus = STACK_OK;
		}

		
	}

	return l_pdata;
}
/**
*
*@brief  Pop data in the Stack
*@param  stack: Pointer to the stack
*@param  stakeStatus: pointer to variable to get the status
*@RetVal Pointer to the data was got
*/
void* StackTop(Stack_ds_t* stack, Stack_Status_t* stakeStatus)
{
	void* l_pdata = 0;
	if (stakeStatus == NULL || stack == NULL)
	{
		*stakeStatus = STACK_NULL_POINTER;
		l_pdata = NULL;
	}
	else
	{
		if (StackEmbty(stack) == STACK_EMBTY)
		{
			*stakeStatus = STACK_NOK;
		}
		else
		{
			l_pdata = stack->StackArray[stack->StackTop];
			*stakeStatus = STACK_OK;
		}
	}

	return l_pdata;
}
/**
*
*@brief  count the data in the Stack
*@param  stack: Pointer to the stack
*@param  count: pointer to variable which wanted to store the the number of data in the stack
*@RetVal  status of the initializtion process
*/

Stack_Status_t StackCount(Stack_ds_t* stack, uint32* count)
{
	Stack_Status_t RetVal = STACK_NOK;
	if (count == NULL || stack == NULL)
	{
		RetVal = STACK_NULL_POINTER;
	}
	else
	{
		*count = stack->ElementCount;

		RetVal = STACK_OK;
	}


	return RetVal;
}



static Stack_Status_t StackEmbty(Stack_ds_t* Stack)
{
	Stack_Status_t RetVal = STACK_NOK;
	if (Stack->ElementCount == 0)
	{
		RetVal = STACK_EMBTY;
	}
	else
	{
		RetVal = STACK_NOT_FULL;
	}
	return RetVal;
}
static Stack_Status_t StackFull(Stack_ds_t* Stack)
{
	Stack_Status_t RetVal = STACK_NOK;
	if (Stack->ElementCount == Stack->StackMaxSize)
	{
		RetVal = STACK_FULL;
	}
	else
	{
		RetVal = STACK_NOT_FULL;
	}
	return RetVal;
}




#endif //  STACK_TYPE == STACK_BASED_ON_ARRAY
