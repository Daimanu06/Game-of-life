#include "gameoflife.h"
#include "cell.h"
#include "renderer.h"
#include "size.h"
#include "grid.h"
#include <thread>
#include <random>

namespace gameoflife {

	struct GameOfLife::Impl {
			Renderer &m_view;
			Grid  m_grid;
			bool m_run = false;
			bool m_paused = false;
			Generation m_current_gen = 0;

			Impl(Renderer &);
			~Impl();

			void newgrid(std::uint8_t life_proba = 50);
			void run(const Generation max = std::numeric_limits<Generation>::max());
			void pause();
			void resume();

			void update();
			/**
			 * Transit to the next generation and set is as the current generation.
			 */
			void nextgeneration();
			/**
			 * Draw the grid in the the view provided.
			 */
			void draw();

	}; //GameOfLife::Impl declaration end

	//GameOfLife::Impl definition
	GameOfLife::Impl::Impl(Renderer &view) :
		m_view(view),
		m_grid(view.availablespace())
	{}

	GameOfLife::Impl::~Impl() {}

	void GameOfLife::Impl::newgrid(std::uint8_t life_proba) {
		m_run = false;
		m_current_gen = 0;
		if(life_proba > 100) {
			life_proba = 100;
		}

		//Random engine init
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(life_proba/100.f);

		for(Size::size_t row = 0; row < m_grid.height(); row++) {
			for(Size::size_t col = 0; col < m_grid.width(); col++) {
				m_grid(row, col).setAlive(d(gen));
			}
		}
	}

	/**
	 * Blocking function released when the user requests a stop or when the provided generation count is reached.
	 * Lauches two threads:
	 * #1 updates and draws continuously the grid.
	 * #2 awaits for user's input.
	 */
	void GameOfLife::Impl::run(const Generation max) {
		m_run = true;
		std::thread t1([&]() {
			while(m_run && m_current_gen < max) {
				if(!m_paused) {
					update();
					draw();
				}
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		});
		std::thread t2([&]() {
			while(m_run) {
				char input = m_view.waitinput();
				m_run = !(input == 'q' || input == 'Q');
				m_paused = m_paused ^ (input == ' ');
			}
		});
		t1.join();
		t2.join();
	}

	void GameOfLife::Impl::pause() {
		m_paused = true;
	}

	void GameOfLife::Impl::resume() {
		m_paused = false;
	}

	void GameOfLife::Impl::update() {
		nextgeneration();
	}

	void GameOfLife::Impl::Impl::nextgeneration() {
		Grid newgrid = m_grid;
		for(Size::size_t row = 0; row < newgrid.height(); row++) {
			for(Size::size_t col = 0; col < newgrid.width(); col++) {
				Cell &newcell = newgrid(row, col);
				Cell  oldcell = m_grid(row, col);
				std::uint8_t neighboors_alive = m_grid.cells_alive_around(row, col);
				newcell.setAlive( (neighboors_alive == 3) || (neighboors_alive == 2 && oldcell.isAlive()) );
			}
		}
		m_grid = std::move(newgrid);
		m_current_gen++;
	}

	void GameOfLife::Impl::draw() {
		m_view.draw(m_grid, m_current_gen);
	}

	//GameOfLife::Impl definition end

	//GameOfLife definition
	GameOfLife::GameOfLife(Renderer &view) :
		pimpl(new Impl(view))
	{}

	GameOfLife::~GameOfLife() {}

	void GameOfLife::newgrid(std::uint8_t life_proba) {
		pimpl->newgrid(life_proba);
	}

	void GameOfLife::run(const Generation max) {
		pimpl->run(max);
	}

	void GameOfLife::pause() {
		pimpl->pause();
	}

	void GameOfLife::resume() {
		pimpl->resume();
	}

}
