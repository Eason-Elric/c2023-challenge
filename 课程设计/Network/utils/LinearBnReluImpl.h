#ifndef GO_LINEARBNRELUIMPL_H
#define GO_LINEARBNRELUIMPL_H
#pragma once

#include <torch/script.h>
#include <torch/torch.h>

class LinearBnReluImpl : public torch::nn::Module {
    public:
        explicit LinearBnReluImpl(int in_features, int out_features);
        torch::Tensor forward(torch::Tensor x);

    private:
        torch::nn::Linear linear{ nullptr };
        torch::nn::BatchNorm1d bn{ nullptr };
};
TORCH_MODULE(LinearBnRelu);

#endif //GO_LINEARBNRELUIMPL_H
