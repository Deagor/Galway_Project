#pragma once

#include "stdafx.h"   

struct Parameter {
	void* param;
};

class Worker {

public:
	typedef function<int(void*)> Task;

	Worker();
	~Worker();

	int id();
	int taskCount();
	void Join();
	void AddTask(Task task, Parameter);
	void RemoveTasks();
	void Work();

private:
	queue<Task> tasks;
	queue<Parameter> parameters;
	SDL_Thread* thd;
	SDL_mutex* mtx = NULL;
	bool alive;
	SDL_sem* sem = NULL;
};

class ThreadPool {
private:
	vector<Worker> workers;
	int index;
public:
	static ThreadPool* GetInstance();

	ThreadPool(unsigned int threadCount = 0);
	~ThreadPool();

	int threadCount();
	int taskCount();
	void Join();
	void AddTask(Worker::Task task, Parameter);
	void RemoveTasks();
};