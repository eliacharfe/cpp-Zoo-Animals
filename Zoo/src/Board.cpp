#include "Board.h"

Board::Board()
{
	allocateBoard();
}
//------------------------------
void Board::allocateBoard()
{
	m_charBoard.resize(Max::Height);
	for (size_t row = 0; row < m_charBoard.size(); row++) {
		m_charBoard[row].resize(Max::Width);
		for (size_t col = 0; col < Max::Width; col++)
			m_charBoard[row][col] = EMPTY;
	}
}
//----------------------------------
void Board::printZoo(std::ostream& ostr)
{
	for (size_t row = 0; row < Max::Height; row++)
		ostr << m_charBoard[row] << endl;
}
//---------------------------------
void Board::setChar(size_t row, size_t col, const char initial)
{
	m_charBoard[row][col] = initial;
}
