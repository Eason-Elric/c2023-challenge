#ifndef GO_LOSS_H
#define GO_LOSS_H

#include <Eigen/Eigen>

class Loss {
    public:
        virtual double LossFunction(Eigen::VectorXd &Predictions, Eigen::VectorXd &Labels) { return double(); }
        virtual Eigen::VectorXd LossDerivative(Eigen::VectorXd &Predictions, Eigen::VectorXd &Labels) { return {}; }
};

class MSE : public Loss {
    public:
        double LossFunction(Eigen::VectorXd &Predictions, Eigen::VectorXd &Labels) override {
            Eigen::VectorXd Diff = Predictions - Labels;
            return 0.5 * ((Diff.array() * Diff.array()).sum());
        }

        Eigen::VectorXd LossDerivative(Eigen::VectorXd &Predictions, Eigen::VectorXd &Labels) override {
            return Predictions - Labels;
        }
};



#endif //GO_LOSS_H
