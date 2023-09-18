#include<bits/stdc++.h>
#define maxn 100010
using namespace std;
int s[maxn] = {0}, seed[maxn] = {0}, a1[maxn] = {0}, a2[maxn] = {0}, a[maxn] = {0}, const_x[maxn] = {0}, temp[maxn] = {0},, tempx[maxn] = {0};
int ans = 0;
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
        for(int i = num__[0]; i > 0; i--)
            cout << num__[i];
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
void high_add(int frist__[], int second__[]) {
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
void single_add(int frist__[], int second__) {
    frist__[1] += second__;
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
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    const_x[0] = 10;
    const_x[1] = 6;
    const_x[2] = 9;
    const_x[3] = 2;
    const_x[4] = 7;
    const_x[5] = 6;
    const_x[6] = 9;
    const_x[7] = 4;
    const_x[8] = 9;
    const_x[9] = 2;
    const_x[10] = 4;
    scan(seed);
    scan(s);
    high_add(a, seed);
    while(compare(a, s) == -1){
        memset(temp, 0 ,sizeof(temp));
        memset(a1, 0 ,sizeof(a1));
        memset(a2, 0 ,sizeof(a2));

        numcpy__(seed, temp, 1);
        single_mult(temp, 213346089);
        single_add(temp, 870413);
        high_div(temp, const_x, a1);
        numcpy__(seed, a1, 1);

        memset(temp, 0, sizeof(temp));

        numcpy__(seed, temp, 1);
        single_mult(temp, 166042049);
        single_add(temp, 598777);
        high_div(temp, const_x, a1);
        numcpy__(temp, a1, 1);

        memset(seed, 0 ,sizeof(seed));
        if(compare(a1, a2) >=0) {
            numcpy__(a1, seed, 1);
            high_add(a, a1);
        }
        else{
            numcpy__(a2, seed, 1);
            high_add(a, a2);
        }
        ans++;
    }
    cout << ans;
    return 0;
}
 