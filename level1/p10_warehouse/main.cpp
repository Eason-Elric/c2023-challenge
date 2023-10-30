#include <iostream>
#include <fstream>

using namespace std;

struct GOOD { // 货物
    string Name;
    int Num;
};

struct NODE { // 链表
    GOOD Good;
    NODE * Pre;
    NODE * Next;
};

NODE * HEAD, * TAIL;
string GoodName;
int GoodNum = 0;
int Choose = 0;

void AddNode();

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    ifstream InGoodList;
    InGoodList.open(R"(C:\Users\56541\CLionProjects\c2023-challenge\level1\p10_warehouse\GoodList.txt)", ios::in);
    while(InGoodList >> GoodName >> GoodNum) {
        AddNode();
        int Length = GoodName.length();
        (TAIL -> Good).Name = (char * ) malloc((Length + 1) * sizeof(char));
        (TAIL -> Good).Name = GoodName;
        (TAIL -> Good).Num = GoodNum;
    }
    InGoodList.close();

    while(true) {
        cout << "----------------------------------" << endl;
        cout << "1: Displays a list of inventories" << endl;
        cout << "2: Inbound shipments" << endl;
        cout << "3: Outbound shipments" << endl;
        cout << "4: Exit" << endl;
        cout << "----------------------------------" << endl;
        cout << "Please choose: ";
        cin >> Choose;
        switch (Choose) {
            case 1: {
                for(NODE * iter = HEAD; iter != nullptr; iter = iter -> Next)
                    cout << (iter -> Good).Name << " " << (iter -> Good).Num << endl;
                break;
            }
            case 2: {
                cout << "Please enter the name and quantity of the goods in the warehouse." << endl;
                cin >> GoodName >> GoodNum;
                bool isFind = false;
                for(NODE * iter = HEAD; iter != nullptr; iter = iter -> Next)
                    if((iter -> Good).Name == GoodName) {
                        (iter -> Good).Num += GoodNum;
                        isFind = true;
                        break;
                    }
                if(!isFind) {
                    AddNode();
                    int Length = GoodName.length();
                    (TAIL -> Good).Name = (char * ) malloc((Length + 1) * sizeof(char));
                    (TAIL -> Good).Name = GoodName;
                    (TAIL -> Good).Num = GoodNum;
                }
                break;
            }
            case 3: {
                cout << "Please enter the name and quantity of the outbound goods." << endl;
                cin >> GoodName >> GoodNum;
                for(NODE * iter = HEAD; iter != nullptr; iter = iter -> Next)
                    if((iter -> Good).Name == GoodName) {
                        (iter -> Good).Num -= GoodNum;
                        if((iter -> Good).Num != 0) {
                            if(!(iter -> Pre))
                                (iter -> Pre) -> Next = iter -> Next;
                            if(!(iter -> Next))
                                (iter -> Next) -> Pre = iter -> Pre;
                            if(iter == HEAD)
                                HEAD = iter -> Next;
                            if(iter == TAIL)
                                TAIL = iter -> Pre;
                            free(iter);
                        }
                        break;
                    }
                break;
            }
            default:
                goto jump;
        }
        getchar();
        system("pause");
        system("cls");
    }
    jump:
    ofstream OutGoodList;
    OutGoodList.open(R"(C:\Users\56541\CLionProjects\c2023-challenge\level1\p10_warehouse\GoodList.txt)", ios::out);
    for(NODE * iter = HEAD; iter != nullptr; iter = iter -> Next)
        OutGoodList << (iter -> Good).Name << " " << (iter -> Good).Num;
    OutGoodList.close();
    return 0;
}

void AddNode() {
    NODE * PreTail = TAIL;
    if(!TAIL)
        HEAD = TAIL = (NODE * ) malloc(sizeof(NODE));
    else {
        TAIL -> Next = (NODE * ) malloc(sizeof(NODE));
        TAIL = TAIL -> Next;
    }
    if(PreTail)
        PreTail -> Next = TAIL;
    TAIL -> Pre = PreTail;
    TAIL -> Next = nullptr;
}