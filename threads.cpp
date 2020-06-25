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

Task* TaskQueue::nextTask() {                                                   //lipsi epomenou task apo tin oura
    Task *nextTask = 0;

    pthread_mutex_lock(&mut);

    while (tasks.empty()) {                                                     //oso i oura ton tasks einai adeia
        pthread_cond_wait(&cond, &mut);                                         //to trexon nima pagonei (mexri na erthei kapoio task stin oura)
    }

    nextTask = tasks.front();                                                   //lipsi epomenou task
    tasks.pop();
    pthread_mutex_unlock(&mut);

    return nextTask;
}

void TaskQueue::addTask(Task *nextTask){                                        //prosthiki neou task stin oura
    pthread_mutex_lock(&mut);
    tasks.push(nextTask);                                                       //prosthiki task
    pthread_cond_signal(&cond);                                                 //signal oti iparxei neo task
    pthread_mutex_unlock(&mut);
}

void *processTask(void* par){                                                   //lipsi, ektelesi kai diagrafi task
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

TaskScheduler::~TaskScheduler(){                                                //prin tin katastrofi tou TaskScheduler
    join();                                                                     //perimenoume na ektelestoun ola ta energa threads
    delete [] threads;
}

void TaskScheduler::addTask(Task *nextTask) {
    taskQueue.addTask(nextTask);
}

void TaskScheduler::join(){
    int i;
	for (i=0; i<numThreads; ++i){                                               //to thread antilambanetai oti theloume na termatistei
        taskQueue.addTask(NULL);                                                //  otan lavei apo tin oura NULL task
    }

	for (i=0; i<numThreads; ++i){
		pthread_join(threads[i], NULL);
	}
}

void TaskScheduler::barrier(){
    pthread_mutex_lock(&mut);
    while(completedTasks != addedTasks)                                         //perimenoume mexri na ektelestoun ola ta tasks tou trexontos vimatos (hist, )
        pthread_cond_wait(&condMain, &mut);
    pthread_mutex_unlock(&mut);
}


dotheJob::dotheJob(string l,Vector<table*> t) : Task(),line(l),tableArray(t) {}

dotheJob::~dotheJob() {}

void dotheJob::run() {

}