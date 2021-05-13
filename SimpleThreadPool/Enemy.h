#pragma once
#include <SFML/Graphics.hpp>

class Map;
class Tile;

class Enemy
{
public:
	void update(sf::Time t_dt);
	void render(sf::RenderWindow t_window);
	sf::Vector2f getPos();
	sf::Vector2f getPreviousPos();
	Enemy();

private:
	static Map* s_map;				//Pointer to the map 
	bool m_isActive;				//Bool for if the world is active or not.
	bool m_isWalkable;
	sf::Vector2f m_pos;				//The current position that the object is in.
	sf::Vector2f m_previousPos;		//The previous position of the object.
	static float s_movementSpeed;		//The speed at which the enemy moves around each frame.
	sf::CircleShape m_shape;		
	int m_pathIndex{ -1 };				//The current index of the node in the path.
	std::vector<Tile*> m_path;		//Vector of path nodes that the enemy needs to visit to reacht the target.
};

