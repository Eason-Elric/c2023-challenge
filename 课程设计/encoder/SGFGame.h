#ifndef GO_SGFGAME_H
#define GO_SGFGAME_H
#pragma once

#include <string>
#include <map>
#include <regex>
#include "../board/gostring.h"

typedef std::map<int, pair<int, Grid>> Kifu;

class SGFGame {
    public:
        explicit SGFGame(const std::string& Content);

    public:
        Kifu kifu;
        int GoNum;
};

#endif //GO_SGFGAME_H
