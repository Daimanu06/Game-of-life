#ifndef _GRID_
#define _GRID_

#include "size.h"
#include <memory>

namespace gameoflife {

	class Cell;

	/**
	 * Internally uses a grid with a few more neutral (aka dead) cells around it.
	 * This is done to simplify algortihms and stability.
	 * However, the user of this class will not be aware of the existence of theses "border" cells.
	 * Consequently, all the functions will return a grid as if these cells didn't exist.
	 */
	class Grid {
		public:
			/**
			 * Constructs a new grid with all cells initially dead.
			 */
			Grid(const Size&);
			Grid(const Grid&);
			~Grid();
			Grid& operator =(const Grid&);

		public:
			///Return the width of the grid.
			Size::size_t width()  const;
			///Return the height of the grid.
			Size::size_t height() const;
			///Return the size of the grid.
			Size         size()   const;

			/**
			 * Returns the cell at the given row and col.
			 * Const version.
			 */
			const Cell& operator()(Size::size_t row, Size::size_t col) const;
			/**
			 * Returns the cell at the given row and col.
			 * Non const version.
			 */
				  Cell& operator()(Size::size_t row, Size::size_t col);

			/**
			 * Returns the amount of cells alive around the cell at row / col.
			 */
			std::uint8_t cells_alive_around(Size::size_t row, Size::size_t col) const;

		private:
			class Impl;
			std::unique_ptr<Impl> pimpl;
	};

}

#endif
