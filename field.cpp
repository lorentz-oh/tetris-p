#include <ncurses.h>
#include "shape.h"

#include "field.h"

Field::Field()
{
	m_FieldSize = FIELD_WIDTH * FIELD_HEIGHT;

	pm_Field = new char[m_FieldSize]; 
	for(int i = 0; i < m_FieldSize; i++)
	{
		pm_Field[i] = '-';
	}

	pm_RowsCount = new int[FIELD_HEIGHT];
	for(int i = 0; i < FIELD_HEIGHT; i++)
	{
		pm_RowsCount[i] = 0;
	}
}

Field::~Field()
{
	delete [] pm_Field;
	delete [] pm_RowsCount;
}

int Field::GetIndex(int X, int Y)
{
	return Y * FIELD_WIDTH + X;
}

void Field::DrawField(WINDOW* tetWindow)
{
	mvwprintw(tetWindow,0,0,pm_Field+FIELD_WIDTH * 4);
}//4 hidden lines where shapes appear

bool Field::SetChar(int X, int Y, char Character)
{
	int Index = GetIndex(X, Y);
	if(Index > m_FieldSize)
		return false;
	pm_Field[Index] = Character;
	return true;
}

char Field::GetChar(int X, int Y)
{
	int Index = GetIndex(X, Y);
	if(Index > m_FieldSize)
		return '-';
	return pm_Field[Index];
}

int Field::GetSize()
{
	return m_FieldSize;
}

bool Field::CheckCollision(Shape* p_Shape)
{
	int XAbsCoord = 0;
	int YAbsCoord = 0;
	for(int i = 0; i < 4; i++)
	{
		XAbsCoord = p_Shape->GetCoord(i,0);
		YAbsCoord = p_Shape->GetCoord(i,1);
		if(this->GetChar(XAbsCoord, YAbsCoord) == '#')
			return true;
		if(XAbsCoord > FIELD_WIDTH - 1) return true;
		if(XAbsCoord < 0) return true;
		if(YAbsCoord > (FIELD_HEIGHT - 1)) return true;
	}
	return false;
}


bool Field::PutShape(Shape* p_Shape, char Character)
{
	int XAbsCoord = 0;
	int YAbsCoord = 0;
	for(int i = 0; i<4; i++)
	{
		XAbsCoord = p_Shape->GetCoord(i,0);
		YAbsCoord = p_Shape->GetCoord(i,1);
		this->SetChar(XAbsCoord, YAbsCoord, Character);
	}
	return true;
}

void Field::UpdateRows(Shape* p_Shape)
{
	int YCoord = 0;
	for(int i = 0; i < 4; i++)
	{
		YCoord = p_Shape->GetCoord(i, 1);
		pm_RowsCount[YCoord]++;
	}	
}	

void Field::PadRow(int Row)
{
	if(Row > FIELD_HEIGHT) return;
	
	for(int Y = Row; Y > 0; Y--)
	{
		for(int X = 0; X < FIELD_WIDTH; X++)
		{
			char Ch;
			Ch = this->GetChar(X, Y - 1);
			this->SetChar(X, Y, Ch);
		}
	}

	for(int i = Row; i >= 0; i--)
	{
		pm_RowsCount[i] = pm_RowsCount[i - 1];
	}
}

int Field::PadFullRows()
{
	int KilledRows = 0;
	for(int Row = 0; Row < FIELD_HEIGHT;Row++)
	{
		if(pm_RowsCount[Row] >= FIELD_WIDTH)
		{
			this->PadRow(Row);
			KilledRows++;
		}
	}
	return KilledRows;
}
