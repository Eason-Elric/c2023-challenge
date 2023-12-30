#ifndef GO_CONVRELUBNIMPL_H
#define GO_CONVRELUBNIMPL_H
#pragma once

#include <torch/script.h>
#include <torch/torch.h>

inline torch::nn::Conv2dOptions ConvOptions(int InPlanes, int OutPlanes, int KernelSize,
                                             int Stride = 1, int Padding = 0, bool WithBias = false) {
    torch::nn::Conv2dOptions ConvOptions = torch::nn::Conv2dOptions(InPlanes, OutPlanes, KernelSize);
    ConvOptions.stride(Stride);
    ConvOptions.padding(Padding);
    ConvOptions.bias(WithBias);
    return ConvOptions;
}

class ConvReluBnImpl : public torch::nn::Module {
    public:
        explicit ConvReluBnImpl(int InputChannel = 3, int OutputChannel = 64, int KernelSize = 3, int Stride = 1);
        torch::Tensor forward(torch::Tensor x);

    private:
        torch::nn::Conv2d conv{ nullptr };
        torch::nn::BatchNorm2d bn{ nullptr };

};
TORCH_MODULE(ConvReluBn);

#endif //GO_CONVRELUBNIMPL_H
