#include "stdafx.h"
#include <conio.h>
#include "Battlefield.h"
#include "Wall.h"
#include "Tanks.h"
#include "EnemyTanks.h"


Battlefield::Battlefield()
{
	m_Lives = 5;//initial number of lives
	m_Destroyed = 0;
	m_gameOver = false;
	for (int hei = 0; hei < Height; hei++)
	{
		for (int wid = 0; wid < Width; wid++)
		{
			if (hei == 0 || hei == (Height - 1) || wid == 0 || wid == (Width - 1))
			{
				 mp_battlefield[hei][wid] = new Wall();	// Create a perimeter from the walls
			}
			else
			{
				if (hei == (Height - 2) && wid == (Width / 2))
				{	// place my tank
					POINT startPoint; startPoint.x = wid; startPoint.y = hei;
					mp_battlefield[hei][wid] = new Tanks(Tanks::Direction::Up, Location::Status::Liberator
						, startPoint, this);
				}
				else
				{	// Mark a free field as nullptr
					mp_battlefield[hei][wid] = nullptr;
				}
			}
		}
	}
	int w_pos(0), h_pos(0);// for random coordinates
	for (int i = ((Height-2) * (Width-2)) / 12; i > 0; i--)
	{	// We sow a free field chaotically with walls
		w_pos = RandFor(Width);//get a random number from 1 to Width
		h_pos = RandFor(Height);//get a random number from 1 to Height

		if (mp_battlefield[h_pos][w_pos] == nullptr)
		{//если пусто
			mp_battlefield[h_pos][w_pos] = new Wall();//set the wall
		}
	}
	m_EnemyTanks = 0; //Counter of enemy tanks set to 0
	for (int i = ((Height - 2) * (Width - 2)) / 30; i > 0; i--)
	{	//We sow a free field with enemy tanks
		w_pos = RandFor(Width);//get a random number from 1 to Width
		h_pos = RandFor(Height);//get a random number from 1 to Height

		if (mp_battlefield[h_pos][w_pos] == nullptr)//if empty
		{
			//if not next to the player's tank
			if (h_pos < (Height - 7) && ((w_pos < (Width / 2 - 5)) || ((Width / 2 + 5) < w_pos)))
			{
				
				POINT startPoint; startPoint.x = w_pos; startPoint.y = h_pos;//pack x and y to the point
				//create an enemy tank in the position [h_pos] [w_pos]
				mp_battlefield[h_pos][w_pos] = new EnemyTanks(Tanks::Direction::Up, Location::Status::Invader
					, startPoint, this);
				m_EnemyTanks++;//increase the counter by 1
			}
		}
	}

}


Battlefield::~Battlefield()
{
	for (int hei = 0; hei < Height; hei++)
	{
		for (int wid = 0; wid < Width; wid++)
		{
			if (mp_battlefield[hei][wid] != nullptr)
			{//if there is an object
				delete mp_battlefield[hei][wid];//delete object
			}
		}
	}
}

void Battlefield::Show()
{
	//Output the number of destroyed tanks
	cout << "\tDestroyed tanks = " << m_Destroyed;
	//Output the number of lives
	cout << "\tLives = " << m_Lives;
	//if the game is incomplete
	if (!m_gameOver)
	{
		//display the battlefield
		for (int hei = 0; hei < Height; hei++)
		{
			std::cout << "\n";
			for (int wid = 0; wid < Width; wid++)
			{
				if (mp_battlefield[hei][wid] == nullptr)
				{
					std::cout << ' ';
				}
				else
				{
					std::cout << mp_battlefield[hei][wid]->GetSymbol();
				}
			}
		}
		std::cout  << "\n";
	}
	else
	{//if the game is over
		const char _(0);
		const char M(-37);
		//if the number of lives is 0
		if (m_Lives == 0)
		{
			char G_O[Height][Width] =//array with the image of game_over
			{
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,M,M,M,_,_,_,_,_,_,_,_,M,M,_,_,_,_,_,_,_,M,_,_,_,_,M,_,_,M,M,M,M,M,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,_,_,_,M,_,M,_,_,_,_,_,_,M,M,_,_,_,M,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,M,_,_,M,_,_,_,_,_,M,_,M,_,_,M,_,M,_,_,M,M,M,M,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,M,_,_,_,M,M,_,_,_,_,M,M,M,M,M,_,_,_,_,M,_,_,M,_,M,_,_,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,_,M,_,_,_,M,M,_,_,_,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,M,M,M,_,_,_,M,_,_,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,_,M,_,_,M,M,M,M,M,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,M,M,M,_,_,_,M,_,_,_,_,_,_,M,_,_,M,M,M,M,M,_,_,M,M,M,M,M,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,_,M,_,_,_,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,M,_,_,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,M,M,M,M,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,M,_,_,_,_,_,M,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,_,_,_,M,M,M,M,M,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,_,_,_,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,M,M,M,_,_,_,_,_,_,M,M,_,_,_,_,_,M,M,M,M,M,_,_,M,_,_,_,M,M,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ }
			};
			//display game_over
			for (int hei = 0; hei < Height; hei++)
			{
				std::cout << "\n";
				for (int wid = 0; wid < Width; wid++)
				{
					cout << G_O[hei][wid];
				}
			}
		}
		else if (m_EnemyTanks <= m_Destroyed)
		{//if all enemy tanks are destroyed
			char Y_W[Height][Width] = //an array with the image of you_win
			{
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,_,M,_,_,_,M,M,M,_,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,M,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,M,_,M,_,_,_,M,_,_,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,M,_,_,_,_,_,M,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,_,_,M,M,M,_,_,_,_,_,_,M,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,M,_,_,_,_,M,_,_,M,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,M,M,_,_,_,M,_,_,_,M,_,_,_,M,M,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,M,_,M,_,_,M,_,_,_,_,M,_,_,_,M,_,M,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,M,_,_,M,_,M,_,_,_,_,_,M,_,_,_,M,_,_,M,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,M,_,_,_,M,M,_,_,_,_,_,_,M,_,_,_,M,_,_,_,M,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,M,_,_,_,M,_,_,_,_,M,_,_,_,_,_,_,_,_,_,_,_,_,_,_ },
				{ _,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_ }
			};
			//display the inscription you_win
			for (int hei = 0; hei < Height; hei++)
			{
				std::cout << "\n";
				for (int wid = 0; wid < Width; wid++)
				{
					cout << Y_W[hei][wid];
				}
			}
		}
		this->~Battlefield();//free up memory
		std::cout << "\nFor continue press any key ";
		while (true)
		{
			if (_kbhit())//if you press a key on the keyboard
				exit(0);//then finish
		}
	}
	static int lastStep(5);//after the game is over, five more cycles of the field drawing
	if (m_Lives == 0 || m_EnemyTanks <= m_Destroyed)
	{
		lastStep--;
		if(lastStep <= 0)//if the last cycle
		m_gameOver = true;//end the game
	}
}

void Battlefield::refresh(int & key)
{
	Location * string[Width] = { nullptr };//array of pointers to the moved battlefield objects in a row
	Location * place = nullptr;//a pointer to the moved battlefield object () in the column
	for (int hei = 0; hei < Height; hei++)
	{
		for (int wid = 0; wid < Width; wid++)
		{
			if (mp_battlefield[hei][wid] != nullptr)//exclude empty pointersWe cut off the empty pointers
				if (mp_battlefield[hei][wid]->GetStatus() != Location::Status::Neutral)//Eliminate neutral objects
				{
					if (place != mp_battlefield[hei][wid] //if you have already worked with the object
						&& string[wid] != mp_battlefield[hei][wid])// We can not re-transfer the moved object
					{
						place = string[wid] = mp_battlefield[hei][wid];
						mp_battlefield[hei][wid]->Move(key);
					}
				}
		}
	}
}

Location * Battlefield::GetLocation(int hei, int wid)
{
	return mp_battlefield[hei][wid];//return the object to [hei] [wid]
}

void Battlefield::SetLocation(int hei, int wid, Location * tank)
{
	mp_battlefield[hei][wid] = tank;//set the object to [hei] [wid]
}

int Battlefield::RandFor(int val) 
{
	int n_pos = 1 + (rand() % (val - 2));// generate a random value within 1 - val
	if (n_pos == 0)n_pos++;// if 0 then 1
	if (n_pos == val) n_pos--;//if the maximum value is less than one
	return n_pos;
}

void Battlefield::MinusLive()
{
	if(m_Lives > 0)
	m_Lives--;
}
void Battlefield::PlusDestroyedTank()
{
	m_Destroyed++;
}
