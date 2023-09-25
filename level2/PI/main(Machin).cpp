// Machin 计算一项得到1.4位有效数字
#include<iostream>
#include<math.h>
#include<time.h>
#include<windows.h>
#include"HighPrecision.h"
#define maxn 1000010
using namespace std;

int num = 0;
int frist_num[maxn] = {0}, second_num[maxn] = {0}, outcome_num[maxn] = {0};
int frist_x[maxn] = {0}, second_x[maxn] = {0}, temp_x[maxn] = {0};
int Pi[maxn] = {0};
bool flag = true;

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    frist_num[0] = second_num[0] = num + 9;
    frist_num[num + 9] = second_num[num + 9] = 1;
    single_mult(frist_num, 4); // x1 * 4
    signle_div(frist_num, 5, frist_x); // x1 // 5
    signle_div(second_num, 239, second_x); // x2 // 239
    numcpy__(frist_x, outcome_num, 1);
    sub(outcome_num, second_x); // out = x1 - x2
    for(int i = 3; i <= 2 * num + 10; i += 2) {
        memset(frist_num, 0, sizeof(frist_num));
        memset(second_num, 0, sizeof(second_num));
        memset(temp_x, 0, sizeof(temp_x));
        signle_div(frist_x, 25, frist_num);
        numcpy__(frist_num, frist_x, 1); // x1 // 25
        signle_div(second_x, 57121, second_num);
        numcpy__(second_num, second_x, 1); // x2 // 57121
        sub(frist_num, second_num); // x = x1 - x2
        signle_div(frist_num, i, temp_x); // x /= i
        if(flag) {
            sub(outcome_num, temp_x);
            flag = false;
        } else {
            add(outcome_num, temp_x); // s += x
            flag = true;
        }
    }
    single_mult(outcome_num, 4); // Pi = s * 4
    signle_div(outcome_num, pow(10, 8), Pi);
    print(Pi);
    cout << endl;
    cout << "Time used " << (double)clock() / CLOCKS_PER_SEC  << "s" << endl;
    system("pause");
    //add(frist_num, second_num);
    //sub(frist_num, second_num);
    //high_mult(frist_num, second_num, outcome_num);
    //single_mult(frist_num, second);
    //high_div(frist_num, second_num, outcome_num); //frist_num为余数，outcome_num为商
    //signle_div(frist_num, 3, outcome_num);
    return 0;
}

// 10000位：8s左右
// 100000位：180s左右
// 1000000位：时间过长