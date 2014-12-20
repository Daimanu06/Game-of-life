#include "cell.h"

namespace gameoflife {

	Cell::Cell(bool isalive) :
		m_isalive(isalive)
	{}

	bool Cell::isAlive() const {
		return m_isalive;
	}

	void Cell::setAlive(bool isAlive) {
		m_isalive = isAlive;
	}

}
