#ifndef GO_ALPHAGOMCTS_H
#define GO_ALPHAGOMCTS_H

#include <cmath>
#include "../agent.h"
#include "../Network/RLPolicy/RLPolicy.cpp"
#include "../Network/RolloutPolicy/RolloutPolicy.cpp"
#include "../Network/SLPolicy/SLPolicy.cpp"

struct AlphaGoNode {
    AlphaGoNode * ParentNode{};
    map<Grid, AlphaGoNode> ChildrenNode;
    int VisitCount{};
    float PriorValue{};
    float Qvalue{};
    float Uvalue{};

    explicit AlphaGoNode(float Probability = 1.0, AlphaGoNode * ParentNode = nullptr) {
        this -> ParentNode = ParentNode;
        this -> PriorValue = Probability;
        this -> VisitCount = 0;
        this -> Qvalue = 0;
        this -> Uvalue = 0;
    }

    Grid SelectChild() {
        auto cmp =
                [](const pair<Grid, AlphaGoNode>& A, const pair<Grid, AlphaGoNode>& B)
                {return (A.second.Qvalue + A.second. Uvalue) > (B.second.Qvalue + B.second.Uvalue); };
        return max_element(ChildrenNode.begin(), ChildrenNode.end(), cmp) -> first;
    }

    void ExpandChild(const map<Grid, float>& Moves) {
        for(auto Move : Moves)
            if (this -> ChildrenNode.find(Move.first) == this -> ChildrenNode.end())
                this -> ChildrenNode.insert({Move.first, AlphaGoNode(Move.second)});
    }

    void UpdateValues(float LeafValue) {
        if(this -> ParentNode != nullptr)
            this -> ParentNode -> UpdateValues(LeafValue);

        VisitCount++;
        Qvalue += LeafValue / (float)VisitCount;

        if(this -> ParentNode != nullptr) {
            float c = 5.0;
            Uvalue = c * (float)sqrt(this -> ParentNode -> VisitCount)
                    * this -> PriorValue / (float)(1 + this -> VisitCount);
        }
    }
};

class AlphaGoMCTS : public Agent {
    private:
        RLPolicy Value = RLPolicy(0);
        RolloutPolicy Rollout = RolloutPolicy(0);
        SLPolicy Agent = SLPolicy(0);

        AlphaGoNode * RootNode;
        float LambdaValue{};
        int Simulations{};
        int Depth{};
        int RolloutLimit{};

    public:
        explicit AlphaGoMCTS(float LambdaValue = 0.5, int Simulations = 1000, int Depth = 50, int RolloutLimit = 100);
        Grid SelectMove(BoardState& Board);

    private:
        static map<Grid, float> GetPredict(map<Grid, float> Moves, BoardState& Board);
        int RolloutPlay(BoardState& Board);
};

#endif //GO_ALPHAGOMCTS_H
