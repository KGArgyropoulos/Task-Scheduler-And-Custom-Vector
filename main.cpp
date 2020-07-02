#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#include "Vector.h"
#include "threads.h"

using namespace std;

int main(void){

    /*****REMOVE FILES CREATED FROM THE PREVIOUS EXECUTION*****/
    if (remove("unorderedStrings.txt") !=0)
        cout << "Remove operation failed" << endl;
    else
        cout << "unorderedStrings.txt has been removed." << endl;

    if (remove("partiallyOrderedStrings.txt") !=0)
        cout << "Remove operation failed" << endl;
    else
        cout << "partiallyOrderedStrings.txt has been removed." << endl;
    /**********************************************************/

    Vector<string > tableArray;
    ifstream file("bow.txt");
    string str;
    while(getline(file, str))
        tableArray.push_back(str);
    file.close();

    ofstream MyFile("unorderedStrings.txt");
    for (int i=0;i<tableArray.size();i++)
        MyFile << tableArray[i] << endl;
    MyFile.close();

    string partiallySortedArray[tableArray.size()];

    TaskScheduler *tp = new TaskScheduler(NUMTHREADS);
    addedTasks = NUMTHREADS;
    completedTasks = 0;

    // start, end: first and last index each thread will process
    int partition = tableArray.size() / NUMTHREADS;
    int start = 0;
    int end = partition;
    int timesIn = 0;
    while(end<=tableArray.size()){
        if(++timesIn == NUMTHREADS)
            end = tableArray.size();
        tp->addTask(new dotheJob(tableArray, partiallySortedArray, start, end));
        start = end;
        end += partition;
    }

    tp->barrier();
    delete tp;

    ofstream MyFile_("partiallyOrderedStrings.txt");
    for (int i=0;i<tableArray.size();i++)
        MyFile_ << partiallySortedArray[i] << endl;
    MyFile_.close();

    tableArray.clear();

    return 0;
}
