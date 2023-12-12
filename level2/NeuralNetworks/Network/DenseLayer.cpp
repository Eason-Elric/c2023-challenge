#include "DenseLayer.h"

inline DenseLayer::DenseLayer(int InputDim, int OutputDim) {
    this -> InputDim = InputDim;
    this -> OutputDim = OutputDim;

    Weight = Eigen::MatrixXd::Random(OutputDim, InputDim);
    Bias = Eigen::VectorXd::Random(OutputDim, 1);
    Params.push_back(Weight);
    Params.emplace_back(Bias);

    DeltaWeight = Eigen::MatrixXd::Zero(OutputDim, InputDim);
    DeltaBias = Eigen::VectorXd::Zero(OutputDim, 1);
}

inline void DenseLayer::Forward() {
    Eigen::VectorXd Data = getForwardInput();
    OutputData = Weight * Data + Bias;
}

inline void DenseLayer::Backward() {
    Eigen::VectorXd Delta = getBackwardInput();
    Eigen::VectorXd Data = getForwardInput();

    DeltaBias += Delta;
    DeltaWeight += Delta * Data.transpose();
    OutputDelta = Weight.transpose() * Delta;
}

inline void DenseLayer::ClearDeltas() {
    DeltaWeight = Eigen::MatrixXd::Zero(OutputDim, InputDim);
    DeltaBias = Eigen::VectorXd::Zero(OutputDim, 1);
}

inline void DenseLayer::UpdateParams(double LearningRate) {
    Weight = Weight - LearningRate * DeltaWeight;
    Bias = Bias - LearningRate * DeltaBias;
}

inline void DenseLayer::Describe() {
    printf("|-- %s", typeid(*this).name());
    printf("  |-- dimensions : (%d, %d)", InputDim, OutputDim);
}
