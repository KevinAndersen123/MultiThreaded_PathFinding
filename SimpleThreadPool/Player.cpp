#include "Player.h"
#include "Map.h"

Map* Player::s_map;

Player::Player()
{

}

void Player::spawnPlayer(float t_size, float t_outline, Tile& t_spawnTile)
{
    m_shape.setSize(sf::Vector2f(t_size, t_size));
    m_shape.setOrigin(t_size / 2, t_size / 2);
    m_shape.setOutlineThickness(t_outline);
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setPosition(t_spawnTile.getPosition());
    t_spawnTile.setIsWalkable(false);
}

Tile* Player::getOccupiedTile()
{
    return s_map->getTileBasedOnPos(m_shape.getPosition());
}

void Player::setMapPointer(Map* t_map)
{
    s_map = t_map;
}

void Player::render(sf::RenderWindow& t_window)
{
    t_window.draw(m_shape);
}
