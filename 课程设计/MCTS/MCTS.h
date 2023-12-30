#ifndef GO_MCTS_H
#define GO_MCTS_H

#include <random>
#include <utility>
#include "../board/boardstate.h"
#include "../agent.h"

struct MCTSNode {
    BoardState boardState;
    MCTSNode * ParentNode{};
    vector<MCTSNode *> ChildrenNode;
    int BlackWinCount{};
    int WhiteWinCount{};
    int RolloutsNum{};
    vector<Grid> UnvisitedGrid;

    MCTSNode() = default;

    explicit MCTSNode(BoardState boardState, MCTSNode * ParentNode = nullptr) {
        this -> boardState = std::move(boardState);
        this -> ParentNode = ParentNode;
        this -> BlackWinCount = 0;
        this -> WhiteWinCount = 0;
        this -> RolloutsNum = 0;
        this -> UnvisitedGrid = this -> boardState.GetLegalGrid();
    }

    MCTSNode * AddChildNode() {
        random_device Random;
        Grid NewGrid = UnvisitedGrid[Random() % UnvisitedGrid.size()];
        BoardState NewBoardState = this -> boardState;
        NewBoardState.DropGo(NewGrid);
        auto * NewNode = new MCTSNode;
        * NewNode = MCTSNode(NewBoardState, this);
        this -> ChildrenNode.push_back(NewNode);
        return NewNode;
    }

    void RecordWin(GridStatus Winner) {
        if(Winner == Black)
            BlackWinCount++;
        else if(Winner == White)
            WhiteWinCount++;
        RolloutsNum++;
    }

    [[nodiscard]] double WinningRate(GridStatus Player) const {
        if(Player == Black)
            return (double)(BlackWinCount) / (double)(RolloutsNum);
        else if(Player == White)
            return (double)(WhiteWinCount) / (double)(RolloutsNum);
        return -1;
    }
};

class MCTS : public Agent {
    private:
        int RoundsNum = 3000; // MCTS模拟次数

    public:
        [[nodiscard]] Grid SelectGrid(const BoardState& boardState) override;

    private:
        static double UCTScore(int ParentRolloutNum, int ChildRolloutNum, double WinningRate, double Temperature);
        static MCTSNode * SelectChild(const MCTSNode& Node);
        static GridStatus SimulateRandomGame(BoardState boardState);
};


#endif //GO_MCTS_H
