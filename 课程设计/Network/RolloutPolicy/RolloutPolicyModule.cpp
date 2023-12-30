#include "RolloutPolicyModule.h"

inline RolloutPolicyModuleImpl::RolloutPolicyModuleImpl(int InChannels, int OutChannels){
    conv1 = ConvReluBn(InChannels, MidChannels[0], 5, 1);
    conv2 = ConvReluBn(MidChannels[0], MidChannels[1], 3, 1);
    conv3 = ConvReluBn(MidChannels[1], MidChannels[2], 3, 1);
    conv4 = ConvReluBn(MidChannels[2], MidChannels[3], 3, 1);
    flatten = torch::nn::Flatten();
    fc1 = LinearBnRelu(MidChannels[3] * 19 * 19, 512);
    fc2 = torch::nn::Linear(512 , OutChannels * 19 * 19);

    Module -> push_back(conv1);
    Module -> push_back(conv2);
    Module -> push_back(conv3);
    Module -> push_back(conv4);
    Module -> push_back(flatten);
    Module -> push_back(fc1);
    Module -> push_back(fc2);

    Module = register_module("Module", Module);
}

inline torch::Tensor RolloutPolicyModuleImpl::forward(torch::Tensor x){
    x = Module -> forward(x);
    return torch::log_softmax(x, 1);
}
