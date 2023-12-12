#include "SequentialNetwork.h"

#include <utility>

inline SequentialNetwork::SequentialNetwork(Loss * loss) {
    printf("Initialize Network...");
    if(loss == nullptr)
        this -> loss = new MSE();
    else
        this -> loss = loss;
}

inline void SequentialNetwork::Add(Layer * layer) {
    Layers.push_back(layer);
    layer -> Describe();
    if(Layers.size() > 1)
        Layers[Layers.size() - 1] -> Connect(Layers[Layers.size() - 2]);
}

void SequentialNetwork::Train(std::vector<Data> TrainData, int Epochs, int MinBatchSize, double LearningRate,
                              const std::vector<Data>& TestData) {
    int TrainDataNum = (int)TrainData.size();
    for(auto i = 0; i < Epochs; i++) {
        std::shuffle(TrainData.begin(), TrainData.end(), std::mt19937(std::random_device()()));

        for (int j = 0; j < TrainDataNum; j += MinBatchSize) {
            std::vector<Data> MiniBacth;
            MiniBacth.assign(TrainData.begin() + j, TrainData.begin() + j + MinBatchSize);
            TrainBatch(MiniBacth, LearningRate);
        }

        if (!TestData.empty()) {
            int TestNum = (int) TestData.size();
            printf("Epoch %d : %d / %d", i, Evaluate(TestData), TestNum);
        }
        else
            printf("Epoch %d complete", i);
    }
}

void SequentialNetwork::TrainBatch(const std::vector<Data>& MiniBatch, double LearningRate) {
    ForwardBackward(MiniBatch);
    Update(MiniBatch, LearningRate);
}

void SequentialNetwork::ForwardBackward(const std::vector<Data>& MiniBatch) {
    for(auto FirstIter : MiniBatch) {
        Layers[0] -> InputData = FirstIter.first;
        for(auto SecondIter : Layers)
            SecondIter -> Forward();
        Layers[Layers.size() - 1] -> InputDelta = loss -> LossDerivative(Layers[Layers.size() - 1] -> OutputData, FirstIter.second);
        for(auto ThirdIter = Layers.end() - 1; ThirdIter != Layers.begin() - 1; ThirdIter--)
            (*ThirdIter) -> Backward();
    }
}

void SequentialNetwork::Update(const std::vector<Data>& MiniBatch, double LearningRate) {
    LearningRate = LearningRate / (int)MiniBatch.size();
    for(auto Iter : Layers)
        Iter -> UpdateParams(LearningRate);
    for(auto Iter : Layers)
        Iter -> ClearDeltas();
}

Eigen::VectorXd SequentialNetwork::SingleForward(Eigen::VectorXd Vec) {
    Layers[0] -> InputData = std::move(Vec);
    for(auto Iter : Layers)
        Iter -> Forward();
    return Layers[Layers.size() - 1] -> OutputData;
}

int SequentialNetwork::Evaluate(const std::vector<Data>& TestData) {
    int RightNum = 0;
    for(const auto& Iter : TestData)
        if(SingleForward(Iter.first).maxCoeff() == Iter.second.maxCoeff())
            RightNum++;
    return RightNum;
}
