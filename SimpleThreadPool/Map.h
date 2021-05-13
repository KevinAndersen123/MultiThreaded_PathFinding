#pragma once
#include <algorithm>
#include <vector>
#include <iostream>
#include "Tile.h"
#include "MapArc.h"
#include <list>
#include <queue>
#include <limits>
#include <stack>
#include <functional>
#include "MathLib.h"

class Map
{
public:

	Map();
	
	void setupTiles();
	void update(sf::Time t_dt);
	void processEvents(sf::Event& t_event);
	void generateSmallMap();
	void generateMediumMap();
	void generateLargeMap();

	void render(sf::RenderWindow& t_window);

	/// <summary>
	/// Checks if the tiles that are in the range a walkable.
	/// If one of the tiles is not walkable the function returns false.
	/// </summary>
	/// <param name="t_pos">The position at which the radius of the range starts</param>
	/// <param name="t_rangeRadius">The radius of the range</param>
	/// <returns>Bool for if all the tiles are walkable within the range</returns>
	bool checkIsWalkable(sf::Vector2f t_pos, float t_rangeRadius);

	/// <summary>
	/// A* alogrythm that searches for the destination tile starting at the start tile.
	/// by expanding all the tiles that are getting closer to the destination first.
	/// </summary>
	/// <param name="t_start">The tile from which the A* will start searching</param>
	/// <param name="t_dest">The tile which the A* is looking for</param>
	/// <param name="t_path">The resulting path that has to be taken to reach the destination</param>
	void aStar(Tile* t_start, Tile* t_dest, std::vector<Tile*>& t_path);

	/// <summary>
	/// Getter method for a pointer to the tile that is containes the target position.
	/// </summary>
	/// <param name="t_pos">Target position based on which we want to get tile</param>
	/// <returns>Pointer to the map tile that contains the target position</returns>
	Tile* getTileBasedOnPos(sf::Vector2f t_pos);

	//The size of a tile.
	const int m_TILE_SIZE{ 32 };

	//The size of the tile diagonaly.
	const int m_TILE_DIAGONAL_SIZE{ 45 };
	const static int m_gridSize = 30;

private:

	//Vector used to find the edges of a collider.
	std::vector<sf::Vector2i> m_edgeMulti;

	Tile m_grid[m_gridSize][m_gridSize];	//Map of map tile objects.


	/// <summary>
	/// Getter method for the index in the map based on the passed in position.
	/// </summary>
	/// <param name="m_position">The position that we want to convert into map index</param>
	/// <returns>The index of the map as a vector</returns>
	sf::Vector2i getMapIndex(sf::Vector2f m_position);

	/// <summary>
	/// Getter method to get all the tiles that are within the past in range.
	/// </summary>
	/// <param name="t_pos">The position which we want to get tiles around</param>
	/// <param name="t_rangeRadius">The radius of the in which we want to get all the tiles</param>
	/// <returns>Vector of MapTile pointers that are within the range radius</returns>
	std::vector<Tile*>getTilesInRange(sf::Vector2f t_pos, float t_rangeRadius);

	/// <summary>
	/// Adds the arc between two tiles. If the arc would go out of map bounds it is ignored.
	/// </summary>
	/// <param name="from">The tile index at which the arc will start</param>
	/// <param name="to">The tile index to which the arc is going to</param>
	/// <param name="weight">The cost of travel for that arc</param>
	/// <returns>Bool for if the function has succeded succesfully</returns>
	bool addArc(sf::Vector2i from, sf::Vector2i to, float weight);

	/// <summary>
	/// Creates the arcs between each node in the map using the neighbours algorythm.
	/// The weight of the arcs is determined using the type of the node and the distance between them.
	/// </summary>
	void setUpArcs();

	/// <summary>
	/// Getter method for a map arc based on map indexes. If the pointer is null
	/// it means that there is no are between these two indexes
	/// </summary>
	/// <param name="from">Vector for the first tile's index position</param>
	/// <param name="to">Vector for the second tile's index position</param>
	/// <returns>Pointer to the map arc between the two tiles</returns>
	MapArc* getArc(sf::Vector2i from, sf::Vector2i to);

	/// <summary>
	/// Getter method for a map arc based on map tiles. If the pointer is null
	/// it means that there is no are between these two indexes
	/// </summary>
	/// <param name="from">The first map tile</param>
	/// <param name="to">The second map tile</param>
	/// <returns>Pointer to the map arc between the two tiles</returns>
	MapArc* getArc(Tile* from, Tile* to);

	/// <summary>
	/// Sets the marked bool for each tile to false.
	/// </summary>
	void clearMarks();

	/// <summary>
	/// Sets the previous pointer for each tile to nullptr.
	/// </summary>
	void clearPrevious();
};
