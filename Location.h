#pragma once
class Location
{
public:
	enum class Status { Neutral = 0, Invader = 1, Liberator = 2, Shell_Invader = 3, Shill_Liberator = 4 };

	Location(char ch, Status st);
	virtual ~Location();
	virtual void Move(int&) = 0;
	virtual bool LastLife() = 0;
	char GetSymbol() const;
	Status  GetStatus() const;
	void SetSymbol(char ch);
	void  SetStatus(Status st);
private:
	char m_symbol;
	Status m_status;
};

