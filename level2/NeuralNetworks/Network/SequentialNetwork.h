#ifndef GO_SEQUENTIALNETWORK_H
#define GO_SEQUENTIALNETWORK_H

#include <cstdio>
#include <algorithm>
#include <utility>
#include <random>
#include "Layer.h"
#include "Loss.h"

typedef std::pair<Eigen::VectorXd, Eigen::VectorXd> Data;

class SequentialNetwork {
    private:
        std::vector<Layer *> Layers;
        Loss * loss;

    public:
        explicit SequentialNetwork(Loss * loss = nullptr);
        void Add(Layer * layer);
        void Train(std::vector<Data> TrainData, int Epochs, int MinBatchSize, double LearningRate,
                   const std::vector<Data>& TestData);
        void TrainBatch(const std::vector<Data>& MiniBatch, double LearningRate);
        void ForwardBackward(const std::vector<Data>& MiniBatch);
        void Update(const std::vector<Data>& MiniBatch, double LearningRate);
        Eigen::VectorXd SingleForward(Eigen::VectorXd Vec);
        int Evaluate(const std::vector<Data>& TestData);
};

#endif //GO_SEQUENTIALNETWORK_H
