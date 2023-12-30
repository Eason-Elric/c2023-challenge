#ifndef GO_BOARDSTATE_H
#define GO_BOARDSTATE_H
#pragma once

#include <map>
#include <raylib.h>
#include "gostring.h"

enum MoveState {
    Pass = 0, Play, Resign
};

class BoardState {
    public:
        /* 棋子 */
        Grid MarkGrid;
        map<Grid, GridStatus> GridList;
        map<Grid, GridStatus> LastGridList;
    
        /* 棋链 */
        map<Grid, GoString> GoStringList;
    
        /* 棋手 */
        int Player = Black;
        
        /* Last Move */
        MoveState LastMoveState;

    public:
        void DropGo(Grid grid);
        void PassGo();
        bool CheckDropGo(Grid grid);
        [[nodiscard]] int CheckGrid(Grid grid) const;
        bool CheckEye(Grid grid);
        vector<Grid> GetLegalGrid();
        bool IsOver();
        int GetWinner();
};


#endif //GO_BOARDSTATE_H
