#include "grid.h"
#include "cell.h"
#include <vector>
#include <stdexcept>
#include <cstdint>

namespace gameoflife {

	/**
	 * Unlinke the Grid class, the Grid::Impl class's functions can manipulate hidden cells.
	 */
	struct Grid::Impl {
			///Size of the grid excluding extra cells. This is the size provided to the user.
			const Size m_size;
			///Real size of the grid including extra cells.
			const Size m_realsize;
			///All the Cells including the neutral ones of the border.
			std::vector<Cell> m_cells;

			Impl(const Size& size);
			Impl(const Grid& other);
			~Impl();

			//Show a part of the grid.
			Size::size_t width()  const;
			Size::size_t height() const;
			Size         size()   const;

			//Allow access to hidden cells.
			const Cell& operator() (const Size::size_t row, const Size::size_t col) const;
				  Cell& operator() (const Size::size_t row, const Size::size_t col);
			
	}; //Grid::Impl declaration end

	//Grid::Impl definition
	Grid::Impl::Impl(const Size& size) :
		m_size     (size),
		m_realsize {static_cast<Size::size_t>(size.width+2), static_cast<Size::size_t>(size.height+2)},
		m_cells    (m_realsize.width * m_realsize.height)
	{}
	Grid::Impl::Impl(const Grid& other) :
		m_size     (other.pimpl->m_size),
		m_realsize (other.pimpl->m_realsize),
		m_cells    (other.pimpl->m_cells)
	{}
	Grid::Impl::~Impl() {}
	Size::size_t Grid::Impl::width() const {
		return m_size.width;
	}
	Size::size_t Grid::Impl::height() const {
		return m_size.height;
	}
	Size Grid::Impl::size() const {
		return m_size;
	}
	const Cell& Grid::Impl::operator() (const Size::size_t row, const Size::size_t col) const {
		if(row > m_realsize.height) throw std::out_of_range("Row out of range.");
		if(col > m_realsize.width ) throw std::out_of_range("Column out of range.");
		return m_cells[(m_realsize.width * row ) + col];
	}

	Cell& Grid::Impl::operator() (const Size::size_t row, const Size::size_t col) {
		if(row > m_realsize.height) throw std::out_of_range("Row out of range.");
		if(col > m_realsize.width ) throw std::out_of_range("Column out of range.");
		return m_cells[(m_realsize.width * row) + col];
	}
	//Grid::Impl definition end

	//Grid definition
	Grid::Grid(const Size& size) :
		pimpl(new Grid::Impl(size))
	{}
	Grid::Grid(const Grid& grid) :
		pimpl(new Grid::Impl(grid))
	{}

	Grid::~Grid() {}

	Grid &Grid::operator =(const Grid& other) {
		pimpl->m_cells = other.pimpl->m_cells;
		return *this;
	}

	Size::size_t Grid::width() const {
		return pimpl->width();
	}

	Size::size_t Grid::height() const {
		return pimpl->height();
	}

	Size Grid::size() const {
		return pimpl->size();
	}

	const Cell &Grid::operator()(Size::size_t row, Size::size_t col) const {
		return (*pimpl)(row+1, col+1);
	}

	Cell &Grid::operator()(Size::size_t row, Size::size_t col) {
		return (*pimpl)(row+1, col+1);
	}

	std::uint8_t Grid::cells_alive_around(Size::size_t row, Size::size_t col) const {
		std::uint8_t alive = 0;
		alive += (*pimpl)(row  , col  ).isAlive(); //top-left
		alive += (*pimpl)(row  , col+1).isAlive(); //top
		alive += (*pimpl)(row  , col+2).isAlive(); //top-right
		alive += (*pimpl)(row+1, col  ).isAlive(); //left
		alive += (*pimpl)(row+1, col+2).isAlive(); //right
		alive += (*pimpl)(row+2, col  ).isAlive(); //bottom-left
		alive += (*pimpl)(row+2, col+1).isAlive(); //bottom
		alive += (*pimpl)(row+2, col+2).isAlive(); //bottom-right
		return alive;
	}
	//Grid definition end

} //namespace end
