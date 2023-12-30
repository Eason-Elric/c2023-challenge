#ifndef GO_GETRLPOLICYDATA_H
#define GO_GETRLPOLICYDATA_H

#include "../SLPolicy/SLPolicy.cpp"
#include "../../board/boardstate.cpp"
#include "../../encoder/encoder/encoder.h"

const string SavePath = R"(../../SelfPlayingData/kifu)";
const int SelfPlayNum = 1000;
const string Mark = "abcdefghijklmnopqrs";

Encoder encoder = Encoder();
SLPolicy SLAgent = SLPolicy(0);

inline string GridtoSGF(Grid grid) {
    string sgf;
    sgf.append(Mark.substr(grid.Column - 1, 1));
    sgf.append(Mark.substr(grid.Row - 1, 1));
    return sgf;
}

inline void GetRLPolicyData() {
    SLAgent.LoadWeights(R"(../Module/SLPolicy.pt)");

    ofstream fout;
    fout.open(SavePath);

    for(int i = 0; i < SelfPlayNum; i++) {
        BoardState boardState;
        string kifu;
        while(boardState.IsOver()) {
            if (!boardState.GetLegalGrid().empty()) {
                map<Grid, float> Moves = SLAgent.Predict(boardState);
                vector<Grid> LegalGrid = boardState.GetLegalGrid();
                for(auto Move : Moves) {
                    auto iter = find_if(LegalGrid.begin(), LegalGrid.end(), FindVector(Move.first));
                    if(iter == LegalGrid.end())
                        Moves.erase(Move.first);
                }
                Grid Move = max_element(Moves.begin(), Moves.end(),
                                        [](const pair<Grid, float>& A, const pair<Grid, float>& B)
                                        {return A.second < B.second; }) -> first;
                boardState.DropGo(Move);
                kifu.append(boardState.Player == Black ? "W" : "B");
                kifu.append("[" + GridtoSGF(boardState.MarkGrid) + "]");
            }
            else
                boardState.Player = !boardState.Player;
        }

        kifu.insert(0, boardState.GetWinner() == Black ? "0 ;" : "1 ;");
        fout << kifu << endl;
    }
    fout.close();
}

#endif //GO_GETRLPOLICYDATA_H
