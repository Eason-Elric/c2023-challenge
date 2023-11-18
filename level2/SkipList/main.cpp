#include <iostream>
#include "SkipList.h"

using namespace std;

int main() {
    SkipList skipList;
    skipList.insert(5);
    skipList.insert(6);
    skipList.insert(7);
    skipList.insert(9);
    skipList.remove(9);
    cout << skipList.search(7) << endl;
    cout << skipList.search(8) << endl;
    cout << skipList.search(9);
    return 0;
}