#ifndef _GAMEOFLIFE_
#define _GAMEOFLIFE_

#include "generation.h"
#include <limits>
#include <memory>

namespace gameoflife {

	struct Renderer;

	/**
	 * Controller class.
	 * Manages the world, the view and the game rules.
	 */
	class GameOfLife{
		public:
			/**
			 * Construct an empty grid (only populated with dead cells).
			 */
			GameOfLife(Renderer &);
			~GameOfLife();

		public:
			/**
			 * Create a new world, with random probability for each cell to live.
			 * If the probability is greater than 100, it will be rounded to 100.
			 * @param life_proba probability of a cell to live in percent (0 → no cells are alive, 100 → all cells are alive).
			 */
			void newworld(std::uint8_t life_proba = 50);
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
			struct Impl;
			std::unique_ptr<Impl> pimpl;
	};

}

#endif
