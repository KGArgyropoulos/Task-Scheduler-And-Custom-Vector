#include <iostream>
#include <cmath>
#include "threads.h"

using namespace std;

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t condMain = PTHREAD_COND_INITIALIZER;

uint64_t addedTasks;
uint64_t completedTasks;

TaskQueue::TaskQueue() {
    pthread_mutex_init(&mut, NULL);
    pthread_cond_init(&cond, NULL);
}

TaskQueue::~TaskQueue() {
    pthread_mutex_destroy(&mut);
    pthread_cond_destroy(&cond);
}

Task* TaskQueue::nextTask() {                                                   //get next task from the queue
    Task *nextTask = 0;

    pthread_mutex_lock(&mut);

    while (tasks.empty()) {                                                     //while task queue is empty
        pthread_cond_wait(&cond, &mut);                                         //current thread waits(till task arrives)
    }

    nextTask = tasks.front();                                                   //get next task
    tasks.pop();
    pthread_mutex_unlock(&mut);

    return nextTask;
}

void TaskQueue::addTask(Task *nextTask){                                        //add new task to the queue
    pthread_mutex_lock(&mut);
    tasks.push(nextTask);                                                       //add task
    pthread_cond_signal(&cond);                                                 //signal new task
    pthread_mutex_unlock(&mut);
}

void *processTask(void* par){                                                   //receive, execute and delete task
    TaskQueue *tq = (TaskQueue*)par;
    while (Task* task = tq->nextTask()){
        task->run();
        delete task;
    }
}

TaskScheduler::TaskScheduler(int n) : numThreads(n){
    threads = new pthread_t[n];
    for (int i=0; i< n; ++i) {
        pthread_create(&(threads[i]), NULL, processTask, &taskQueue);
    }
}

TaskScheduler::~TaskScheduler(){                                                //before destroying TaskScheduler
    join();                                                                     //wait for every active task to complete execution
    delete [] threads;
}

void TaskScheduler::addTask(Task *nextTask) {
    taskQueue.addTask(nextTask);
}

void TaskScheduler::join(){
    int i;
	for (i=0; i<numThreads; ++i){                                               // thread knows we've terminated it
        taskQueue.addTask(NULL);                                                // when receives NULL task
    }

	for (i=0; i<numThreads; ++i){
		pthread_join(threads[i], NULL);
	}
}

void TaskScheduler::barrier(){
    pthread_mutex_lock(&mut);
    while(completedTasks != addedTasks)                                         //wait for every task to complete execution
        pthread_cond_wait(&condMain, &mut);
    pthread_mutex_unlock(&mut);
}

dotheJob::dotheJob(Vector<string > t,string *psa, int s, int e) : Task(), tableArray(t), partiallySortedArray(psa), startIndex(s), endIndex(e) {}

dotheJob::~dotheJob() {}

void dotheJob::run() {

    /*Bubble Sort*/
    for(int i=startIndex; i<endIndex-1; i++){
        for(int j=startIndex; j < (startIndex+(endIndex-i-1)) ; j++){ 
            if(tableArray[j] > tableArray[j+1]){
                string temp = tableArray[j];
                tableArray[j] = tableArray[j+1];
                tableArray[j+1] = temp;
            }
        }
    }

    for(int i=startIndex;i<endIndex;i++)
        partiallySortedArray[i] = tableArray[i];

    pthread_mutex_lock(&mut);
    completedTasks++;                   //every time a task is completed, we increase the completedTasks counter
    if (completedTasks == addedTasks)
        pthread_cond_signal(&condMain);

    pthread_mutex_unlock(&mut);
}
