#include "Tile.h"
#include <iostream>

Tile::Tile()
{
}

Tile::~Tile()
{
}


void Tile::setPosition(sf::Vector2f t_pos)
{
	m_position = t_pos;
}

void Tile::setTileType(TileType t_type)
{
	m_type = t_type;

	if (m_type == TileType::Impassable)
	{
		m_weight = 999;
	}
}

void Tile::setMarked(bool t_mark)
{
	m_marked = t_mark;
}

bool Tile::getMarked() const
{
	return m_marked;
}

TileType Tile::getTileType() const
{
	return m_type;
}

sf::Vector2f Tile::getPosition()
{
	return m_position;
}

void Tile::setWeight(int t_weight)
{
	m_weight = t_weight;
}

float Tile::getWeight() const
{
	return m_weight;
}