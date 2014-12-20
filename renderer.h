#ifndef VIEW_H
#define VIEW_H

#include "size.h"

namespace gameoflife {

	class Grid;

	/**
	 * Base class of differents renderers.
	 * A renderer must be able to draw the grid, get user input and provide it's available space.
	 */
	struct Renderer {
			/**
			 * Draw the world winthin the given grid. Must be overriden in subclasses.
			 */
			virtual void draw(const Grid&) = 0;
			/**
			 * Wait for the user input and return it as a character.
			 */
			virtual char waitinput() = 0;
			/**
			 * Return the available space of the window / terminal or whatever.
			 * This will be the maximum space usable to print the grid.
			 */
			virtual Size availablespace() = 0;
	};

}

#endif // VIEW_H
