#include "board.h"

inline void Board::CreateBoard() {
    InitWindow(WindowWidth, WindowHeight, Title);

    imgBoard = LoadImage(imgBoardAddress);
    imgLine = DrawLine();
    imgBlack = LoadImage(imgBlackAddress);
    imgWhite = LoadImage(imgWhiteAddress);
    imgBan = LoadImage(imgBanAddress);

    tBoard = LoadTextureFromImage(imgBoard);
    tLine = LoadTextureFromImage(imgLine);
    tBlack = LoadTextureFromImage(imgBlack);
    tWhite = LoadTextureFromImage(imgWhite);
    tBan = LoadTextureFromImage(imgBan);

    SetTargetFPS(60);

    while(!WindowShouldClose()) {
        BeginDrawing();

        DrawTexture(tBoard, 50, 100, WHITE);
        DrawTexture(tLine, 50, 100, WHITE);
        
        DrawGo();

        for(auto iter : boardState.GridList) {
            if(iter.second == Black)
                DrawTexture(tBlack, (iter.first.Row - 1) * LineSpacing + Margins + 27, iter.first.Column * LineSpacing + Margins + 25, WHITE);
            else if(iter.second == White)
                DrawTexture(tWhite, (iter.first.Row - 1) * LineSpacing + Margins + 27, iter.first.Column * LineSpacing + Margins + 25, WHITE);
        }

        if(boardState.MarkGrid.Row != 0 && boardState.MarkGrid.Column != 0) {
            Vector2 MarkGridPosition{(float)((boardState.MarkGrid.Row - 1) * LineSpacing + Margins) + 51, (float)((boardState.MarkGrid.Column) * LineSpacing + Margins + 49)};
            DrawCircleV(MarkGridPosition, 7, RED);
        }

        EndDrawing();
    }

    UnloadTexture(tBoard);
    UnloadTexture(tLine);
    UnloadTexture(tBlack);
    UnloadTexture(tWhite);

    UnloadImage(imgBoard);
    UnloadImage(imgLine);
    UnloadImage(imgBlack);
    UnloadImage(imgWhite);

    CloseWindow();
}

inline Image Board::DrawLine() const {
    Color backColor = {0, 0, 0, 0};
    Image imgLine_ = GenImageColor(BoardWidth,BoardHeight,backColor);

    // 棋盘竖线
    for(int i = 0; i <  19; i++)
        ImageDrawLineEx(&imgLine_, LineSpacing * i + Margins, Margins, LineSpacing * i + Margins, BoardHeight - Margins, 1, BLACK);

    // 棋盘横线
    for(int i = 0; i <  19; i++)
        ImageDrawLineEx(&imgLine_, Margins, LineSpacing * i + Margins, BoardWidth - Margins, LineSpacing * i + Margins, 1, BLACK);

    // 星位
    for(int i = 3; i <= 16; i += 6)
        for(int j = 3; j <= 16; j += 6) {
            ImageDrawPointEx(&imgLine_, LineSpacing * i + Margins, LineSpacing * j + Margins, 6, BLACK);
            ImageDrawPointEx(&imgLine_, LineSpacing * i + Margins, LineSpacing * j + Margins, 6, BLACK);
            ImageDrawPointEx(&imgLine_, LineSpacing * i + Margins, LineSpacing * j + Margins, 6, BLACK);
        }

    Font font = LoadFont(R"(fonts\ebrima.ttf)");

    // 绘制行坐标
    for(int i = 0; i <  19; i++) {
        char Text[2] = {((i < 'I' - 'A') ? (char)('A' + i) : (char)('A' + 1 + i)), '\0'};
        ImageDrawTextEx(&imgLine_, font, Text, {(float)(Margins + LineSpacing * i - 5), (float)(Margins - 34)}, 25,  1, BLACK);
        ImageDrawTextEx(&imgLine_, font, Text, {(float)(Margins + LineSpacing * i - 5), (float)(BoardHeight - Margins + 14)}, 25,  1, BLACK);
    }

    // 绘制列坐标
    for(int i = 18; i >= 0; i--) {
        if(i > 9){
            char Text[] = {(char)('1' + 18 - i), '\0'};
            ImageDrawTextEx(&imgLine_, font, Text, {(float)(Margins - 30), (float)(Margins + (LineSpacing - 0.5) * i - 5)}, 25,  0, BLACK);
            ImageDrawTextEx(&imgLine_, font, Text, {(float)(BoardWidth - Margins + 20), (float)(Margins + (LineSpacing - 0.5) * i - 5)}, 25,  0, BLACK);
        }
        else{
            char Text[] = {'1', (char)('0' + 9 - i), '\0'};
            ImageDrawTextEx(&imgLine_, font, Text, {(float)(Margins - 35), (float)(Margins + (LineSpacing - 0.5) * i - 5)}, 25,  0, BLACK);
            ImageDrawTextEx(&imgLine_, font, Text, {(float)(BoardWidth - Margins + 15), (float)(Margins + (LineSpacing - 0.5) * i - 5)}, 25,  0, BLACK);
        }
    }

    return imgLine_;
}

inline void Board::DrawGo() {
    Color Transparent = {255, 255, 255, 150};

    Vector2 MousePos;
    Rectangle MouseRange = {(float)(50 + Margins - LineSpacing / 2.0 + 5), (float)(100 + Margins - LineSpacing / 2.0 + 5),
                         (float)(BoardWidth - 2 * Margins + LineSpacing - 10), (float)(BoardHeight - 2 * Margins + LineSpacing - 10)};
    int CurrentGesture;

    CurrentGesture = GetGestureDetected();
    MousePos = GetTouchPosition(0);

    int MousePosX = (int)round(MousePos.x / 52) * LineSpacing - 20;
    int MousePosY = (int)round(MousePos.y / 52) * LineSpacing - 22;

    Grid CurrentGrid = Grid((int)((MousePosX - Margins) / LineSpacing) + 1, (int)((MousePosY - Margins) / LineSpacing));

    if(CheckCollisionPointRec(MousePos, MouseRange) && CurrentGesture != GESTURE_TAP && boardState.CheckGrid(CurrentGrid) == None) {
        if(boardState.CheckDropGo(CurrentGrid)) {
            if(boardState.Player == Black)
                DrawTexture(tBlack, MousePosX, MousePosY, Transparent);
            else if(boardState.Player == White)
                DrawTexture(tWhite, MousePosX, MousePosY, Transparent);
        }
        else
            DrawTexture(tBan, MousePosX, MousePosY, WHITE);
    }
    else if(CheckCollisionPointRec(MousePos, MouseRange) && CurrentGesture == GESTURE_TAP && boardState.CheckGrid(CurrentGrid) == None) {
        if(boardState.CheckDropGo(CurrentGrid))
            boardState.DropGo(CurrentGrid);
        else
            DrawTexture(tBan, MousePosX, MousePosY, WHITE);
    }

    /* test */

    else if(!CheckCollisionPointRec(MousePos, MouseRange) && CurrentGesture == GESTURE_TAP) {
        Grid grid = agent -> SelectGrid(boardState);
        //if(grid != Grid(0, 0))
        boardState.DropGo(grid);
        //else if(grid == Grid(0, 0))
            //boardState.Pass(grid);
    }
}
