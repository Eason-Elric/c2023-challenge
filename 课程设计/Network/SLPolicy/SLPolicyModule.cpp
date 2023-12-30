#include "SLPolicyModule.h"

inline SLPolicyModuleImpl::SLPolicyModuleImpl(int InChannels, int OutChannels) {
    conv1 = ConvReluBn(InChannels, MidChannels, 5, 1);
    conv2 = ConvReluBn(MidChannels, MidChannels, 3, 1);
    conv3 = ConvReluBn(MidChannels, OutChannels, 1, 1);
    flatten = torch::nn::Flatten();

    Module -> push_back(conv1);
    for(int i = 2; i < 12; i++) {
        Module -> push_back(conv2);
    }
    Module -> push_back(conv3);
    Module -> push_back(flatten);
}

inline torch::Tensor SLPolicyModuleImpl::forward(torch::Tensor x) {
    x = Module -> forward(x);
    return torch::log_softmax(x, 1);
}
