#include<iostream>
#include<time.h>
#include"..\..\level1\IsPrime.h"
using namespace std;

int num = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    for(int i = 2; i <= num; i++)
        if(is_prime(i))
            cout << i << " ";
    cout << endl;
    cout << "Time used " << (double)clock() / CLOCKS_PER_SEC << "s";
    return 0;
}