#ifndef STDOUTVIEW_H
#define STDOUTVIEW_H

#include "renderer.h"

namespace gameoflife {

	class Grid;

	/**
	 * View using a simple terminal.
	 * Show one grid per generation on the default output (stdout).
	 */
	struct TerminalRenderer : public Renderer {
			virtual void draw(const Grid&) override;
			virtual char waitinput() override;
			virtual Size availablespace() override;
	};

}

#endif // STDOUTVIEW_H
