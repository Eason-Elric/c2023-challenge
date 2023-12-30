#include "RLPolicyModule.h"

inline RLPolicyModuleImpl::RLPolicyModuleImpl(int InChannels, int OutChannels) {
    conv1 = ConvReluBn(InChannels, MidChannels, 5, 1);
    conv2 = ConvReluBn(MidChannels, MidChannels, 3, 1);
    conv3 = ConvReluBn(MidChannels, OutChannels, 1, 1);
    flatten = torch::nn::Flatten();
    fc1 = LinearBnRelu(OutChannels * 19 * 19, 256);
    fc2 = torch::nn::Linear(256, 1);

    Module -> push_back(conv1);
    for(int i = 2; i < 13; i++) {
        Module -> push_back(conv2);
    }
    Module -> push_back(conv3);
    Module -> push_back(flatten);
    Module -> push_back(fc1);
    Module -> push_back(fc2);

    register_module("RLPolicyModule", Module);
}

inline torch::Tensor RLPolicyModuleImpl::forward(torch::Tensor x) {
    x = Module -> forward(x);
    return torch::tanh(x);
}