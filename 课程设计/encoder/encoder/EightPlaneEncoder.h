#ifndef GO_EIGHTPLANEENCODER_H
#define GO_EIGHTPLANEENCODER_H

#include "encoder.h"

class EightPlaneEncoder : public Encoder  {
    public:
        [[maybe_unused]] explicit EightPlaneEncoder(int BoardSize);
        std::string Name() override;
        torch::Tensor Encode(BoardState &boardState) override;
};


#endif //GO_EIGHTPLANEENCODER_H
