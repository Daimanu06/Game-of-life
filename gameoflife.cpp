#include "gameoflife.h"
#include "cell.h"
#include "renderer.h"
#include <thread>
#include <random>

namespace gameoflife {

	GameOfLife::GameOfLife(Renderer &view) :
			m_view(view),
			m_grid(view.availablespace())
	{}

	GameOfLife::~GameOfLife() {}

	void GameOfLife::newgrid(std::uint8_t life_proba) {
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
	void GameOfLife::run(const Generation max) {
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

	void GameOfLife::pause() {
		m_paused = true;
	}

	void GameOfLife::resume() {
		m_paused = false;
	}

	void GameOfLife::update() {
		nextgeneration();
	}

	void GameOfLife::nextgeneration() {
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

	void GameOfLife::draw() {
		m_view.draw(m_grid);
	}
}
