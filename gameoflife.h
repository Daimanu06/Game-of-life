#ifndef _GAMEOGLIFE_
#define _GAMEOFLIFE_

#include "size.h"
#include "grid.h"
#include "generation.h"
#include <limits>

namespace gameoflife {

	class Renderer;

	/**
	 * Controller class.
	 * Manages the data (the grid), the view and the game rules.
	 */
	class GameOfLife{
		private:
			Renderer &m_view;
			Grid  m_grid;
			bool m_run = false;
			bool m_paused = false;
			Generation m_current_gen = 0;

		public:
			/**
			 * Construct an empty grid (only populated with dead cells).
			 */
			GameOfLife(Renderer &);
			~GameOfLife();

		public:
			/**
			 * Create a new grid, with random probability for each cell to live.
			 * If the probability is greater than 100, it will be rounded to 100.
			 * @param life_proba probability of a cell to live in percent (0 → no cells are alive, 100 → all cells are alive).
			 */
			void newgrid(std::uint8_t life_proba = 50);
			/**
			 * Update and render the game "max" times.
			 * By default the game will run until it reaches the 2³²th (≈ 4⋅10⁹) generation.
			 */
			void run(const Generation max = std::numeric_limits<Generation>::max());
			/**
			 * Pause the game.
			 */
			void pause();
			/**
			 * Resume the game if it was paused.
			 */
			void resume();

		private:
			void update();
			/**
			 * Transit to the next generation and set is as the current generation.
			 */
			void nextgeneration();
			/**
			 * Draw the grid in the the view provided.
			 */
			void draw();
	};

}

#endif
