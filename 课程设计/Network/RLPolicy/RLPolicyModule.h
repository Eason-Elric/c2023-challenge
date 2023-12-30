#ifndef GO_RLPOLICYMODULE_H
#define GO_RLPOLICYMODULE_H

#include <torch/script.h>
#include <torch/torch.h>
#include "../utils/ConvReluBnImpl.cpp"
#include "../utils/LinearBnReluImpl.cpp"

class RLPolicyModuleImpl : public torch::nn::Module {
    public:
        explicit RLPolicyModuleImpl(int InChannels = 8, int OutChannels = 1);
        torch::Tensor forward(torch::Tensor x);

    private:
        int MidChannels = 192;
        torch::nn::Sequential Module{ nullptr };
        torch::nn::Flatten flatten{ nullptr };
        ConvReluBn conv1{ nullptr };
        ConvReluBn conv2{ nullptr };
        ConvReluBn conv3{ nullptr };
        LinearBnRelu fc1{ nullptr };
        torch::nn::Linear fc2{ nullptr };
};
TORCH_MODULE(RLPolicyModule);

#endif //GO_RLPOLICYMODULE_H
