#include "OnePlaneEncoder.h"

inline OnePlaneEncoder::OnePlaneEncoder(int BoardSize) {
    this -> BoardWidth = BoardSize;
    this -> BoardHeight = BoardSize;
    this -> PlanesNum = 1;
}

inline std::string OnePlaneEncoder::Name() {
    return "OnePlane";
}

inline torch::Tensor OnePlaneEncoder::Encode(BoardState &boardState) {
    torch::Tensor BoardTensor = torch::zeros(this -> Shape());
    int Player = boardState.Player;
    for(int Row = 1; Row <= BoardHeight; Row++)
        for(int Column = 1; Column <= BoardWidth; Column++) {
            Grid grid = Grid(Row, Column);
            if (boardState.CheckGrid(grid) == None)
                continue;
            if (boardState.CheckGrid(grid) == Player)
                BoardTensor[0, Row, Column] = 1;
            else if (boardState.CheckGrid(grid) != Player)
                BoardTensor[0, Row, Column] = -1;
        }
    return BoardTensor;
}
