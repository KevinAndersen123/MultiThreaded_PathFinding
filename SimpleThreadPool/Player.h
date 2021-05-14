#pragma once
#include <SFML/Graphics.hpp>
#include <Tile.h>

class Map;
class Tile;

class Player
{
public:
	Player();
	void spawnPlayer(float t_size, float t_outline, Tile* t_spawnTile);
	Tile* getOccupiedTile();
	sf::RectangleShape m_shape;
	static void setMapPointer(Map* t_map);
	void render(sf::RenderWindow& t_window);
private:
	static Map* s_map;				//Pointer to the map 
};

