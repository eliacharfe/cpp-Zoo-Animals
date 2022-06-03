#pragma once
#include "Animal.h"

class Board
{
public:
	Board(); // c-tor
	void allocateBoard();
	void printZoo(std::ostream& ostr);
	void setChar(size_t row, size_t col, const char initial);

private:
	vector < string > m_charBoard;

};

