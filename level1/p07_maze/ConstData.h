#ifndef _CONSTNUM_H_
#define _CONSTNUM_H_

// Maze
#define MAXSIZE 10010
#define WALL 0
#define PATH 1

enum Direction{
    Nothing = 0, Up, Down, Left, Right
};

// Move
#define CTRL 0xE0
#define UP 0x48
#define DOWN 0x50
#define LEFT 0x4B
#define RIGHT 0x4D

#endif // _CONSTNUM_H_
