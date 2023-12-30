#pragma once
#include "LinearBnReluImpl.h"

inline LinearBnReluImpl::LinearBnReluImpl(int in_features, int out_features){
    linear = register_module("linear", torch::nn::Linear(torch::nn::LinearOptions(in_features, out_features)));
    bn = register_module("bn", torch::nn::BatchNorm1d(out_features));
}

inline torch::Tensor LinearBnReluImpl::forward(torch::Tensor x){
    x = torch::relu(linear -> forward(x));
    x = bn(x);
    return x;
}