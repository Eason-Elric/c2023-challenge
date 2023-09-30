#include <iostream>
using namespace std;

int num = 0;

void hanoi(int num__, char begin__, char end__);

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    hanoi(num, 'A', 'C');
    return 0;
}

void hanoi(int num__, char begin__, char end__){
    if(num__ == 1)
        cout << begin__ << " -> " << end__ << endl;
    else{
        hanoi(num__ - 1, begin__, (char)('A' + 3 + ('A' - begin__) + ('A' - end__)));
        cout << begin__ << " -> " << end__ << endl;
        hanoi(num__ - 1, (char)('A' + 3 + ('A' - begin__) + ('A' - end__)), end__);
    }
}