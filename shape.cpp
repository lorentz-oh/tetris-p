#include <ncurses.h>
#include "const.h"
#include "shape.h"

Shape::Shape(int ShapeIndex)
{
	enum Axes {X = 0, Y};

	for(int i = 0; i<4;i++)
	{ 
		ShapeElms[i][X] = Shapes[ShapeIndex][i][X];
		ShapeElms[i][Y] = Shapes[ShapeIndex][i][Y];
	}
	Coordinates[X] = START_X;
	Coordinates[Y] = START_Y;
} 

void Shape::Reload(int ShapeIndex)
{

	enum Axes {X = 0, Y};

	for(int i = 0; i<4;i++)
	{ 
		ShapeElms[i][X] = Shapes[ShapeIndex][i][X];
		ShapeElms[i][Y] = Shapes[ShapeIndex][i][Y];
	}
	Coordinates[X] = START_X;
	Coordinates[Y] = START_Y;
}

void Shape::MoveShape(int incX, int incY)
{
	enum Axes {X = 0, Y};

	Coordinates[X] += incX;
	Coordinates[Y] += incY;  
}

void Shape::RotateShape(int Direction)
{
	enum Directions {CLOCK = 0, COUNTER_CLOCK};
	enum Axes {X = 0, Y};

	int vx = 0;
	int vy = 0;

	for(int i = 0; i < 4; i++)
	{
		vx = ShapeElms[i][X];
		vy = ShapeElms[i][Y];
		ShapeElms[i][X] = vy;
		ShapeElms[i][Y] = vx;

		if(Direction == CLOCK) 
			ShapeElms[i][Y] *= -1;
		else if(Direction == COUNTER_CLOCK )
			ShapeElms[i][X] *= -1; 
	}

}

void Shape::DrawShape(WINDOW* tetWindow)
{

	enum Axes {X = 0, Y};

	int XAbsCoord = 0;
	int YAbsCoord = 0;

	for(int i = 0; i < 4; i++)
	{
		XAbsCoord = Coordinates[X] + this->ShapeElms[i][X];
		YAbsCoord = Coordinates[Y] + this->ShapeElms[i][Y] - 4;
		mvwaddch(tetWindow,YAbsCoord,XAbsCoord,'#');
	}
}

void Shape::Assign(Shape* p_Shape)
{
	enum Axes {X = 0, Y};
	this->Coordinates[X] = p_Shape->Coordinates[X];
	this->Coordinates[Y] = p_Shape->Coordinates[Y];

	for(int i = 0; i<4; i++)
	{
		this->ShapeElms[i][X] = p_Shape->ShapeElms[i][X];
		this->ShapeElms[i][Y] = p_Shape->ShapeElms[i][Y];
	}
}

int Shape::GetCoord(int Element, int Component)
{
	return int(Coordinates[Component] + ShapeElms[Element][Component]);	 
}


bool Shape::CheckTop(void)
{
	enum Axes {Y = 1};
	
	for(int i = 0; i < 4; i++)
	{
		if(this->GetCoord(i,Y) < 4)
			return true;
	}
	return false;
}
