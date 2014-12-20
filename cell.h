#ifndef _CELL_
#define _CELL_

namespace gameoflife {

	/**
	 * Represents a cell that maybe alive or dead.
	 */
	class Cell {
		private:
			bool m_isalive = false;

		public:
			Cell(bool isalive = false);
			bool isAlive() const;
			void setAlive(bool);
	};

}

#endif
