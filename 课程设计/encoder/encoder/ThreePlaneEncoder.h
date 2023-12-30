#ifndef GO_THREEPLANEENCODER_H
#define GO_THREEPLANEENCODER_H

#include "encoder.h"

class ThreePlaneEncoder : public Encoder {
    public:
        [[maybe_unused]] explicit ThreePlaneEncoder(int BoardSize);
        std::string Name() override;
        torch::Tensor Encode(BoardState &boardState) override;
};

#endif //GO_THREEPLANEENCODER_H
