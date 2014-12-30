#include "main.h"
#include "terminalrenderer.h"
#include "cursesrenderer.h"
#include "gameoflife.h"
#include <iostream>
#include <algorithm>

int main(int argc, char **argv) {
	try{
		arguments_hub(argc, argv);
	} catch (const std::out_of_range& e) {
		std::cerr << "Error: " << e.what() << ".\n";
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << ".\n";
	} catch (const std::string& str) {
		std::cerr << "Error: " << str << ".\n";
	} catch (const char* str) {
		std::cerr << "Error: " << str << ".\n";
	} catch (...) {
		std::cerr << "Fatal error!" << '\n';
	}
	return 0;
}

void start_game(gameoflife::Renderer &renderer) {
	namespace gol = gameoflife;

	gol::GameOfLife game(renderer);
	game.newworld();
	game.run();
}

void arguments_hub(int argc, char *argv[]) {
	std::string exename = argv[0];
	exename = exename.substr(exename.find_last_of("/")+1);

	int it = 0;
	while(it < argc) {
		std::string arg = argv[it];
		if(arg.at(0) == '-') {
			if( arg == "-h" || arg == "--help" ) {
				print_help(exename);
				return;
			}
			if( arg == "-v" || arg == "--version" ) {
				print_version(exename);
				return;
			}
			if( arg == "-r" || arg == "--renderer" ) {
				if(it >= argc - 1)
					throw("a parameter must be supplied with the options -r or --renderer");
				std::string nextarg = argv[it+1];
				std::transform(nextarg.begin(), nextarg.end(), nextarg.begin(), ::tolower);
				if(nextarg.at(0) == '-')
					throw("an option can't follow a -r or --renderer option");
				//todo: -r=curses OK?

				if(nextarg == "terminal") {
					gameoflife::TerminalRenderer r;
					start_game(r);
					return;
				}
				if(nextarg == "curses") {
					gameoflife::CursesRenderer r;
					start_game(r);
					return;
				}

				throw("no valid value provided to -r or --renderer option\nReminder: valid values are {terminal|curses}");
			}
			throw(std::string("incorrect option ") + argv[it]);
		}
		it++;
	}
	gameoflife::CursesRenderer r;
	start_game(r);
}

void print_help(const std::string &exename) {
	std::cout <<
		"Usage: " + exename + " [options]\n\n"
		"Implementation of the Conway's Game of life.\n\n"
		"Options:\n"
		"  -h, --help     print this help\n"
		"  -v, --version  print the version of ugrid\n"
		"  -r, --renderer {terminal,curses}\n"
		"                 select how the game is displayed (curses by default).\n\n"
		"Note:\n"
		"This program requires your terminal to be able to print unicode charcaters\n"
	;
}
void print_version (const std::string &exename) {
	std::cout << exename <<
			" 0.3.\n"
			"Written by Emmanuel \"Daïmanu\" Di Clemente.\n";
}
