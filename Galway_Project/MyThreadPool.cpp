#include "stdafx.h"
#include "MyThreadPool.h"

//Method used to call the worker's work method. Is necessary for the calling of different task's methods
static int StaticThreadProcess(void * param)
{
	((Worker*)param)->Work();
	return 0;
}

//Constructor of the Worker. 
Worker::Worker() :
	mtx(SDL_CreateMutex()),
	alive(true)
{
	srand(SDL_GetTicks()); //Seeding the random for each worker
	thd = SDL_CreateThread(StaticThreadProcess, "Worker Thread", (void*)this); //Creating the thread for each worker. 
}

//Method is the main work of the worker. 
//Locks the semaphore for each task in it's list and runs that task.
//Unlocks semaphore after each task has been run to give other workers a chance
//to move through their tasks.
void Worker::Work() {
	while (alive)
	{
		while (!tasks.empty())
		{
			SDL_SemWait(semGlobal); //Locking the semaphore (part of)

			//Locking the mutex so that nothing else can access the tasks at the same time
			SDL_LockMutex(mtx);
			Task task = tasks.front(); //Sets current task to the task at the front of the queue
			Parameter p = parameters.front(); //Takes the parameter from the front of it's queue. Corresponds to task above ^
			SDL_UnlockMutex(mtx); //unlocking

			int alive = 1; //This is used to tell if the task needs to be pushed to the back of the queue to be worked again
			alive = task(p.param); //Running the task. This calls the task method.

			//Locking the mutex so that nothing else can access the tasks at the same time
			SDL_LockMutex(mtx);
			if (!tasks.empty()) { 
				if (alive == 1) {
					tasks.push(tasks.front()); //Moves current task to the back of the queue
					parameters.push(parameters.front()); //Moves current parameter to the back of the queue
				}
				tasks.pop(); //removes task from front of the queue
				parameters.pop(); //removes parameter from front of the queue
			}

			SDL_UnlockMutex(mtx); //unlocking

			SDL_SemPost(semGlobal); //Unlocking the semaphore (part of)
		}
	}
};

//Destructor for the worker, clears the tasks queue, destroys the mtx and waits for the thread to end
Worker::~Worker()
{
	RemoveTasks();
	alive = false; //Worker not alive
	SDL_DestroyMutex(mtx); //Destroying the mutex

	int threadReturnValue; 

	SDL_WaitThread(thd, &threadReturnValue);//Waiting for the threads to end
}

//Method not being used currently
int Worker::id()
{
	return 0;
}

//Size of the tasks queue
int Worker::taskCount()
{
	return tasks.size();
}

//Wait for the tasks queue to be empty (ending the worker)
void Worker::Join()
{
	while (tasks.size());
}

//Adding a task and it's parameter to the worker to be worked
void Worker::AddTask(Task task, Parameter p)
{
	SDL_LockMutex(mtx); //locking mutex for tasks and parameters manipulation
	tasks.push(task);
	parameters.push(p);
	SDL_UnlockMutex(mtx); //Unlocking
}

//Removing all tasks in the queue
void Worker::RemoveTasks()
{
	SDL_LockMutex(mtx); //locking mutex for tasks and parameters manipulation
	tasks = std::queue<Task>();
	SDL_UnlockMutex(mtx); //Unlocking
}

//used for creating a singleton of the the threadpool
bool instanceFlag = false;
ThreadPool* instance = NULL;

//used for creating a singleton of the the threadpool
ThreadPool* ThreadPool::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ThreadPool();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance; //Return instance of the threadpool
	}
}

//Constructor of the threadpool 
ThreadPool::ThreadPool(unsigned int threadCount) :
	index(0)
{
	if (!threadCount)
		threadCount = SDL_GetCPUCount(); //Returns the number of logical cores <- Not using as this is creating errors. 
	workers = std::vector<Worker>(4);
}

//Destructor of the threadpool. Removes tasks from workers and waits for threads to end
ThreadPool::~ThreadPool()
{
	RemoveTasks();
	Join();
}

//Number of threads running are returned
int ThreadPool::threadCount()
{
	return workers.size();
}

//Total number of tasks in the threadpool
int ThreadPool::taskCount()
{
	int task_count = 0;
	for (auto& worker : workers)
		task_count += worker.taskCount();
	return task_count;
}

//Wait for the threads to finish (0)
void ThreadPool::Join()
{
	while (taskCount());
}

//Add task to the next worker. (Index is kept track of)
void ThreadPool::AddTask(Worker::Task task, Parameter p)
{
	workers[index++].AddTask(task, p);
	if (index >= workers.size())
		index = 0;
}

//Remove all tasks from each of the workers
void ThreadPool::RemoveTasks()
{
	for (auto& worker : workers) //Looping through all the workers
		worker.RemoveTasks();
}