#include "terminalrenderer.h"
#include "grid.h"
#include "cell.h"
#include <iostream>
#ifdef __gnu_linux__
#include <sys/ioctl.h>
#endif

namespace gameoflife {

	void TerminalRenderer::draw(const Grid &grid, const Generation&) {
		for(Size::size_t row = 0; row < grid.height(); row++) {
			for(Size::size_t col = 0; col < grid.width(); col++) {
				std::cout << (grid(row, col).isAlive() ? 'X' : ' ');
			}
			std::cout << '\n';
		}
		std::cout << std::string(availablespace().width, '=') << '\n';
	}

	char TerminalRenderer::waitinput() {
		return std::cin.get();
	}

	Size TerminalRenderer::availablespace() {
#ifdef __gnu_linux__
		winsize w;
		ioctl(0, TIOCGWINSZ, &w);
		return Size{w.ws_col, w.ws_row};
#else
		return Size{0, 0}; //TODO: get space of terminal for other systems
#endif
	}
}
