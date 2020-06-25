# Task-Scheduler-And-Custom-Vector
Waiting an inspiration for the driver program though!
- Under Construction of driver program (main)
- Need to work on the threads.cpp as well
- Changed the Makefile to check the vector who can also be modified/optimized

**Vector.h**
This is the vector implementation header file. Class vector -of type template- has 4 constructors, whose calls depend on the arguments of the Vector function.
**Basic functionalities:**
- insert: Insertion of an element at the beggining of the vector
- push_back: Insertion of an element at the end of the vector
- reserve: In charge of having enough memory allocated, for every insertion. Every time the buffer is overloading, reserve creates a new array with more space an copies the elements of the existing one.

**threads.cpp**
Initially the constructon of the TaskScheduler is called, which creates a number of threads running at processTask and being enqueued with the TaskQueue class in charge for that. When we execute a thread, we call addTask function from TaskScheduler. addTask respectively calls addTask from TaskQueue, which pushes the prioritized task in the stack, triggering nextTash which, until this point, is waiting for an element (task)in the stack and returns the task to processTask, which executes it.
