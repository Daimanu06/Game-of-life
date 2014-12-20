#include "terminalrenderer.h"
#include "cursesrenderer.h"
#include "gameoflife.h"
#include <iostream>

int main(int, char **) {
	namespace gol = gameoflife;
	try{
		//gol::StdoutView view;
		gol::CursesRenderer view;
		gol::GameOfLife game(view);
		game.newgrid();
		game.run();
	} catch (const std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << '\n';
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
	} catch (...) {
		std::cerr << "Fatal error !!" << '\n';
	}

	return 0;
}
