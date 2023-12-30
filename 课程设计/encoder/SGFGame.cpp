#pragma once
#include "SGFGame.h"

inline SGFGame::SGFGame(const std::string& Content) {
    GoNum = 1;
    auto iter = Content.begin();
    auto end = Content.end();
    while (iter != end) {
        iter = std::find(iter, end, ';');
        if (iter != end) {
            iter += 1;
            auto nextIter = std::find(iter, end, ';');
            if (nextIter != end) {
                int Player = *iter == 'B' ? Black : White;
                Grid grid = Grid((int)(*(iter + 2) - 'a' + 1), (int)(*(iter + 3) - 'a' + 1));
                this -> kifu.emplace(GoNum, make_pair(Player, grid));
                GoNum++;
                iter = nextIter;
            }
        }
    }
}