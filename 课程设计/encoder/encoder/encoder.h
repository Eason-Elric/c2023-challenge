#ifndef GO_ENCODER_H
#define GO_ENCODER_H

#include <torch/script.h>
#include <torch/torch.h>
#include <string>
#include <tuple>
#include "../../board/boardstate.cpp"

class Encoder {
    public:
        int PlanesNum{};
        int BoardWidth{};
        int BoardHeight{};

    public:
        virtual std::string Name() { return {}; }
        virtual torch::Tensor Encode(BoardState &boardState) { return {}; }
        [[nodiscard]] int EncodePoint(Grid grid) const;
        [[nodiscard]] Grid DecodePoint(int index) const;
        [[nodiscard]] int PointNum() const;
        at::IntArrayRef Shape();
};

inline int Encoder::EncodePoint(Grid grid) const {
    return BoardWidth * (grid.Row - 1) + (grid.Column - 1);
}

inline Grid Encoder::DecodePoint(int Index) const {
    int Row = floor(Index / BoardWidth);
    int Column = Index % BoardWidth;
    return Grid(Row + 1, Column + 1);
}

inline int Encoder::PointNum() const {
    return BoardWidth * BoardHeight;
}

inline at::IntArrayRef Encoder::Shape() {
    return {PlanesNum, BoardWidth, BoardHeight};
}

#endif //GO_ENCODER_H
