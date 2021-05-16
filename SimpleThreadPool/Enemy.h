#pragma once
#include <SFML/Graphics.hpp>

class Map;
class Tile;

class Enemy
{
public:
	void update(sf::Time t_dt);
	void render(sf::RenderWindow& t_window);
	sf::Vector2f getPos();
	sf::Vector2f getPreviousPos();
	std::vector<Tile*> m_path;		//Vector of path nodes that the enemy needs to visit to reacht the target.
	Enemy(Tile* t_spawnTile, float t_size, Tile* t_targetTile, float t_outline,int t_id);
	Tile* getCurrentTile();
	std::vector<Tile*> getPath() { return m_path; }
	static void setMapPointer(Map* t_map);
	void enableMovement(bool t_move) { m_isAbleToMove = t_move; }
	int getID();
private:
	bool m_once = false;
	bool m_isAbleToMove = false;
	void setVelocity();
	void updateMovement(sf::Time t_dt);
	sf::Vector2f m_velocity;
	sf::Vector2f m_targetPos;
	Tile* m_targetTile;
	static Map* s_map;				//Pointer to the map 
	bool m_isWalkable = false;
	sf::Vector2f m_pos;				//The current position that the object is in.
	sf::Vector2f m_previousPos;		//The previous position of the object.
	static float s_movementSpeed;		//The speed at which the enemy moves around each frame.
	sf::RectangleShape m_shape;		
	int m_pathIndex{ -1 };				//The current index of the node in the path.
	int m_id = 0;
};

