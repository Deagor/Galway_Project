#include "stdafx.h"
#include "Semaphore.h"

//constructor
Semaphore::Semaphore()
{
	value = 1;//Because this is a binary semaphore
}

//destructor
Semaphore::~Semaphore()
{

}

//P operation decrements the semaphore
void Semaphore::P()
{
	value -= 1;
}

//V operation increments semaphore
void Semaphore::V()
{
	value += 1;
}

//Check the current value of the semaphore
int Semaphore::GetCurrentValue()
{
	return value;
}