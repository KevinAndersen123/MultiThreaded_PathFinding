#pragma once
#include <SFML/Graphics.hpp>
#include <list>

enum class TileType
{
	Default,
	Start,
	Goal,
	Impassable,
	Void
};

class Tile
{
public:
	Tile();
	~Tile();

	/// <summary>
	/// Sets the position of the tile sprite to the passed in position.
	/// </summary>
	/// <param name="t_pos">The position that the position of the tile is to be set to</param>
	void setPosition(sf::Vector2f t_pos);

	/// <summary>
	/// Sets if the tile has been marked already or not.
	/// </summary>
	/// <param name="mark">Bool for if the tile has been marked already</param>
	void setMarked(bool t_mark);

	/// <summary>
	///	Getter method for the bool if the tile has been marked already.
	/// </summary>
	/// <returns>Bool for if the tile has been marked</returns>
	bool getMarked() const;

	/// <summary>
	///	Get method for the type of this tile.
	/// </summary>
	/// <returns>The type of this tile</returns>
	TileType getTileType() const;

	void setTileType(TileType t_type);
	/// <summary>
	///	Get method for the position of the map tile.
	/// </summary>
	/// <returns>The position of the map tile/returns>
	sf::Vector2f getPosition();

	/// <summary>
	/// sets the weight of the tile
	/// </summary>
	/// <param name="t_weight"> weight of the tile</param>
	void setWeight(int t_weight);

	/// <summary>
	/// gets the weight of the tile
	/// </summary>
	float getWeight() const;
private:

	TileType m_type{ TileType::Default };								//The type of the tile.

	sf::Vector2f m_position = sf::Vector2f(0.0f, 0.0f);					//The position of the tile in the world.

	std::list<Tile*> m_neighbourTiles;

	bool m_marked = false;												//Bool for if the map tile has already been marked.
	float m_weight = 0;

};
