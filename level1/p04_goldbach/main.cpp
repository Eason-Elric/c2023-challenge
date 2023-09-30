#include <iostream>
#include "../LibraryFiles/IsPrime.h"
using namespace std;

int num = 0;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << "Please input a number: ";
    cin >> num;
    for(int i = 4; i <= num; i += 2)
        for(int j = 2; j <= i / 2; j++)
            if(is_prime(j))
                if(is_prime(i - j)) {
                    cout << i << "=" << j << "+" << i - j << endl;
                    break;
                }
    return 0;
}