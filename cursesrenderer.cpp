#include "cursesrenderer.h"
#include "grid.h"
#include "cell.h"
#include <ncursesw/curses.h>
#include <sstream>

namespace gameoflife {

	struct CursesRenderer::Impl {
			///Displays the title of the game, aka “Conway's Game of life” in english, or « Le jeu de la vie de Conway » in French.
			WINDOW *title_win;
			///Displays the world and it's cells.
			WINDOW *play_win;
			///Displays some informations like the current generation number.
			WINDOW *info_win;
			///Displays keyboard shortcuts used to interact with the game.
			WINDOW *ctrl_win;
			///Window where inputs will be redirected.
			WINDOW *input_win;
			Size screen_size;

			//ctor, dtor
			Impl();
			~Impl();

			void draw(const Grid&);
			char waitinput();
			Size availablespace();

			void drawTitle(WINDOW *);
			void drawControl(WINDOW *);
			void drawPlay(WINDOW *, const Grid&);
	}; //CursesRenderer::Impl declaration

	//CursesRenderer::Impl definition
	CursesRenderer::Impl::Impl() {
		setlocale(LC_ALL, "");
		initscr();

		if( !has_colors() ) {
			endwin();
			throw("The terminal must be able to show colors.");
		}

		//Screen dimensions
		Size::size_t scrw, scrh;
		getmaxyx(stdscr, scrh, scrw);
		//TODO: warning with getmaxyx
		screen_size = Size{scrw, scrh-2};

		start_color();
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		init_pair(2, COLOR_GREEN, COLOR_BLACK);

		const Size::size_t WIN_WIDTH = 64, WIN_HEIGHT = 10;
		if(scrw < WIN_WIDTH || scrh < WIN_HEIGHT) {
			endwin();
			std::ostringstream oss;
			oss << "The window is too small.\n";
			oss << "Please resize the window so that it is at least ";
			oss << WIN_WIDTH << "\303\227" << WIN_HEIGHT;
			oss << " (currently " << scrw << "\303\227" << scrh << ")",
					throw(oss.str());
		}

		//Windows init
		//h w y x
		title_win = newwin(     1, scrw,      0, 0);
		play_win  = newwin(scrh-2, scrw,      1, 0);
		ctrl_win  = newwin(     1, scrw, scrh-1, 0);
		input_win = ctrl_win;

		//Other attributes
		noecho();
		curs_set(0); //hide cursor
		keypad(input_win, true); //bind keyboard to a window

		//Draw constant windows, since they won't change in the future
		drawTitle(title_win);
		drawControl(ctrl_win);
	}

	CursesRenderer::Impl::~Impl() {
		delwin(title_win);
		delwin(play_win);
		delwin(ctrl_win);
		endwin();
	}

	char CursesRenderer::Impl::waitinput() {
		return (char)wgetch(input_win);
	}

	Size CursesRenderer::Impl::availablespace() {
		return screen_size;
	}

	void CursesRenderer::Impl::draw(const Grid &grid) {
		drawPlay(play_win, grid);
	}

	void CursesRenderer::Impl::drawTitle(WINDOW *win) {
		wattron(win, COLOR_PAIR(1));
		wattron(win, A_BOLD);
		whline(win, '=', getmaxx(win));
		std::string title = " Conway's Game of Life ";
		mvwprintw(win, 0, (getmaxx(win) - title.size())/2, "%s", title.c_str());
		wrefresh(win);
		wattroff(win, A_BOLD);
		wattroff(win, COLOR_PAIR(1));
	}

	void CursesRenderer::Impl::drawControl(WINDOW *win) {
		wattron(win, COLOR_PAIR(1));
		wattron(win, A_BOLD);
		mvwprintw(win, 0, 0, "Q - Quit    N - New grid    <Space> - Pause / Resume the game");
		wrefresh(win);
		wattroff(win, A_BOLD);
		wattroff(win, COLOR_PAIR(1));
	}

	void CursesRenderer::Impl::drawPlay(WINDOW *win, const Grid &grid) {
		wattron(win, COLOR_PAIR(2));
		wattron(win, A_BOLD);
		for(Size::size_t row = 0; row < grid.height(); row++) {
			for(Size::size_t col = 0; col < grid.width(); col++) {
				mvwprintw(win, row, col, (grid(row, col).isAlive() ? "\342\226\210" : " "));
			}
		}
		wrefresh(win);
		wattroff(win, A_BOLD);
		wattroff(win, COLOR_PAIR(2));
	}
	//CursesRenderer::Impl definition

	//CursesRenderer definition
	CursesRenderer::CursesRenderer() : Renderer(), pimpl(new Impl) {}
	CursesRenderer::~CursesRenderer() {}

	char CursesRenderer::waitinput() {
		return pimpl->waitinput();
	}
	void CursesRenderer::draw(const Grid &grid) {
		pimpl->draw(grid);
	}
	Size CursesRenderer::availablespace() {
		return pimpl->availablespace();
	} //CursesRenderer definition

} //!namespace
