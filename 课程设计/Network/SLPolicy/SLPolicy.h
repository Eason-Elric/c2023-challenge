#ifndef GO_SLPOLICY_H
#define GO_SLPOLICY_H

#include <ATen/ATen.h>
#include "SLPolicyModule.cpp"
#include "../../encoder/encoder/GoDataProcessor.h"

class SLPolicy {
    private:
        torch::Device device = torch::kCPU;
        SLPolicyModule Module = SLPolicyModule{ nullptr };
        GoDataProcessor goDataProcessor = GoDataProcessor("EightPlane", 19);

    public:
        explicit SLPolicy(int GPU_id);
        void Initialize(int InChannels = 8, int OutChannels = 1, const std::string& PretrainedPath = "");
        void LoadWeights(const std::string& Path);
        void Train(int Samples, int Epochs, int BatchSize, float LearningRate);
        map<Grid, float> Predict(BoardState boardState);
};

#endif //GO_SLPOLICY_H
