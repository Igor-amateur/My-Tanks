// MyTanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h> // for _kbhit()
#include"Battlefield.h"
#include"Timer.h"

int main()
{
	
	srand(unsigned int(time(0)));

	int key(0);//Stores a character from the keyboard
	COORD coord = { 0 };//Coordinate cursor coordinates
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	wchar_t szTITLE[] = L"MY TANK";// title for the console
	SetConsoleTitle(szTITLE); //Set the title
	SetWindowPos(GetConsoleWindow(), 0, 300, 150, 640, 480, SWP_SHOWWINDOW);

	Battlefield battlefield;
	Timer timer;//Displays the time and sets the interrupt period
	CONSOLE_CURSOR_INFO ccf;
	ccf.dwSize = 100;//maximum size
	ccf.bVisible = FALSE;//cursor is not displayed
	SetConsoleCursorInfo(hConsole, &ccf); //Set new cursor properties

 	while (timer.SetInterrupt(TIME_PAUSE))//interrupt loop
	{
		SetConsoleCursorPosition(hConsole, coord);//Set the drawing with (x = 0 and y = 0)

		timer.ShowTime();//Show game time
		if (_kbhit())//if you press a key on the keyboard
		{
			key = _getch();
			if (key == 224)
			{
				key = _getch();//get the next value from the buffer
			}
		}
		battlefield.Show();//show field
		battlefield.refresh(key);//update the field according to the received symbol
	}
    return 0;
}

