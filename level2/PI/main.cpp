// Machin
#include<iostream>
#include<string>
#include<math.h>
#include<time.h>
#include<windows.h>
#define maxn 1000010
using namespace std;
int num = 0;
int frist_num[maxn] = {0}, second_num[maxn] = {0}, outcome_num[maxn] = {0};
int frist_x[maxn] = {0}, second_x[maxn] = {0}, temp_x[maxn] = {0}, const_x[maxn] = {0};
int Pi[maxn] = {0};
bool flag = true;
void scan(int num__[]) {
    string str = "\0";
    getline(cin, str);
    num__[0] = str.length();
    for(int i = 1; i <= num__[0]; i++)
        num__[i] = str[num__[0] - i] - '0';
}
void print(int num__[]) {
    if(!num__[0])
        cout << "0";
    else
        for(int i = num__[0]; i > 0; i--) {
            cout << num__[i];
            if(i == num__[0])
                cout << ".";  // 输出小数点
        }
}
int compare(int frist__[], int second__[]) {
    if(frist__[0] > second__[0])
        return 1;
    if(frist__[0] < second__[0])
        return -1;
    for(int i = frist__[0]; i > 0; i--)
        if(frist__[i] > second__[i])
            return 1;
        else if(frist__[i] < second__[i])
            return -1;
    return 0;
}
void numcpy__(int origin__[], int outcome__[], int temp) {
    for(int i = 1; i <= origin__[0]; i++)
        outcome__[i + temp - 1] = origin__[i];
    outcome__[0] = origin__[0] + temp - 1;
} // 将第1位的数据移到temp位
void add(int frist__[], int second__[]) {
    if(frist__[0] < second__[0])
        frist__[0] = second__[0];
    for(int i = 1; i <= frist__[0]; i++)
        frist__[i] += second__[i];
    for(int i = 1; i <= frist__[0]; i++) {
        frist__[i + 1] += frist__[i] / 10;
        frist__[i] %= 10;
    }
    if(frist__[frist__[0] + 1])
        frist__[0]++;
}
void sub(int frist__[], int second__[]) {
    int flag = compare(frist__, second__);
    if(!flag)
        frist__[0] = 0;
    else if(flag == 1) {
        for(int i = 1; i <= frist__[0]; i++) {
            if(frist__[i] < second__[i]) {
                frist__[i + 1]--;
                frist__[i] += 10;
            }
            frist__[i] -= second__[i];
        }
        while(frist__[frist__[0]] == 0)
            frist__[0]--;
    } else {
        cout << "-";
        for(int i = 1; i <= second__[0]; i++) {
            if(second__[i] < frist__[i]) {
                second__[i + 1]--;
                second__[i] += 10;
            }
            frist__[i] = second__[i] - frist__[i];
        }
        frist__[0] = second__[0];
        while(frist__[frist__[0]] == 0)
            frist__[0]--;
    }
}
void high_mult(int frist__[], int second__[], int outcome__[]) {
    for(int i = 1; i <= frist__[0]; i++)
        for(int j = 1; j <= second__[0]; j++)
            outcome__[i + j - 1] += frist__[i] * second__[j];
    outcome__[0] = frist__[0] + second__[0];
    for(int i = 1; i <= outcome__[0]; i++) {
        outcome__[i + 1] += outcome__[i] / 10;
        outcome__[i] %= 10;
    }
    while(outcome__[outcome__[0]] == 0)
        outcome__[0]--;
}
void single_mult(int frist__[], int second__) {
    if(second__ == 0)
        memset(frist__, 0, sizeof(frist__));
    else {
        for(int i = 1; i <= frist__[0]; i++)
            frist__[i] *= second__;
        for(int i = 1; i <= frist__[0]; i++) {
            frist__[i + 1] += frist__[i] / 10;
            frist__[i] %= 10;
        }
        while(frist__[frist__[0] + 1] > 0) {
            frist__[0]++;
            frist__[frist__[0] + 1] += frist__[frist__[0]] / 10;
            frist__[frist__[0]] %= 10;
        }
    }
}
void high_div(int frist__[], int second__[], int outcome__[]) {
    int temp__[maxn] = {0};
    outcome__[0] = frist__[0] - second__[0] + 1; //frist__ 大于 second__
    for(int i = outcome__[0]; i > 0; i--) {
        memset(temp__, 0, sizeof(temp__));
        numcpy__(second__, temp__, i);
        while(compare(frist__, temp__) >= 0) {
            outcome__[i]++;
            sub(frist__, temp__);
        }
    }
    while(outcome__[0] > 0 && outcome__[outcome__[0]] == 0)
        outcome__[0]--;
}
int signle_div(int frist__[], int second, int outcome__[]) {
    int remainder = 0;
    for(int i = frist__[0]; i > 0; i--) {
        remainder = remainder * 10 + frist__[i];
        outcome__[i] = remainder / second;
        remainder %= second;
    }
    outcome__[0] = frist__[0];
    while(outcome__[0] > 0 && outcome__[outcome__[0]] == 0)
        outcome__[0]--;
    return remainder;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> num;
    const_x[0] = 1;
    const_x[1] = -1;
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
    cout << "Time used " << (double)clock() / CLOCKS_PER_SEC;
    system("pause");
    //add(frist_num, second_num);
    //sub(frist_num, second_num);
    //high_mult(frist_num, second_num, outcome_num);
    //single_mult(frist_num, second);
    //high_div(frist_num, second_num, outcome_num); //frist_num为余数，outcome_num为商
    //signle_div(frist_num, 3, outcome_num);
    return 0;
}