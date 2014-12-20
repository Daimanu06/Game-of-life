#include "terminalrenderer.h"
#include "grid.h"
#include "cell.h"
#include <iostream>

namespace gameoflife {

	void TerminalRenderer::draw(const Grid &grid) {
		for(Size::size_t row = 0; row < grid.width(); row++) {
			for(Size::size_t col = 0; col < grid.height(); col++) {
				std::cout << (grid(row, col).isAlive() ? 'X' : ' ') << ' ';
			}
			std::cout << '\n';
		}
	}

	char TerminalRenderer::waitinput() {return 0;}

	Size TerminalRenderer::availablespace() {
		return Size{0, 0}; //TODO: get space of terminal
	}
}
