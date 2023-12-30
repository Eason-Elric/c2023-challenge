#pragma once
#include "boardstate.h"

inline void BoardState::DropGo(Grid grid) {
    vector<Grid> AdjacentSameColorGo; // 相邻的同种棋子
    vector<Grid> AdjacentOppositeColorGo; // 相邻的异种棋子
    set<Grid> Liberties_;

    LastGridList = GridList;
    LastMoveState = Play;

    GridList[grid] = (GridStatus)Player;
    MarkGrid = grid;

    for(auto iter : grid.Neighbors()) {
        if(CheckGrid(iter) == None)
            Liberties_.insert(iter); // 若周围没有棋子，增加一口气
        else if(GridList[iter] == Player) {
            auto iter_ = find_if(AdjacentSameColorGo.begin(), AdjacentSameColorGo.end(), FindVector(iter));
            if(iter_ == AdjacentSameColorGo.end())
                AdjacentSameColorGo.push_back(iter);
        }
        else if(GridList[iter] == !Player) {
            auto iter_ = find_if(AdjacentOppositeColorGo.begin(), AdjacentOppositeColorGo.end(), FindVector(iter));
            if(iter_ == AdjacentOppositeColorGo.end())
                AdjacentOppositeColorGo.push_back(iter);
        }
    }

    GoString NewString = GoString((GridStatus)Player, {grid}, Liberties_);

    for(auto iter : AdjacentSameColorGo)
        NewString = NewString.Merged(GoStringList[iter]);

    for(auto iter : NewString.Stones)
        GoStringList[iter] = NewString;

    for(auto iter : AdjacentOppositeColorGo)
        for(auto iter_ : GoStringList[iter].Stones)
            GoStringList[iter_].Liberties.erase(grid);

    for(auto iter : AdjacentOppositeColorGo)
        if(GoStringList[iter].Liberties.empty()){
            GoString TempGoString = GoStringList[iter];
            for(auto iter_ : TempGoString.Stones) {
                for(auto _iter_ : iter_.Neighbors()) {
                    if(CheckGrid(_iter_) == None)
                        continue;
                    if(GoStringList[_iter_].Stones != GoStringList[iter].Stones)
                        for(auto Iter_ : GoStringList[_iter_].Stones)
                            GoStringList[Iter_].Liberties.insert(iter_);
                }
                GridList.erase(iter_);
                GoStringList.erase(iter_);
            }
        }
    Player = !Player;
}

inline void BoardState::PassGo() {
    LastMoveState = Pass;
    Player = !Player;
}

inline bool BoardState::CheckDropGo(Grid grid) {
    BoardState NextBoardState = * this;
    GoString NewGoString;
    map<Grid, GridStatus> NewGridList;
    NextBoardState.DropGo(grid);

    /* Check Suicide */
    NewGoString = NextBoardState.GoStringList[grid];

    /* Check Ko */
    NewGridList = NextBoardState.GridList;

    return !NewGoString.Liberties.empty() && LastGridList != NewGridList;
}

inline int BoardState::CheckGrid(Grid grid) const {
    auto iter = find_if(GridList.begin(), GridList.end(), FindMap(grid));
    if(iter == GridList.end())
        return None;
    return iter -> second;
}

inline bool BoardState::CheckEye(Grid grid) {
    if(CheckGrid(grid) != None)
        return false;

    for(auto iter : grid.Neighbors())
        if(CheckGrid(iter) != None) {
            if (this -> GridList[iter] != this -> Player)
                return false;
        }
        else
            return false;

    int CornerSameColorGoNum = 0;
    for(auto iter : grid.Corners())
        if(CheckGrid(iter) != None)
            if (this -> GridList[iter] == this -> Player)
                CornerSameColorGoNum++;

    return (grid.Corners().size() == 4) ? (CornerSameColorGoNum >= 3) : (CornerSameColorGoNum == grid.Corners().size());
}

inline vector<Grid> BoardState::GetLegalGrid() {
    vector<Grid> LegalGrid;
    for(int Row = 1; Row <=  19; Row++)
        for(int Column = 1; Column <=  19; Column++) {
            Grid grid = Grid(Row, Column);
            if(CheckGrid(grid) == None && CheckDropGo(grid) && !CheckEye(grid))
                LegalGrid.emplace_back(Row, Column);
        }
    return LegalGrid;
}

inline bool BoardState::IsOver() {
    if(this -> GetLegalGrid().empty()){
        BoardState boardState = *this;
        boardState.Player = !boardState.Player;
        if(boardState.GetLegalGrid().empty())
            return true;
    }
    return false;
}

inline int BoardState::GetWinner() {
    int BlackStonesNum = 0;
    int WhiteStonesNum = 0;
    for(int Row = 1; Row <= 19; Row++) {
        for (int Column = 1; Column <= 19; Column++) {
            Grid grid = Grid(Row, Column);
            if (this -> GridList[grid] == Black)
                BlackStonesNum++;
            else if (this -> GridList[grid] == White)
                WhiteStonesNum++;
            else if (this -> GridList[grid] == None) {
                this -> Player = Black;
                if (this -> CheckEye(grid))
                    BlackStonesNum++;
                this -> Player = White;
                if (this -> CheckEye(grid))
                    WhiteStonesNum++;
            }
        }
    }
    return (double)BlackStonesNum >= (double)(WhiteStonesNum + 7.5) ? Black : White;
}
