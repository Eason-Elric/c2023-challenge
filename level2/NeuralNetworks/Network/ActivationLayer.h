#ifndef GO_ACTIVATIONLAYER_H
#define GO_ACTIVATIONLAYER_H

#include <cstdio>
#include "Layer.cpp"
#include "ActivationFunction.h"

class ActivationLayer : protected Layer {
    private:
        /* 激活函数 */
        ActivationFunction * activationFunction;

    public:
        explicit ActivationLayer(int InputDim, ActivationFunction * activationFun = nullptr);

    private:
        void Forward() override;
        void Backward() override;
        void Describe() override;
};


#endif //GO_ACTIVATIONLAYER_H
