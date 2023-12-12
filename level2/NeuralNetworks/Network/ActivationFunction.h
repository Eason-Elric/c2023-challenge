#ifndef GO_ACTIVATIONFUNCTION_H
#define GO_ACTIVATIONFUNCTION_H

#include <Eigen/Eigen>

class ActivationFunction {
    public:
        virtual double FunctionDouble(double x) { return double(); }
        virtual Eigen::VectorXd Function(Eigen::VectorXd Vec) { return {}; }
        virtual double FunctionPrimeDouble(double x) { return double(); }
        virtual Eigen::VectorXd FunctionPrime(Eigen::VectorXd Vec) { return {}; }
};

class Sigmoid : public ActivationFunction {
    public:
        double FunctionDouble(double x) override {
            return 1.0 / (1.0 + exp(-x));
        }

        Eigen::VectorXd Function(Eigen::VectorXd Vec) override {
            for(int i = 0; i < Vec.size(); i++)
                Vec(i) = FunctionDouble(Vec(i));
            return Vec;
        }

        double FunctionPrimeDouble(double x) override {
            return FunctionDouble(x) * (1.0 - FunctionDouble(x));
        }

        Eigen::VectorXd FunctionPrime(Eigen::VectorXd Vec) override {
            for(int i = 0; i < Vec.size(); i++)
                Vec(i) = FunctionPrimeDouble(Vec(i));
            return Vec;
        }
};

class Tanh : public ActivationFunction {
public:
    double FunctionDouble(double x) override {
        return 2.0 * 1.0 / (1.0 + exp(-(2.0 * x))) - 1;
    }

    Eigen::VectorXd Function(Eigen::VectorXd Vec) override {
        for(int i = 0; i < Vec.size(); i++)
            Vec(i) = FunctionDouble(Vec(i));
        return Vec;
    }

    double FunctionPrimeDouble(double x) override {
        return 1.0 - (FunctionDouble(x) * FunctionDouble(x));
    }

    Eigen::VectorXd FunctionPrime(Eigen::VectorXd Vec) override {
        for(int i = 0; i < Vec.size(); i++)
            Vec(i) = FunctionPrimeDouble(Vec(i));
        return Vec;
    }
};

#endif //GO_ACTIVATIONFUNCTION_H
