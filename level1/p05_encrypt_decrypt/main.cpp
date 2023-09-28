#include <iostream>
#include<string>
using namespace std;

string str = "";
int choose__ = 0, num = 0;

void encode(string str__, int n) {
    char c = '\0';
    for(int i = 0; i < str__.length(); i++) {
        c = str__[i];
        if(c >= 'a' && c <= 'z')
            if(c + n % 26 <= 'z')
                str__[i] = (char)(c + n % 26);
            else
                str__[i] = (char)(c + n % 26 - 26);
        else if(c >= 'A' && c <= 'Z')
            if(c + n % 26 <= 'Z')
                str__[i] = (char)(c + n % 26);
            else
                str__[i] = (char)(c + n % 26 - 26);
        else
            str__[i]=c;
    }
    cout << endl << "After encode: " << str__ << endl;
}

void decode(string str__, int n) {
    char c = '\0';
    for(int i = 0; i < str__.length(); i++) {
        c = str__[i];
        if(c >= 'a' && c <= 'z')
            if(c - n % 26 >= 'a')
                str__[i] = (char)(c - n % 26);
            else
                str__[i] = (char)(c - n % 26 + 26);
        else if(c >= 'A' && c <= 'Z')
            if(c - n % 26 >= 'A')
                str__[i] = (char)(c - n % 26);
            else
                str__[i] = (char)(c - n % 26 + 26);
        else
            str__[i] = c;
    }
    cout << endl << "After decode: " << str__ << endl;
}

int main(){
    while(1){
        cout << "-----------------" << endl;
        cout << "1: Encryption" << endl;
        cout << "2: Decryption" << endl;
        cout << "3: Exit" << endl;
        cout << "-----------------" << endl;
        cout << "Please choose: ";
        cin >> choose__;
        cout << endl;
        getchar();
        switch(choose__){
            case 1:
                cout << "Please input strings: ";
                getline(cin, str);
                cout << endl << "Please input number: ";
                cin >> num;
                encode(str, num);
                break;
            case 2:
                cout << "Please input strings: ";
                getline(cin, str);
                cout << endl << "Please input number: ";
                cin >> num;
                decode(str, num);
                break;
            case 3:
                exit(0);
        }
        cout << endl;
    }
}