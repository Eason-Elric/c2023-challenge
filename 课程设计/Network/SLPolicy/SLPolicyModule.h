#ifndef GO_SLPOLICYMODULE_H
#define GO_SLPOLICYMODULE_H

#include <torch/script.h>
#include <torch/torch.h>
#include "../utils/ConvReluBnImpl.cpp"
#include "../utils/LinearBnReluImpl.cpp"

class SLPolicyModuleImpl : public torch::nn::Module {
    public:
        explicit SLPolicyModuleImpl(int InChannels = 8, int OutChannels = 1);
        torch::Tensor forward(torch::Tensor x);

    private:
        int MidChannels = 192;
        torch::nn::Sequential Module{ nullptr };
        torch::nn::Flatten flatten{ nullptr };
        ConvReluBn conv1{ nullptr };
        ConvReluBn conv2{ nullptr };
        ConvReluBn conv3{ nullptr };
};
TORCH_MODULE(SLPolicyModule);

#endif //GO_SLPOLICYMODULE_H
