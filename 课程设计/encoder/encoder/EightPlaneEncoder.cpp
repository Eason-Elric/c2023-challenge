#include "EightPlaneEncoder.h"

inline EightPlaneEncoder::EightPlaneEncoder(int BoardSize) {
    this -> BoardWidth = BoardSize;
    this -> BoardHeight = BoardSize;
    this -> PlanesNum = 8;
}

inline std::string EightPlaneEncoder::Name() {
    return "EightPlane";
}

inline torch::Tensor EightPlaneEncoder::Encode(BoardState &boardState) {
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

                if(boardState.GoStringList[grid].Liberties.size() == 1)
                    BoardTensor[3, Row, Column] = 1;
                else if(boardState.GoStringList[grid].Liberties.size() == 2)
                    BoardTensor[4, Row, Column] = 1;
                else if(boardState.GoStringList[grid].Liberties.size() == 3)
                    BoardTensor[5, Row, Column] = 1;
                else if(boardState.GoStringList[grid].Liberties.size() > 3)
                    BoardTensor[6, Row, Column] = 1;
            }

            BoardTensor[7, boardState.MarkGrid.Row, boardState.MarkGrid.Column] = 1;
        }
    return BoardTensor;
}