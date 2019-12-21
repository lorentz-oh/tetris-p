#pragma once
#include "const.h"
#include "shape.h"
#include <ncurses.h>

class Field
{
private:

 /*Pointer to characters constituting field*/
 char* pm_Field;
 
 /*Size of field in cells.*/
 int m_FieldSize;

 /*The count of free cells in rows*/
 int* pm_RowsCount;
public:

 Field();

 ~Field();

 /*Get index of a cell in the character array,
  *which pm_Field points to*/
 int GetIndex(int X, int Y);

 void DrawField(WINDOW* tetWindow);

 bool SetChar(int X, int Y, char Character);

 char GetChar(int X, int Y);

 int GetSize();

 bool PutShape(Shape* p_Shape, char Character);
 
 bool CheckCollision(Shape* p_Shape);
 /*Update the count of free cells in rows*/
 void UpdateRows(Shape* p_Shape); 

 void PadRow(int Row);
 /*Makes the cells above full rows fall onto them*/
 int PadFullRows();
};
