#ifndef GO_ROLLOUTPOLICYMODULE_H
#define GO_ROLLOUTPOLICYMODULE_H

#include <torch/script.h>
#include <torch/torch.h>
#include "../utils/ConvReluBnImpl.cpp"
#include "../utils/LinearBnReluImpl.cpp"

class RolloutPolicyModuleImpl : public torch::nn::Module {
    public:
        explicit RolloutPolicyModuleImpl(int InChannels, int OutChannels);
        torch::Tensor forward(torch::Tensor x);

    private:
        int MidChannels[4] = {48, 32, 32, 32};
        torch::nn::Sequential Module{ nullptr };
        torch::nn::Flatten flatten{ nullptr };
        ConvReluBn conv1{ nullptr };
        ConvReluBn conv2{ nullptr };
        ConvReluBn conv3{ nullptr };
        ConvReluBn conv4{ nullptr };
        LinearBnRelu fc1{ nullptr };
        torch::nn::Linear fc2{ nullptr };
};
TORCH_MODULE(RolloutPolicyModule);

#endif //GO_ROLLOUTPOLICYMODULE_H
