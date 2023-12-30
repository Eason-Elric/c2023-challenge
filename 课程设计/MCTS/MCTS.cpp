#include <iostream>
#include "MCTS.h"

inline Grid MCTS::SelectGrid(const BoardState& boardState) {
    MCTSNode MCTSRoot = MCTSNode(boardState);
    for(int i = 0; i < RoundsNum; i++) {
        MCTSNode * Node = &MCTSRoot;
        while(Node -> UnvisitedGrid.empty() && !Node -> boardState.IsOver())
            Node = SelectChild(*Node);

        if(!Node -> UnvisitedGrid.empty())
            Node = Node -> AddChildNode();

        GridStatus Winner = SimulateRandomGame(Node -> boardState);

        while(true) {
            Node -> RecordWin(Winner);
            if(Node -> ParentNode != nullptr)
                Node = Node -> ParentNode;
            else
                break;
        }
    }

    Grid BestGrid = Grid(0, 0);
    double BestRate = -1.0;
    for(auto iter : MCTSRoot.ChildrenNode) {
        double ChildRate = iter -> WinningRate((GridStatus)MCTSRoot.boardState.Player);
        if(ChildRate > BestRate) {
            BestRate = ChildRate;
            BestGrid = iter -> boardState.MarkGrid;
        }
    }

    return BestGrid;
}

inline double MCTS::UCTScore(int ParentRolloutNum, int ChildRolloutNum, double WinningRate, double Temperature) {
    double Exploration = sqrt(log(ParentRolloutNum) / ChildRolloutNum);
    return WinningRate + Temperature * Exploration;
}

inline MCTSNode * MCTS::SelectChild(const MCTSNode& Node) {
    double BestScore = -1.0;
    MCTSNode *BestChildNode;

    for(auto iter : Node.ChildrenNode) {
        double CurrentScore =
                UCTScore(Node.RolloutsNum,
                         iter -> RolloutsNum,
                         Node.WinningRate((GridStatus)Node.boardState.Player),
                         sqrt(2));
        if(CurrentScore > BestScore) {
            BestScore = CurrentScore;
            BestChildNode = iter;
        }
    }

    return BestChildNode;
}

inline GridStatus MCTS::SimulateRandomGame(BoardState boardState) {
    random_device Random;
    while(boardState.IsOver())
        if(!boardState.GetLegalGrid().empty())
            boardState.DropGo(boardState.GetLegalGrid()[Random() % boardState.GetLegalGrid().size()]);
        else
            boardState.Player = !boardState.Player;
    return (GridStatus)boardState.GetWinner();
}
