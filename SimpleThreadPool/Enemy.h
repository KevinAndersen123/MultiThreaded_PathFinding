#pragma once
#include <SFML/Graphics.hpp>

class Map;
class Tile;

class Enemy
{
public:
	/// <summary>
	/// Constructor for the Enemy object
	/// Sets the start pos,the target tile, the size of the enemy and its outline, and assigns its id
	/// </summary>
	/// <param name="t_spawnTile">Starting tile</param>
	/// <param name="t_size">Size of the rectangle shape</param>
	/// <param name="t_targetTile">Target tile</param>
	/// <param name="t_outline">outline size</param>
	/// <param name="t_id">Id of the enemy</param>
	Enemy(Tile* t_spawnTile, float t_size, Tile* t_targetTile, float t_outline, int t_id);

	//checks if able to move the enemy and if so, update its movement
	void update(sf::Time t_dt); 

	//render the sf::rectangle of the enemy
	void render(sf::RenderWindow& t_window); 

	/// <summary>
	/// Getter method for the enemies position
	/// </summary>
	/// <returns>vector of the enemies current position</returns>
	sf::Vector2f getPos(); 

	/// <summary>
	/// Getter method for the prevoius pos of the enemy
	/// </summary>
	/// <returns></returns>
	sf::Vector2f getPreviousPos(); 


	std::vector<Tile*> m_path;		//Vector of path nodes that the enemy needs to visit to reacht the target.

	/// <summary>
	/// Gets the current tile of the Enemy
	/// </summary>
	/// <returns>Tile the tile the enemy is on</returns>
	Tile* getCurrentTile();

	/// <summary>
	/// Sets the map pointer
	/// </summary>
	/// <param name="t_map"></param>
	static void setMapPointer(Map* t_map);
	/// <summary>
	/// Enables the enemy to start moving
	/// </summary>
	/// <param name="t_move"></param>
	void enableMovement(bool t_move) { m_isAbleToMove = t_move; }
	/// <summary>
	/// Returns the enemies id
	/// </summary>
	/// <returns></returns>
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

