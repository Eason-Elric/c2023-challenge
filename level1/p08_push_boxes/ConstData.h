#ifndef _CONSTNUM_H_
#define _CONSTNUM_H_

// Map
#define MAXSIZE 15

enum MapElement{
    WALL, PATH, BOX, END, PLAYER
};

enum Direction{
    Up = 1, Down, Left, Right
};

// Move
#define CTRL 0xE0
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4B
#define RIGHT 0x4D

#endif // _CONSTNUM_H_
