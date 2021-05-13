// author Kevin Andersen
#include "Game.h"
#include <iostream>

/// <summary>
/// constructor for game setup window and initial state
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1000, 1000, 32 }, "Lab 6" }
{
	m_view.setCenter(sf::Vector2f(500.0f, 500.0f));
	m_view.setSize(sf::Vector2f(1000.0f, 1000.0f));
	m_map.setupTiles();
}

/// <summary>
/// destructor for game class
/// </summary>
Game::~Game()
{

}

/// <summary>
/// main method for game executes the main game loop
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{

		sf::Vector2f m_mousePos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_window.close();
			}			
			if (event.key.code == sf::Keyboard::Num1)
			{
				m_map.generateSmallMap();
				m_player.spawnPlayer();
				m_map.setHeuristicCost(m_player.getOccupiedTile());
				m_enemies.clear();

				for (int i = 0; i < 5; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[25][19 + i], 90.0f));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i]));
				}
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				m_map.generateMediumMap();
				m_player.spawnPlayer();
				m_map.setHeuristicCost(m_player.getOccupiedTile());
				m_enemies.clear();

				for (int i = 0; i < 50; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[90][20 + i], 25.0f));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i]));
				}
			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				m_map.generateLargeMap();
				m_player.spawnPlayer();
				m_map.setHeuristicCost(m_player.getOccupiedTile());
				m_enemies.clear();

				for (int i = 0; i < 100; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[900][500 + i], 2.0f));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i]));
				}
			}

			if (event.key.code == sf::Keyboard::W)
			{
				m_view.move(sf::Vector2f(0.0f, -1.0f));
			}
			if (event.key.code == sf::Keyboard::A)
			{
				m_view.move(sf::Vector2f(-1.0f, 0.0f));
			}
			if (event.key.code == sf::Keyboard::S)
			{
				m_view.move(sf::Vector2f(0.0f, 1.0f));
			}
			if (event.key.code == sf::Keyboard::D)
			{
				m_view.move(sf::Vector2f(1.0f, 0.0f));

			}
			if (event.key.code == sf::Keyboard::Z)
			{
				m_view.zoom(1.1);
			}
			if (event.key.code == sf::Keyboard::X)
			{
				m_view.zoom(0.9);
			}
		}
		if (sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	m_map.update(t_deltaTime);
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.setView(m_view);
	m_window.clear();
	m_map.render(m_window);
	m_window.display();
}
