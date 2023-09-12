#include<iostream>
#include<math.h>
using namespace std;
int num = 0;
bool is_prime(int num__){
    if(num__ <= 1)
        return false;
    if(num__ == 2 || num__ == 3)
        return true;
    if(num__ % 6 != 1 && num__ % 6 != 5)
        return false;
    for(int i = 5; i <= floor(sqrt(num__)); i += 6)
        if(num__ % i == 0 || num__ % (i + 2) == 0)
            return false;
    return true;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    if(is_prime(num))
        cout << "Prime.";
    else
        cout << "Not prime.";
    return 0;
}