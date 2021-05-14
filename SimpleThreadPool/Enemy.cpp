#include "Enemy.h"
#include "Map.h"

Map* Enemy::s_map;
float Enemy::s_movementSpeed = 5.0f;

Enemy::Enemy(Tile* t_spawnTile, float t_size,Tile* t_targetTile)
{
	
	m_pos = t_spawnTile->getPosition();
	m_previousPos = m_pos;
	m_shape.setFillColor(sf::Color::Red);
	m_shape.setPosition(m_pos);
	m_shape.setSize(sf::Vector2f(t_size-5, t_size-5));
	m_shape.setOrigin(t_size / 2, t_size / 2);
	m_shape.setOutlineColor(sf::Color::Black);
	m_shape.setPosition(t_spawnTile->getPosition());
	m_targetTile = t_targetTile;
	setPath();

}

void Enemy::update(sf::Time t_dt)
{
	m_previousPos = m_pos;
	updateMovement(t_dt);
}

Tile* Enemy::getCurrentTile()
{
	return s_map->getTileBasedOnPos(m_pos);
}

void Enemy::render(sf::RenderWindow& t_window, sf::RenderTexture& t_texture)
{
	t_window.draw(m_shape);
	std::vector<sf::Vertex> vertices;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1) && m_pathIndex != -1)
	{
		vertices.push_back(sf::Vertex(m_pos, sf::Color::Blue));

		for (int i = m_pathIndex; i < m_path.size(); i++)
		{
			vertices.push_back(sf::Vertex(m_path[i]->getPosition(), sf::Color::White));
		}

		t_window.draw(&vertices[0], vertices.size(), sf::LinesStrip);
	}
}

sf::Vector2f Enemy::getPos()
{
	return m_pos;
}

sf::Vector2f Enemy::getPreviousPos()
{
	return m_previousPos;
}
void Enemy::setMapPointer(Map* t_map)
{
	s_map = t_map;
}

void Enemy::updateMovement(sf::Time t_dt)
{
	if (Thor::length(m_targetPos - m_pos) <= s_movementSpeed)
	{
		m_pos = m_targetPos;
		m_shape.setPosition(m_pos);
		setVelocity();
	}

	else
	{
		m_pos += m_velocity;
		m_shape.setPosition(m_pos);
	}
}

void Enemy::setPath()
{
	m_pathIndex = -1;

	s_map->aStar(s_map->getTileBasedOnPos(m_pos), s_map->getTileBasedOnPos(m_targetTile->getPosition()), m_path);
	setVelocity();
}

void Enemy::setVelocity()
{
	int maxIndex = m_path.size() - 1;

	if (m_pathIndex < maxIndex)
	{
		//Increase the path index by 1.
		m_pathIndex++;
		{
			m_targetPos = m_path[m_pathIndex]->getPosition();
			m_velocity = Thor::unitVector(m_targetPos - m_pos) * s_movementSpeed;
		}
	}
}
