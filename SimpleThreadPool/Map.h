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
#include <mutex>
#include "Enemy.h"

class Map
{
public:

	Map();
	
	void processEvents(sf::Event& t_event);
	void generate30Map();
	void generate100Map();
	void generate1000Map();

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
	void aStar(Tile* t_start, Tile* t_dest, std::vector<Tile*>& t_path);

	std::vector<std::vector<Tile*>> m_grid;
private:
	int m_width = 0;
	int m_height = 0;
	float m_tileSize =0;
	float m_diagonalTileSize = 0;
	sf::Sprite m_gridSprite;
	sf::RectangleShape m_tile;
	sf::RenderTexture m_texture;

	sf::Vector2f m_offset;

	//Vector used to find the edges of a collider.
	std::vector<sf::Vector2i> m_edgeMulti;
	void createMap(float t_tileSize, float t_outline);
	void genTexture();

	/// <summary>
	/// Getter method for the index in the map based on the passed in position.
	/// </summary>
	/// <param name="m_position">The position that we want to convert into map index</param>
	/// <returns>The index of the map as a vector</returns>
	sf::Vector2i getMapIndex(sf::Vector2f m_position);

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

	void clearGrid();
};
