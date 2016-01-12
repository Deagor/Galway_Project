#ifndef SEMAPHORE_H
#define SEMAPHORE_H

class Semaphore
{
private:
	atomic_int value;
public:
	//constructor
	Semaphore();

	//destructor
	~Semaphore();

	//P operation decrements the semaphore
	void P();

	//V operation increments semaphore
	void V();

	//Check the current value of the semaphore
	int GetCurrentValue();
};

#endif