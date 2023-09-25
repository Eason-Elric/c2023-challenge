#include<iostream>
#include<string>
#include<windows.h>
#include<conio.h>
using namespace std;

string str;
bool check = false;
HANDLE hOnt = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Pos;
CONSOLE_SCREEN_BUFFER_INFO screenInfo;

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    Pos.X = Pos.Y = 0;
    GetConsoleScreenBufferInfo(hOnt, &screenInfo);
    cout << "Please input a string:";
    getline(cin, str);
    SetConsoleCursorPosition(hOnt, Pos);
    for(int i = 0; i < 5 ;i++)
        cout << "                                  ";
    while (true) {
        if(Pos.X == 0)
            check = true;
        if (Pos.X == screenInfo.dwSize.X - str.length() + 1) {
            Pos.X--;
            check = false;
        }
        SetConsoleCursorPosition(hOnt, Pos);
        cout << str;
        Sleep(100);
        SetConsoleCursorPosition(hOnt, Pos);
        for (int i = 0; i < str.length(); i++)
            cout << " ";
        if(check)
            Pos.X++;
        else
            Pos.X--;
        if(_kbhit())
            break;
    }
    system("pause");
    return 0;
}