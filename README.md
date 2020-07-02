# Project: Partial Order
-   Create a main driver program
    * which will store random strings from a bow (100 strings/bow.txt) to VECTORS(custom Vector.h file is the library) and display them.
        * unorderedStrings.txt gets created to dispay the strings.
    * those strings will be sent to threads (4 threads / 25 strings to each one of them in that case).
    * threads will sort them to their alphabetical (ASCII) value.
    * the results will be 4 ordered partitions of the initial file.
        * partiallyOrderedStrings.txt gets created to dispay the strings' new order.
# NOTE: The addition of a merge function could be a future add-on.

- **Compilation & Execution**
    * Compile: make
    * Remove object files: make clean
    * Run: ./run

**Vector.h**
This is the vector implementation header file. Class vector -of type template- has 4 constructors, whose calls depend on the arguments of the Vector function.
**Basic functionalities:**
- insert: Insertion of an element at the beggining of the vector
- push_back: Insertion of an element at the end of the vector
- reserve: In charge of having enough memory allocated, for every insertion. Every time the buffer is overloading, reserve creates a new array with more space an copies the elements of the existing one.

**threads.cpp**
Initially the constructon of the TaskScheduler is called, which creates a number of threads running at processTask and being enqueued with the TaskQueue class in charge for that. When we execute a thread, we call addTask function from TaskScheduler. addTask respectively calls addTask from TaskQueue, which pushes the prioritized task in the stack, triggering nextTash which, until this point, is waiting for an element (task)in the stack and returns the task to processTask, which executes it.
