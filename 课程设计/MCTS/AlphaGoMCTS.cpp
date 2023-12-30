#include "AlphaGoMCTS.h"

inline AlphaGoMCTS::AlphaGoMCTS(float LambdaValue, int Simulations, int Depth, int RolloutLimit) {
    Value.LoadWeights(R"(../Module/RLPolicy.pt)");
    Rollout.LoadWeights(R"(../Module/RolloutPolicy.pt)");
    Agent.LoadWeights(R"(../Module/SLPolicy.pt)");

    RootNode = new AlphaGoNode();
    LambdaValue = LambdaValue;
    Simulations = Simulations;
    Depth = Depth;
    RolloutLimit = RolloutLimit;
}

inline Grid AlphaGoMCTS::SelectMove(BoardState &Board) {
    for(int i = 0; i < Simulations; i++) {
        BoardState CurrentBoard = Board;
        AlphaGoNode * CurrentNode = RootNode;
        for (int j = 0; j < Depth; j++) {
            if (CurrentNode -> ChildrenNode.empty()) {
                if (CurrentBoard.IsOver())
                    break;
                map<Grid, float> Moves = Agent.Predict(Board);
                Moves = GetPredict(Moves, CurrentBoard);
                CurrentNode -> ExpandChild(Moves);
            }
            Grid Move = CurrentNode -> SelectChild();
            *CurrentNode = CurrentNode -> ChildrenNode[Move];
            CurrentBoard.DropGo(Move);
        }

        float value = Value.Predict(CurrentBoard);
        float rollout = RolloutPlay(CurrentBoard);
        float WeightedValue = (1 - LambdaValue) * value + LambdaValue * rollout;

        CurrentNode -> UpdateValues(WeightedValue);
    }

    Grid Move = max_element(RootNode -> ChildrenNode.begin(), RootNode -> ChildrenNode.end(),
                    [](const pair<Grid, AlphaGoNode>& A, const pair<Grid, AlphaGoNode>& B)
                    {return A.second.VisitCount < B.second.VisitCount; }) -> first;

    RootNode = new AlphaGoNode();
    RootNode = &(RootNode -> ChildrenNode[Move]);
    RootNode->ParentNode = nullptr;

    return Move;
}

inline map<Grid, float> AlphaGoMCTS::GetPredict(map<Grid, float> Moves, BoardState &Board) {
    vector<Grid> LegalGrid = Board.GetLegalGrid();
    for(auto Move : Moves) {
        auto iter = find_if(LegalGrid.begin(), LegalGrid.end(), FindVector(Move.first));
        if(iter == LegalGrid.end())
            Moves.erase(Move.first);
    }
    return Moves;
}

inline int AlphaGoMCTS::RolloutPlay(BoardState &Board) {
    for(int i = 0; i < RolloutLimit; i++) {
        if(Board.IsOver())
            break;
        auto Moves = Rollout.Predict(Board);
        Moves = GetPredict(Moves, Board);
        Grid Move = max_element(Moves.begin(), Moves.end(),
                                [](const pair<Grid, float>& A, const pair<Grid, float>& B)
                                {return A.second < B.second; }) -> first;
        Board.DropGo(Move);
    }
    return Board.GetWinner() == Board.Player ? 1 : -1;
}
