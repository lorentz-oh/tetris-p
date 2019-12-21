#pragma once
#include <ncurses.h>

class Shape
{
private:
 int Coordinates[2] = {0,0};

 int ShapeElms[4][2];

public:
 Shape(int ShapeIndex);

 void Reload(int ShapeIndex);

 void MoveShape(int incX, int incY);

 void RotateShape(int Direction);

 void DrawShape(WINDOW* tetWindow);

 void Assign(Shape* p_Shape);

 int GetCoord(int Element, int Component);

 bool CheckTop(void);
};
