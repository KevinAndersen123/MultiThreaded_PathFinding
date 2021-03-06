// author Kevin Andersen
#include "Game.h"
#include <iostream>

/// <summary>
/// constructor for game setup window and initial state
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1500, 1000, 32 }, "Threadpool Pathfinding" }
{
	m_view.setCenter(sf::Vector2f(750.0f, 500.0f));
	m_view.setSize(sf::Vector2f(1500.0f, 1000.0f));
	m_map.generate30Map();
	Enemy::setMapPointer(&m_map);
	Player::setMapPointer(&m_map);
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
			//create 30x30 map, spawn the player goal and 5 enemies. Add the A* task to the threadpool for each enemy object to give it a path
			if (event.key.code == sf::Keyboard::Num1)
			{
				m_map.generate30Map();
				m_player.spawnPlayer(90.0f,5.0f, *m_map.m_grid[0][0]);
				m_map.setH(m_player.getOccupiedTile());
				m_enemies.clear();
				for (int i = 0; i < 5; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[25][22 + i], 90.0f, m_player.getOccupiedTile(),5.0f,i));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i], &m_map));
				}
			}
			//create 100x100 map, spawn the player goal and 50 enemies. Add the A* task to the threadpool for each enemy object to give it a path
			if (event.key.code == sf::Keyboard::Num2)
			{
				m_map.generate100Map();
				m_player.spawnPlayer(25.0f, 2.0f, *m_map.m_grid[0][0]);
				m_map.setH(m_player.getOccupiedTile());
				m_enemies.clear();

				for (int i = 0; i < 50; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[85][0 + i], 25.0f, m_player.getOccupiedTile(),2.0f,i));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i], &m_map));
				}
			}
			//create 1000x1000 map, spawn the player goal and 500 enemies. Add the A* task to the threadpool for each enemy object to give it a path
			if (event.key.code == sf::Keyboard::Num3)
			{ 
				m_map.generate1000Map();
				m_player.spawnPlayer(2.0f, 0.5f, *m_map.m_grid[0][0]);
				m_map.setH(m_player.getOccupiedTile());
				m_enemies.clear();

				for (int i = 0; i < 500; i++)
				{
					m_enemies.push_back(new Enemy(m_map.m_grid[100][i], 2.0f, m_player.getOccupiedTile(),0.5f,i));
					m_threadPool.addTask(std::bind(&Map::aStar, m_enemies[i]->getCurrentTile(), m_player.getOccupiedTile(), m_enemies[i], &m_map));
				}
			}
		}
		//move around map
		if (event.key.code == sf::Keyboard::W)
		{
			m_view.move(sf::Vector2f(0.0f, -5.0f));
		}
		if (event.key.code == sf::Keyboard::A)
		{
			m_view.move(sf::Vector2f(-5.0f, 0.0f));
		}
		if (event.key.code == sf::Keyboard::S)
		{
			m_view.move(sf::Vector2f(0.0f, 5.0f));
		}
		if (event.key.code == sf::Keyboard::D)
		{
			m_view.move(sf::Vector2f(5.0f, 0.0f));

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

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->update(t_deltaTime); //update the npc's
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.setView(m_view);
	m_window.clear();
	m_map.render(m_window);
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->render(m_window);
	}
	m_player.render(m_window);
	m_window.display();
}
