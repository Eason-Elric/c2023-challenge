#include<iostream>
#include<string.h>
#include<time.h>
#define maxn 10010
using namespace std;
int num = 0, count = 0;
int prime[maxn] = {0};
bool is_prime[maxn];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    memset(is_prime, true, sizeof(is_prime));
    is_prime[1] = false;
    for(int i = 2; i <= num; i++){
        if(is_prime[i])
            prime[count++] = i;
        for(int j = 0; (j < count) && (i * prime[j] <= num); j++){
            is_prime[i * prime[j]] = false;
            if(i % prime[j] == 0)
                break;
        }
    }
    for(int i = 0; i < count; i++)
        cout << prime[i] << " ";
    cout << endl;
    cout << "Time used " << (double)clock() / CLOCKS_PER_SEC;
    return 0;
}