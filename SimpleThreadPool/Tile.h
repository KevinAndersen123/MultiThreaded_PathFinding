#pragma once
#include <SFML\Graphics.hpp>
#include <list>
#include <mutex>
class MapArc;

class Tile
{
public:

	Tile();

	/// <summary>
	/// Sets the position of the tile sprite to the passed in position.
	/// </summary>
	/// <param name="t_pos">The position that the position of the tile is to be set to</param>
	void setPosition(sf::Vector2f t_pos);

	/// <summary>
	/// Sets if the tile has been marked already or not.
	/// </summary>
	/// <param name="mark">Bool for if the tile has been marked already</param>
	void setMarked(bool mark, int t_enemyID);

	/// <summary>
	/// Sets the pointer to the previous tile that this tile is connected to.
	/// </summary>
	/// <param name="previous">The pointer to the previous map tile</param>
	void setPrevious(Tile* previous, int t_enemyID);

	/// <summary>
	/// Adds the to the list of arc that start at this tile.
	/// </summary>
	/// <param name="node">The tile that the are will point to</param>
	/// <param name="weight">The travel cost of the new arc</param>
	void addArc(Tile* node, float weight);

	/// <summary>
	/// Draws a rectangle 
	/// </summary>
	/// <param name="t_window">The windowin which the rectangle will be drawn</param>
	void render(sf::RenderWindow& t_window);

	/// <summary>
	/// Sets the new path cost for this tile that has been calcukulated by A*.
	/// </summary>
	/// <param name="t_newCost">The new path cost</param>
	void setPathCost(float t_newCost, int t_enemyID);

	/// <summary>
	/// The estimated straight line path cost from this tile to the target tile.
	/// </summary>
	/// <param name="t_newHeuristic">The estimated path cost</param>
	void setHeuristicCost(float t_newHeuristic);

	/// <summary>
	/// Setter fucntion to set if the tile is walkable or not
	/// </summary>
	/// <param name="t_isWalkable">is it walkable</param>
	void setIsWalkable(bool t_isWalkable);

	/// <summary>
	/// Getter method for the m_isWalkable which provides information
	/// on if the tile can be traversed by a character.
	/// </summary>
	/// <returns>A bool for if the tile is walkable</returns>
	bool getIsWalkable();

	/// <summary>
	///	Getter method for the bool if the tile has been marked already.
	/// </summary>
	/// <returns>Bool for if the tile has been marked</returns>
	bool marked(int t_enemyID);

	/// <summary>
	///	Getter method for the path cost from this map tile.
	/// </summary>
	/// <returns>The path cost</returns>
	float getPathCost(int t_enemyID);

	/// <summary>
	///	Getter method for the predicted path cost from this map tile.
	/// </summary>
	/// <returns>The predicted path cost</returns>
	float getHeuristicCost();

	/// <summary>
	/// set the cost multiplier of the weight of the arc
	/// </summary>
	/// <param name="t_val">new value for the weight multiplier</param>
	void setCostMulti(float t_val) { m_costMultiplier = t_val; }

	/// <summary>
	///	Getter method for the cost multiplier that is applied to basic weight of the arc.
	/// </summary>
	/// <returns>The multiplier</returns>
	float getCostMulti() { return m_costMultiplier; }

	/// <summary>
	///	Getter method for the pointer to the previous map tile.
	/// </summary>
	/// <returns>pointer to the previous map tile/returns>
	Tile* previous(int t_enemyID);

	/// <summary>
	///	Getter method for arc that points to the passed in tile.
	/// If the returned arc is null that means there is no arc pointing to the passed in tile
	/// </summary>
	/// <param name="t_window">The tile to which we want to get an arc that points to it</param>
	/// <returns>Pointer to the arc/returns>
	MapArc* getArc(Tile* node);

	/// <summary>
	///	Getter method for the position of the map tile.
	/// </summary>
	/// <returns>The position of the map tile/returns>
	sf::Vector2f getPosition();

	void setIsOccupied(bool t_isOccupied);

	bool getIsOccupied();
	/// <summary>
	///	Getter method for the list of arcs that start at this tile.
	/// </summary>
	/// <returns>The list of arcs that starts at this tile/returns>
	std::list<MapArc> const& arcList() const;

	void clearArcs() { m_arcList.clear(); }

private:
	std::mutex m_mutex;
	std::map<int, Tile*> m_previousTiles;
	std::map<int, float> m_pathCosts;
	std::map<int, bool> m_isMarked;

	bool m_isWalkable;		//Bool for if the a moving world object can walk through it.
	sf::RectangleShape m_tileShape; //rectangle used to show what tiles are walkable or not;

	sf::Vector2f m_position;			//The position of the tile in the world.
	float m_costMultiplier = 1;			//The multiplier that is applied to thebasic weight of the arc.
	float m_heuristicCost{ 0 };				//The predicted cost from this tile.
	bool m_isOccupied{ false };
	//List of arcs the the map tile has.
	std::list<MapArc> m_arcList;

};


class TileSearchComperor
{
public:
	TileSearchComperor(int t_id) : m_id(t_id) {};

	int m_id;
	bool operator()(Tile* n1, Tile* n2)
	{
		return n1->getPathCost(m_id) + n1->getHeuristicCost() > n2->getPathCost(m_id) + n2->getHeuristicCost();
	}
};