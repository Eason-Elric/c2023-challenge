#include "Layer.h"

inline void Layer::Connect(Layer * layer) {
    Previous = layer;
    layer -> Next = this;
}

inline Eigen::VectorXd Layer::getForwardInput() const {
    if(this -> Previous != nullptr)
        return this -> Previous -> OutputData;
    else
        return InputData;
}

inline Eigen::VectorXd Layer::getBackwardInput() const {
    if(this -> Next != nullptr)
        return this -> Next -> OutputDelta;
    else
        return InputDelta;
}
