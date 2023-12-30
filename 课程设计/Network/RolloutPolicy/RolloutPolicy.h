#ifndef GO_ROLLOUTPOLICY_H
#define GO_ROLLOUTPOLICY_H

#include "RolloutPolicyModule.cpp"
#include "../../encoder/encoder/GoDataProcessor.cpp"

class RolloutPolicy {
    private:
        torch::Device device = torch::kCPU;
        RolloutPolicyModule Module = RolloutPolicyModule{ nullptr };
        GoDataProcessor goDataProcessor = GoDataProcessor("EightPlane", 19);

    public:
        explicit RolloutPolicy(int GPU_id);
        void Initialize(int InChannels = 8, int OutChannels = 1, const std::string& PretrainedPath = "");
        void LoadWeights(const std::string& Path);
        void Train(int Samples, int Epochs, int BatchSize, float LearningRate);
        map<Grid, float> Predict(BoardState boardState);
};

#endif //GO_ROLLOUTPOLICY_H
