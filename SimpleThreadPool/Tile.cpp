#include "Tile.h"
#include "MapArc.h"
#include <iostream>

Tile::Tile(Tile* previous) :
	m_previous(previous),
	m_isWalkable(true)
{
	m_tileShape.setSize(sf::Vector2f(32, 32));
	m_tileShape.setOrigin(16.0f, 16.0f);
	m_tileShape.setOutlineColor(sf::Color::Black);
	m_tileShape.setOutlineThickness(1);
}


sf::Vector2f Tile::getPosition()
{
	return m_position;
}

void Tile::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
	m_tileShape.setPosition(m_position);
}

bool Tile::getIsWalkable()
{
	return m_isWalkable;
}

void Tile::setPathCost(int t_newCost)
{
	m_pathCost = t_newCost;
}

void Tile::setHeuristicCost(int t_newHeuristic)
{
	m_heuristicCost = t_newHeuristic;
}

int Tile::getPathCost()
{
	return m_pathCost;
}

int Tile::getHeuristicCost()
{
	return m_heuristicCost;
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

bool Tile::marked() const
{
	return m_marked;
}

Tile* Tile::previous() const
{
	return m_previous;
}

void Tile::setMarked(bool mark)
{
	m_marked = mark;
}

void Tile::setPrevious(Tile* previous)
{
	m_previous = previous;
}
