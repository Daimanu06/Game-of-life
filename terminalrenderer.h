#ifndef STDOUTVIEW_H
#define STDOUTVIEW_H

#include "renderer.h"

namespace gameoflife {

	class Grid;

	/**
	 * View using a simple terminal.
	 * Show one grid per generation on the default output (stdout).
	 * @warning Does not work on every platform
	 * @warning To enter a command, you need to type the letter and press <Enter> to validate.
	 */
	struct TerminalRenderer : public Renderer {
			virtual void draw(const Grid&, const Generation&) override;
			virtual char waitinput() override;
			virtual Size availablespace() override;
	};

}

#endif // STDOUTVIEW_H
