#ifndef THREADS_H
#define THREADS_H

#include <queue>
#include <pthread.h>
#include "Vector.h"

using namespace std;

#define NUMTHREADS 4

extern pthread_mutex_t mut;
extern pthread_cond_t cond;
extern pthread_cond_t condMain;

extern uint64_t addedTasks;
extern uint64_t completedTasks;

class Task {
public:
    Task() {}
    virtual ~Task() {}
    virtual void run() = 0;                                                     //ektelesi tou task apo tin paragogi klasi
};

class TaskQueue {
private:
    queue<Task*> tasks;
public:
    TaskQueue();
    ~TaskQueue();
    Task* nextTask();                                                           //lipsi epomenou task apo tin oura
    void addTask(Task* );                                                       //proshiki task stin oura
};

void *processTask(void* );

class TaskScheduler {
private:
    pthread_t* threads;
    int numThreads;
    TaskQueue taskQueue;
public:
    TaskScheduler(int );
    ~TaskScheduler();
    void addTask(Task* );
    void join();
    void barrier();                                                             //anamoni mexri na ektelestoun ola ta tasks tou trexontos vimatos (p.x. HistPsum, Ordered, Join)
};

class dotheJob : public Task {
private:
    Vector<string> tableArray;
    string *partiallySortedArray;
    int startIndex;
    int endIndex;
public:
    dotheJob(Vector<string> t, string *psa, int s, int e);
    ~dotheJob();
    void run();
};

#endif
