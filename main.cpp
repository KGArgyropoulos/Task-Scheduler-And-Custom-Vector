#include <iostream>
#include "Vector.h"
#include <string>

using namespace std;

int main(void){
    Vector<string > tableArray;

    tableArray.push_back("Ti kanete eiste kala?");
    tableArray.insert("Kalhspera friends");
    tableArray.push_back("Kai egw kala eimai");
    tableArray.insert("Oriste");
    tableArray.insert("Oriste");

    for (int i=0;i<tableArray.size();i++)
        cout << tableArray[i] << endl;
    /*------------BP1------------*/
    tableArray.pop_back();
    for (int i=0;i<tableArray.size();i++)
        cout << tableArray[i] << endl;
    /*------------BP2------------*/
    tableArray.clear();
    return 0;
}
