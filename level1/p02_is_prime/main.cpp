#include<iostream>
#include"..\..\level1\IsPrime.h"
using namespace std;

int num = 0;

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    if(is_prime(num))
        cout << "Prime." << endl;
    else
        cout << "Not prime." << endl;
    system("pause");
    return 0;
}