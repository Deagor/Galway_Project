#include "stdafx.h"
#include "MyThreadPool.h"

static int StaticThreadProc(void * param)
{
	((Worker*)param)->Work();
	return 0;
}

Worker::Worker() :
	mtx(SDL_CreateMutex()),
	alive(true)
{
	srand(SDL_GetTicks());
	sem = SDL_CreateSemaphore(1);
	thd = SDL_CreateThread(StaticThreadProc, "LazyThread", (void*)this);
}

void Worker::Work() {
	while (alive)
	{
		while (!tasks.empty())
		{
			SDL_SemWait(semGlobal);

			SDL_LockMutex(mtx);
			Task task = tasks.front();
			Parameter p = parameters.front();
			SDL_UnlockMutex(mtx);

			int alive = 1;
			alive = task(p.param);

			SDL_LockMutex(mtx);
			if (!tasks.empty()) {
				if (alive == 1) {
					tasks.push(tasks.front());
					parameters.push(parameters.front());
				}
				tasks.pop();
				parameters.pop();
			}

			SDL_UnlockMutex(mtx);

			SDL_SemPost(semGlobal);
		}
	}
};

Worker::~Worker()
{
	RemoveTasks();
	alive = false;
	SDL_DestroyMutex(mtx);
	SDL_DestroySemaphore(sem);
	sem = NULL;

	int threadReturnValue;

	SDL_WaitThread(thd, &threadReturnValue);
}

int Worker::id()
{
	return 0;
}

int Worker::taskCount()
{
	return tasks.size();
}

void Worker::Join()
{
	while (tasks.size());
}

void Worker::AddTask(Task task, Parameter p)
{
	SDL_LockMutex(mtx);
	tasks.push(task);
	parameters.push(p);
	SDL_UnlockMutex(mtx);

	SDL_SemPost(sem);
}

void Worker::RemoveTasks()
{
	SDL_LockMutex(mtx);
	tasks = std::queue<Task>();
	SDL_UnlockMutex(mtx);
}

bool instanceFlag = false;
ThreadPool* instance = NULL;

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
		return instance;
	}
}

ThreadPool::ThreadPool(unsigned int threadCount) :
	index(0)
{
	if (!threadCount)
		threadCount = thread::hardware_concurrency();
	workers = std::vector<Worker>(4);
}

ThreadPool::~ThreadPool()
{
	RemoveTasks();
	Join();
}

int ThreadPool::threadCount()
{
	return workers.size();
}

int ThreadPool::taskCount()
{
	int task_count = 0;
	for (auto& worker : workers)
		task_count += worker.taskCount();
	return task_count;
}

void ThreadPool::Join()
{
	while (taskCount());
}

void ThreadPool::AddTask(Worker::Task task, Parameter p)
{
	workers[index++].AddTask(task, p);
	if (index >= workers.size())
		index = 0;
}

void ThreadPool::RemoveTasks()
{
	for (auto& worker : workers)
		worker.RemoveTasks();
}