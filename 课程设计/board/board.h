#ifndef GO_BOARD_H
#define GO_BOARD_H
#pragma once

#include <cmath>
#include "../rdrawing/rdrawing.h"
#include "boardstate.cpp"
#include "../MCTS/MCTS.cpp"
#include "../MCTS/AlphaGoMCTS.cpp"

class Board {
    private:
        /* 窗口参数 */
        const char * Title = R"(Go)";
        const int WindowWidth = 1500;
        const int WindowHeight = 1200;

        /* 棋盘参数 */
        const int BoardWidth = 1050;
        const int BoardHeight = 1050;
        int Margins = 57;
        int LineSpacing = 52;

        /* 图片地址 */
        const char * imgBoardAddress = R"(.\img\broad.png)";
        const char * imgBlackAddress = R"(.\img\black.png)";
        const char * imgWhiteAddress = R"(.\img\white.png)";
        const char * imgBanAddress = R"(.\img\ban.png)";

        /* 图片 */
        Image imgBoard{};
        Image imgLine{};
        Image imgBlack{};
        Image imgWhite{};
        Image imgBan{};

        /* 图层 */
        Texture tBoard{};
        Texture tLine{};
        Texture tBlack{};
        Texture tWhite{};
        Texture tBan{};

        /* 棋子 */
        BoardState boardState;

        /* 代理 */
        Agent * agent = new AlphaGoMCTS();

    public:
        void CreateBoard();

    private:
        [[nodiscard]] Image DrawLine() const;
        void DrawGo();
};

#endif //GO_BOARD_H
