#include "ThreePlaneEncoder.h"

inline ThreePlaneEncoder::ThreePlaneEncoder(int BoardSize) {
    this -> BoardWidth = BoardSize;
    this -> BoardHeight = BoardSize;
    this -> PlanesNum = 3;
}

inline std::string ThreePlaneEncoder::Name() {
    return "ThreePlane";
}

inline torch::Tensor ThreePlaneEncoder::Encode(BoardState &boardState) {
    torch::Tensor BoardTensor = torch::zeros(this -> Shape());
    for(int Row = 1; Row <= BoardHeight; Row++)
        for(int Column = 1; Column <= BoardWidth; Column++) {
            Grid grid = Grid(Row, Column);
            if (boardState.CheckGrid(grid) == None)
                BoardTensor[2, Row, Column] = 1;
            else {
                if (boardState.CheckGrid(grid) == Black)
                    BoardTensor[0, Row, Column] = 1;
                else if (boardState.CheckGrid(grid) != White)
                    BoardTensor[1, Row, Column] = 1;
            }
        }
    return BoardTensor;
}



