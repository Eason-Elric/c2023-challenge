#include <iostream>
#include "ConstData.h"
#include "RandomMap.h"
#include "Archive.h"
#include "Move.h"
using namespace std;

int CHOOSEMODE = 0, CHOOSESAVE = 0, Level = 1, Step = 0;

void ChooseMode();
void PrintMap();
void ChooseSave();
void GameOperation();

int main() {
    //ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ReadScore();
    while(1){
        ChooseMode();
        switch (CHOOSEMODE) {
            case 1: {
                jump:
                memset(Map, 0, sizeof(Map));
                ReadArchive(Level);
                PrintMap();
                GameOperation();
                End.clear();
                Start.clear();
                Level++;
                system("cls");
                memset(Map, 0, sizeof(Map));
                ReadArchive(Level);
                for(int i = 0; i <= MapSize + 1; i++)
                    for(int j = 0; j <= MapSize + 1; j++)
                        if(Map[i][j] != 0)
                            goto jump;
                system("cls");
                GotoPos(0, 0);
                cout << "Congratulate!\nYou cleared the customs!\n";
                Level = 1;
                system("pause");
                system("cls");
                break;
            }
            case 2: {
                int SaveMap[MAXSIZE][MAXSIZE] = {0};
                CreateMap();
                memcpy(SaveMap, Map, sizeof(Map));
                PrintMap();
                ChooseSave();
                if(CHOOSESAVE == 1)
                    SaveArchive(SaveMap);
                system("cls");
                PrintMap();
                GameOperation();
                break;
            }
            default:{
                SaveScore();
                exit(0);
            }
        }
    }
    return 0;
}

void ChooseMode(){
    cout << "--------------" << endl;
    cout << "1: Level Mode" << endl;
    cout << "2: Random Mode" << endl;
    cout << "3: Exit" << endl;
    cout << "--------------" << endl;
    cout << "Please choose: ";
    cin >> CHOOSEMODE;
    system("cls");
}

void PrintMap(){
    for(int i = 0; i <= MapSize + 1; i++){
        for(int j = 0; j <= MapSize + 1; j++) {
            if(Map[i][j] == PLAYER){
                cout << (char)0xa7 << (char)0xb0;
                Player.x = i;
                Player.y = j;
            }
            else if (Map[i][j] == BOX)
                cout << "#";
            else if (Map[i][j] == END)
                cout << "x";
            else if (Map[i][j] == PATH)
                cout << " ";
            else
                cout << (char)0xa8 << (char)0x80; // 输出墙体
        }
        cout << endl;
    }
}

void ChooseSave(){
    cout << "--------------" << endl;
    cout << "1: Save Map" << endl;
    cout << "2: Just play" << endl;
    cout << "--------------" << endl;
    cout << "Please choose: ";
    cin >> CHOOSESAVE;
    system("cls");
}

void GameOperation(){
    GotoPos(Player.y, Player.x);
    while(1){
        Move();
        Step++;
        if(CheckWin()){
            if(Level <= Score.size()){
                if(100 - Step > Score[Level - 1])
                    Score[Level - 1] = 100 - Step;
            }
            else
                Score.push_back(100 - Step);
            system("cls");
            GotoPos(0, 0);
            cout << "Congratulate!\n";
            system("pause");
            system("cls");
            break;
        }
    }
}