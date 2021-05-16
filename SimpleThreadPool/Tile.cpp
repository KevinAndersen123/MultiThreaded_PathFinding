#include "Tile.h"
#include "MapArc.h"
#include <iostream>

Tile::Tile():
	m_isWalkable(true)
{
	m_position = sf::Vector2f{ -20,-20 };
}

sf::Vector2f Tile::getPosition()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_position;
	lock.unlock();
}

void Tile::setIsOccupied(bool t_isOccupied)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isOccupied = t_isOccupied;
	lock.unlock();
}

bool Tile::getIsOccupied()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_isOccupied;
	lock.unlock();
}

void Tile::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_tileShape.setPosition(m_position);
}

bool Tile::getIsWalkable()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_isWalkable;
	lock.unlock();
}

void Tile::setPathCost(float t_newCost,int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_pathCosts[t_enemyID] = t_newCost;
	lock.unlock();
}

void Tile::setHeuristicCost(float t_newHeuristic)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_heuristicCost = t_newHeuristic;
	lock.unlock();
}

void Tile::setIsWalkable(bool t_isWalkable)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isWalkable = t_isWalkable;
	if (t_isWalkable)
	{
		m_costMultiplier = 1;
	}
	else
	{
		m_costMultiplier = 100;
	}
	lock.unlock();
}

float Tile::getPathCost(int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_pathCosts.count(t_enemyID) == 1)
	{
		return m_pathCosts[t_enemyID];
	}
	else
	{
		return std::numeric_limits<float>::max();
	}
	lock.unlock();
}

float Tile::getHeuristicCost()
{
	std::unique_lock<std::mutex> lock(m_mutex);
	return m_heuristicCost;
	lock.unlock();
}

// ----------------------------------------------------------------
//  Name:           getArc
//  Description:    This finds the arc in the current node that
//                  points to the node in the parameter.
//  Arguments:      The node that the arc connects to.
//  Return Value:   A pointer to the arc, or 0 if an arc doesn't
//                  exist from this to the specified input node.
// ----------------------------------------------------------------
MapArc* Tile::getArc(Tile* node)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	auto iter = m_arcList.begin();
	auto endIter = m_arcList.end();
	MapArc* arc = 0;

	// find the arc that matches the node
	for (; iter != endIter && nullptr == arc; ++iter)
	{
		if ((*iter).node() == node)
		{
			arc = &((*iter));
		}
	}

	// returns nullptr if not found
	return arc;
	lock.unlock();
}

// ----------------------------------------------------------------
//  Name:           addArc
//  Description:    This adds an arc from the current node pointing
//                  to the first parameter, with the second parameter 
//                  as the weight.
//  Arguments:      First argument is the node to connect the arc to.
//                  Second argument is the weight of the arc.
//  Return Value:   None.
// ----------------------------------------------------------------
void Tile::addArc(Tile* node, float weight)
{
	// Create a new arc.
	MapArc a;
	a.setNode(node);
	a.setWeight(weight);
	// Add it to the arc list.
	m_arcList.push_back(a);
}

void Tile::render(sf::RenderWindow& t_window)
{
	if (m_isWalkable)
	{
		m_tileShape.setFillColor(sf::Color::Green);
	}
	else
	{
		m_tileShape.setFillColor(sf::Color(255, 0, 0, 100));
	}
	t_window.draw(m_tileShape);
}

std::list<MapArc> const& Tile::arcList() const
{
	return m_arcList;
}

bool Tile::marked( int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_isMarked.count(t_enemyID) == 1)
	{
		return m_isMarked[t_enemyID];
	}
	else
	{
		return false;
	}
	lock.unlock();
}

Tile* Tile::previous( int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	if (m_previousTiles.count(t_enemyID) == 1)
	{
		return m_previousTiles[t_enemyID];
	}
	else
	{
		return nullptr;
	}
	lock.unlock();
}

void Tile::setMarked(bool mark, int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isMarked[t_enemyID] = mark;
	lock.unlock();
}

void Tile::setPrevious(Tile* previous, int t_enemyID)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_previousTiles[t_enemyID] = previous;
	lock.unlock();
}
