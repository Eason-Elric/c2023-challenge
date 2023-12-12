#ifndef GO_LAYER_H
#define GO_LAYER_H

#include <vector>
#include <Eigen/Eigen>

class Layer {
    public:
        /* 参数 */
        std::vector<Eigen::MatrixXd> Params;

        /* 维度 */
        int InputDim;
        int OutputDim;

        /* 连接层 */
        Layer * Previous = nullptr;
        Layer * Next = nullptr;

        /* 前向传递数据 */
        Eigen::VectorXd InputData;
        Eigen::VectorXd OutputData;

        /* 反向传递数据 */
        Eigen::VectorXd InputDelta;
        Eigen::VectorXd OutputDelta;

    public:
        void Connect(Layer * layer);
        [[nodiscard]] Eigen::VectorXd getForwardInput() const;
        [[nodiscard]] Eigen::VectorXd getBackwardInput() const;

        /* 虚函数 */
        virtual void Forward() { ; }
        virtual void Backward() { ; }
        virtual void ClearDeltas() { ; }
        virtual void UpdateParams(double LearningRate) { ; }
        virtual void Describe() { ; }
};

#endif //GO_LAYER_H
