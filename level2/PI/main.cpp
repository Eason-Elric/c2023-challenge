// Pi / 2 = Σk / (2 * k + 1)...
#include<stdio.h>
#include<time.h>
#include<iostream>
using namespace std;
long long int num = 0;
int reserved_num = 10000, k = 0, temp = 0, outcome_num = 0;
int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    long long int iterate_num = 14 * num / 4;
    int* remainder = new int[iterate_num + 10];
    for(int i = 0; i < iterate_num; i++)
        remainder[i] = reserved_num / 5; // 两边同时乘于2000，将小数转化为整数
    while(iterate_num != 0) {
        temp = 0;
        k = iterate_num;
        while(1) {
            temp += remainder[k] * reserved_num; // 将小数扩大为整数
            remainder[k] =  temp % (2 * k - 1); // 将每一轮余数记录，留到下一轮继续计算
            temp /= 2 * k - 1;
            k--;
            if(k == 0)
                break;
            temp = temp * k; // 计算 k / (2 * k + 1)
        }
        iterate_num -= 14; // 迭代
        printf("%.4d", outcome_num + temp / reserved_num); // 输出上一轮的余数加上这轮的商
        outcome_num = temp % reserved_num;
    }
    cout << endl;
    cout << "Time used " << (double)clock() / CLOCKS_PER_SEC  << "s" << endl;
    delete[] remainder;
    system("pause");
    return 0;
}
// 10000位：0.8s左右
// 100000位：65s左右
//