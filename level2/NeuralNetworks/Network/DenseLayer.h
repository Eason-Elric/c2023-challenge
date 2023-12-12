#ifndef GO_DENSELAYER_H
#define GO_DENSELAYER_H

#include "Layer.h"

class DenseLayer : protected Layer {
    private:
        Eigen::MatrixXd Weight;
        Eigen::VectorXd Bias;
        Eigen::MatrixXd DeltaWeight;
        Eigen::VectorXd DeltaBias;

    public:
        explicit DenseLayer(int InputDim, int OutputDim);

    private:
        void Forward() override;
        void Backward() override;
        void ClearDeltas() override;
        void UpdateParams(double LearningRate) override;
        void Describe() override;
};

#endif //GO_DENSELAYER_H
