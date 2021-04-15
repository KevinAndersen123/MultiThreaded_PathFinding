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
	initGrid();

	m_tile.setSize(sf::Vector2f(19.0f, 19.0f));
	m_tile.setOrigin(9.5f, 9.5f);
	m_tile.setFillColor(sf::Color::Green);
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
				m_gridSize = 30;
				initGrid();
			}
			if (event.key.code == sf::Keyboard::Num2)
			{
				m_gridSize = 100;
				initGrid();
			}
			if (event.key.code == sf::Keyboard::Num3)
			{
				m_gridSize = 1000;
				initGrid();
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

}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.setView(m_view);
	m_window.clear();
	for (int x = 0; x < m_gridSize; x++)
	{
		for (int y = 0; y < m_gridSize; y++)
		{
			m_tile.setPosition(m_tileArray[x][y].getPosition());
			m_window.draw(m_tile);
		}
	}
	m_window.display();
}

void Game::initGrid()
{
	m_tileArray.clear();
	for (int r = 0; r < m_gridSize; r++)
	{
		std::vector<Tile> tileR;
		for (int c = 0; c < m_gridSize; c++)
		{
			Tile tile;
			tile.setPosition(sf::Vector2f(10 + r * 20, 10 + c * 20));
			tileR.push_back(tile);
		}
		m_tileArray.push_back(tileR);
	}
}
