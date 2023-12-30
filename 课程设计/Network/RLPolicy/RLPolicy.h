#ifndef GO_RLPOLICY_H
#define GO_RLPOLICY_H

#include <torch/script.h>
#include <torch/torch.h>
#include "RLPolicyModule.cpp"
#include "RLPolicyModule.h"
#include "../../encoder/encoder/GoDataProcessor.h"

class RLPolicy {
    private:
        torch::Device device = torch::kCPU;
        RLPolicyModule Module = RLPolicyModule{ nullptr };
        GoDataProcessor goDataProcessor = GoDataProcessor("EightPlane", 19);

    public:
        explicit RLPolicy(int GPU_id);
        void Initialize(int InChannels = 8, int OutChannels = 1, const std::string& PretrainedPath = "");
        void LoadWeights(const std::string& Path);
        void Train(int Samples, int Epochs, int BatchSize, float LearningRate);
        float Predict(BoardState boardState);
};

#endif //GO_RLPOLICY_H
