#ifndef MAPARC_H
#define MAPARC_H

#include "Tile.h"

class MapArc
{
private:

	//The map tile that the arc points to.
	Tile* m_node;

	//The cost to travel to the tile that the arc is pointing to.
	float m_weight;
public:
	/// <summary>
	/// Getter method for the map tile that the arc points to.
	/// </summary>
	/// <returns>Pointer to the tile that the arc points to</returns>
	Tile* node() const
	{
		return m_node;
	}

	/// <summary>
	/// Getter method for the cost to travel to the tile that the arc is pointing to.
	/// </summary>
	/// <returns>Cost of travel to this tile</returns>
	float weight() const
	{
		return m_weight;
	}

	/// <summary>
	/// Sets the map tile the arc is pointing to.
	/// </summary>
	/// <param name="node">The map tile that the arc will point to</param>
	void setNode(Tile* node)
	{
		m_node = node;
	}

	/// <summary>
	/// Sets the travel cost of this arc.
	/// </summary>
	/// <param name="weight">The cost of travel to the map tile that the arc is pointing to</param>
	void setWeight(float weight)
	{
		m_weight = weight;
	}
};
#endif