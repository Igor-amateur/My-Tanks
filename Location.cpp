#include "stdafx.h"
#include "Location.h"

namespace MyTanks
{

	Location::Location(char ch, Status st) noexcept :
		m_symbol(ch),
		m_status(st) {}

	Location::~Location()
	{
	}

	char Location::GetSymbol() const
	{
		return m_symbol;
	}

	Location::Status  Location::GetStatus() const
	{
		return m_status;
	}

	void Location::SetSymbol(char ch)
	{
		m_symbol = ch;
	}

	void  Location::SetStatus(Status st)
	{
		m_status = st;
	}

}