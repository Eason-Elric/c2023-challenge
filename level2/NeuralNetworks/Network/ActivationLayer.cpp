#include "ActivationLayer.h"

inline ActivationLayer::ActivationLayer(int InputDim, ActivationFunction * activationFunction) {
    this -> InputDim = InputDim;
    this -> OutputDim = InputDim;
    if(activationFunction == nullptr)
        this -> activationFunction = new Sigmoid();
    else
        this -> activationFunction = activationFunction;
}

inline void ActivationLayer::Forward() {
    Eigen::VectorXd Data = getForwardInput();
    OutputData = activationFunction -> Function(Data);
}

inline void ActivationLayer::Backward() {
    Eigen::VectorXd Delta = getBackwardInput();
    Eigen::VectorXd Data = getForwardInput();
    OutputDelta = Delta.array() * activationFunction -> FunctionPrime(Data).array();
}

inline void ActivationLayer::Describe() {
    printf("|-- %s", typeid(*this).name());
    printf("  |-- dimensions : (%d, %d)", InputDim, OutputDim);
}
