#ifndef GO_AGENT_H
#define GO_AGENT_H

#include "board/boardstate.h"

class Agent {
    public:
        virtual Grid SelectGrid(const BoardState& boardState) ;
};

inline Grid Agent::SelectGrid(const BoardState& boardState) {
    return Grid(1, 1);
}

#endif //GO_AGENT_H
