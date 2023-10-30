#include<iostream>
#include<vector>
using namespace std;
string str;
vector<int> a;
int b = 0;
int main() {
    getline(cin, str);
    for(int i = 0; i < str.size(); i++) {
        if(isdigit(str[i]))
            a.push_back(str[i] - '0');
        else{
            switch (str[i]) {
                case '+':
                    a.push_back(a[a.size() - 2] + a[a.size() - 1]);
                    break;
                case '-':
                    a.push_back(a[a.size() - 2] - a[a.size() - 1]);
                    break;
                case '*':
                    a.push_back(a[a.size() - 2] * a[a.size() - 1]);
                    break;
                case '/':
                    a.push_back(a[a.size() - 2] / a[a.size() - 1]);
                    break;
            }
            a.erase(a.end() - 3);
            a.erase(a.end() - 2);
        }
    }
    cout << *(a.begin());
    return 0;
}
