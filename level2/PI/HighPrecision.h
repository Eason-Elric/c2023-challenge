#ifndef _STRING_
#define _STRING_
#include<string>
#define maxn 1000010
using namespace std;

void scan(int num__[]) {
    string str = "";
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

#endif
