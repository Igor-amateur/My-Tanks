// MyTanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Windows.h>
#include <conio.h> // for _kbhit()
#include"Battlefield.h"
#include"Timer.h"

namespace mws //create my workspace
{
	using namespace MyTimer;
	using namespace MyTanks;

	void EndGame(Timer*, Battlefield*);
}



int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	HWND hWind = GetConsoleWindow();
	wchar_t szTITLE[] = L"MY TANK";// title for the console
	SetConsoleTitle(szTITLE); //Set the title
	if (hWind != NULL)
	{
		SetWindowPos(hWind, 0, 300, 150, 450, 360, SWP_SHOWWINDOW);
	}

	if (hConsole != INVALID_HANDLE_VALUE) {

		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 24;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

		CONSOLE_CURSOR_INFO ccf;
		ccf.dwSize = 100;//maximum size
		ccf.bVisible = FALSE;//cursor is not displayed
		SetConsoleCursorInfo(hConsole, &ccf); //Set new cursor properties
	}

	

	
	int key(0);//Stores a character from the keyboard
	COORD coord = { 0 };//Coordinate cursor coordinates
	mws::Battlefield * battlefield(nullptr);
	mws::Timer * timer(nullptr);//Displays the time and sets the interrupt period
	bool continueGame(false);
	srand(unsigned int(time(0)));

	
	while (true)
	{
		
		
		key = 0;//Stores a character from the keyboard
		//COORD coord = { 0 };//Coordinate cursor coordinates
		battlefield = new mws::Battlefield;
		timer = new mws::Timer;//Displays the time and sets the interrupt period
		continueGame = false;

		while (timer->SetInterrupt(TIME_PAUSE))//interrupt loop
		{
			SetConsoleCursorPosition(hConsole, coord);//Set the drawing with (x = 0 and y = 0)

			timer->ShowTime();//Show game time
			if (_kbhit())//if you press a key on the keyboard
			{
				key = _getch();
				if (key == 224)
				{
					key = _getch();//get the next value from the buffer
				}
				if (27 == key)
				{
					mws::EndGame(timer, battlefield);
					exit(0);//then finish
				}
			}
			continueGame = battlefield->Show();//show field
			if (continueGame)
				battlefield->refresh(key);//update the field according to the received symbol
			else
				break;
		}
		mws::EndGame(timer, battlefield);
	}
    return 0;
}

void mws::EndGame(mws::Timer* timer, mws::Battlefield* battlefield)
{
	delete timer;
	timer = nullptr;
	delete battlefield;
	battlefield = nullptr;
	system("cls");
}