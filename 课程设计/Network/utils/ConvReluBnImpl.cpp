#pragma once
#include "ConvReluBnImpl.h"

inline ConvReluBnImpl::ConvReluBnImpl(int InputChannel, int OutputChannel, int KernelSize, int Stride) {
    conv = register_module("conv", torch::nn::Conv2d(ConvOptions(InputChannel, OutputChannel, KernelSize, Stride, KernelSize / 2)));
    bn = register_module("bn", torch::nn::BatchNorm2d(OutputChannel));
}

inline torch::Tensor ConvReluBnImpl::forward(torch::Tensor x) {
    x = torch::relu(conv -> forward(x));
    x = bn(x);
    return x;
}
