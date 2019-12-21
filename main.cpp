#include <ncurses.h>
#include <random>
#include "const.h"
#include "field.h"
#include "shape.h"
#include <string>

void ProcessInput(Shape* FirstShape, Shape* SecondShape, Field* tetField, WINDOW* tetWin)
{
	enum Directions {CLOCK = 0, COUNTER_CLOCK};
	int ch = 0;

	for(int i = 0; i < 10; i++)
	{
		ch = getch();
		switch (ch)
		{
			case 'a':
				FirstShape->MoveShape(-1,0);
				break;
			case 'd':
				FirstShape->MoveShape( 1,0);
				break;
			case 's':
				FirstShape->MoveShape( 0,1);
				break;
			case 'q':
				FirstShape->RotateShape(CLOCK);
				break;
			case 'e': 
				FirstShape->RotateShape(COUNTER_CLOCK);
				break;
		}

		if(tetField->CheckCollision(FirstShape))
			FirstShape->Assign(SecondShape);
		else
			SecondShape->Assign(FirstShape);
		
		tetField->DrawField(tetWin);
		SecondShape->DrawShape(tetWin);
		wrefresh(tetWin);
	}
}

int main()
{
	std::random_device Rd;
	std::mt19937 Mersenne(Rd());
	std::uniform_int_distribution<int> Distrib(0,6);

	initscr();
	cbreak();
	noecho();
	refresh();
	curs_set(0); 
	halfdelay(1);	
	
	int Score = 0;
	std::string ScoreStr;

	WINDOW* ScoreWin = newwin(FIELD_HEIGHT -4, FIELD_WIDTH,0,FIELD_WIDTH);	
	WINDOW* tetWin = newwin(FIELD_HEIGHT-4,FIELD_WIDTH,0,0);
	Field tetField;
	Shape FirstShape(0);
	Shape SecondShape(0);

	do
	{
		ScoreStr = std::to_string(Score);

		mvwprintw(ScoreWin, 1, 1, "Score:");
		mvwprintw(ScoreWin, 2, 1, ScoreStr.c_str());
		wrefresh(ScoreWin);
		
		FirstShape.Reload(Distrib(Mersenne));
		SecondShape.Assign(&FirstShape);
		
		while(!tetField.CheckCollision(&FirstShape)){
			ProcessInput(&FirstShape, &SecondShape,&tetField, tetWin);
			SecondShape.Assign(&FirstShape);
			FirstShape.MoveShape(0,1);
			tetField.DrawField(tetWin);
			SecondShape.DrawShape(tetWin);
			wrefresh(tetWin);
		}
		tetField.PutShape(&SecondShape, '#');
		tetField.UpdateRows(&SecondShape);

		Score += tetField.PadFullRows();
	}while(!FirstShape.CheckTop());
	
	halfdelay(50);
	mvwprintw(tetWin, (FIELD_HEIGHT / 2), (FIELD_WIDTH / 2 - 5), "Game over!");
	wrefresh(tetWin);
	getch();
	endwin();

}

