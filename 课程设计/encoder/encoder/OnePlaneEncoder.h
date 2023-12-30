#ifndef GO_ONEPLANEENCODER_H
#define GO_ONEPLANEENCODER_H

#include "encoder.h"

class OnePlaneEncoder : public Encoder {
    public:
        [[maybe_unused]] explicit OnePlaneEncoder(int BoardSize);
        std::string Name() override;
        torch::Tensor Encode(BoardState &boardState) override;
};

#endif //GO_ONEPLANEENCODER_H
