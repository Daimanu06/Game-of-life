#ifndef VIEW_H
#define VIEW_H

#include "size.h"

namespace gameoflife {

	class Grid;

	/**
	 * Base class of differents renderers.
	 * A renderer must be able to draw the grid, get user input and communicate it's available space.
	 */
	struct Renderer {
			/**
			 * Draw the grid. Must be overriden in subclasses.
			 */
			virtual void draw(const Grid&) = 0;
			/**
			 * Wait for the user input and return it as a character.
			 */
			virtual char waitinput() = 0;
			/**
			 * Return the available space of the view.
			 * This space will be the maximum space usable to print the grid.
			 */
			virtual Size availablespace() = 0;
	};

}

#endif // VIEW_H
