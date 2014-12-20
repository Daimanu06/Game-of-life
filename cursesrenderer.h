#ifndef TUIVIEW_H
#define TUIVIEW_H

#include "renderer.h"
#include <memory>

namespace gameoflife {

	class Grid;

	/**
	 * View using full window, using ncurses lib.
	 * Split the window into 4 frames.
	 */
	class CursesRenderer : public Renderer {
		public:
			CursesRenderer();
			~CursesRenderer();

		public:
			virtual void draw(const Grid&) override;
			virtual char waitinput() override;
			virtual Size availablespace() override;

		private:
			class Impl;
			std::unique_ptr<Impl> pimpl;

	};

}

#endif // TUIVIEW_H
