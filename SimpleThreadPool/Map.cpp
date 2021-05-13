#include "Map.h"

Map::Map()
{
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			sf::Vector2f pos = sf::Vector2f(m_TILE_SIZE / 2 + m_TILE_SIZE * col,
				m_TILE_SIZE / 2 + m_TILE_SIZE * row);

			m_grid[row][col].setPosition(pos);
		}
	}

	m_edgeMulti.push_back(sf::Vector2i(-1, -1));
	m_edgeMulti.push_back(sf::Vector2i(1, -1));
	m_edgeMulti.push_back(sf::Vector2i(1, 1));
	m_edgeMulti.push_back(sf::Vector2i(-1, 1));

}

void Map::render(sf::RenderWindow& t_window)
{
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			m_grid[row][col].render(t_window);
		}
	}
}


void Map::setupTiles()
{
	setUpArcs();
}

void Map::update(sf::Time t_dt)
{

}

void Map::processEvents(sf::Event& t_event)
{
	
}

void Map::generateSmallMap()
{

}

void Map::generateMediumMap()
{
}

void Map::generateLargeMap()
{
}


bool Map::checkIsWalkable(sf::Vector2f t_pos, float t_rangeRadius)
{
	sf::Vector2i minMapIndex = getMapIndex(t_pos + sf::Vector2f(-t_rangeRadius, -t_rangeRadius));
	sf::Vector2i maxMapIndex = getMapIndex(t_pos + sf::Vector2f(t_rangeRadius, t_rangeRadius));

	for (int row = minMapIndex.y; row < maxMapIndex.y; row++)
	{
		for (int col = minMapIndex.x; col < maxMapIndex.x; col++)
		{
			if (!m_grid[row][col].getIsWalkable())
			{
				return false;
			}
		}
	}

	return true;
}


sf::Vector2i Map::getMapIndex(sf::Vector2f m_position)
{
	sf::Vector2i mapIndex = static_cast<sf::Vector2i>(m_position / static_cast<float>(m_TILE_SIZE));

	if (mapIndex.x < 0)
	{
		mapIndex.x = 0;
	}

	if (mapIndex.y < 0)
	{
		mapIndex.y = 0;
	}

	return mapIndex;
}

bool Map::addArc(sf::Vector2i from, sf::Vector2i to, float weight)
{
	std::pair<int, int> mapIndex1 = std::make_pair(from.y, from.x);
	std::pair<int, int> mapIndex2 = std::make_pair(to.y, to.x);

	bool proceed = true;
	// make sure both nodes exist.
	if (0 > from.y || 0 > from.x || 0 > to.y || 0 > to.x ||
		m_gridSize < from.y || m_gridSize < from.x || m_gridSize < to.y || m_gridSize < to.x)
	{
		proceed = false;
	}

	//If an arc already exists we should not proceed
	if (m_grid[mapIndex1.first][mapIndex1.second].getArc(&m_grid[mapIndex2.first][mapIndex2.second]) != nullptr)
	{
		proceed = false;
	}

	if (proceed == true)
	{
		// add the arc to the "from" node.
		m_grid[from.y][from.x].addArc(&m_grid[to.y][to.x], weight);
	}

	return proceed;
}

void Map::setUpArcs()
{
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			// List all neighbors:
			for (int direction = 0; direction < 9; direction++)
			{
				if (direction == 4)
				{
					continue;
				}

				int n_row = row + ((direction % 3) - 1);	//Neighbor row
				int n_col = col + ((direction / 3) - 1);	//Neighbor column

				// Check the bounds.
				if (n_row >= 0 && n_row < m_gridSize && n_col >= 0 && n_col < m_gridSize)
				{
					//Check if the target node is in stright line with the start node.
					if (n_row == row || n_col == col)
					{
						//First half ofthe cost.
						int cost1 = m_grid[row][col].getCostMulti() * m_TILE_SIZE / 2;

						//Second half of the cost.
						int cost2 = m_grid[n_row][n_col].getCostMulti() * m_TILE_SIZE / 2;

						addArc(sf::Vector2i(col, row), sf::Vector2i(n_col, n_row), cost1 + cost2);
					}

					//Otherwise the target node is diagonal to the start node.
					else
					{
						//First half ofthe cost.
						int cost1 = m_grid[row][col].getCostMulti() * m_TILE_DIAGONAL_SIZE / 2;

						//Second half of the cost.
						int cost2 = m_grid[n_row][n_col].getCostMulti() * m_TILE_DIAGONAL_SIZE / 2;

						addArc(sf::Vector2i(col, row), sf::Vector2i(n_col, n_row), cost1 + cost2);
					}
				}
			}
		}
	}
}

MapArc* Map::getArc(sf::Vector2i from, sf::Vector2i to)
{
	std::pair<int, int> mapIndex1 = std::make_pair(from.y, from.x);
	std::pair<int, int> mapIndex2 = std::make_pair(to.y, to.x);

	MapArc* arc = 0;
	// make sure the to and from nodes exist
	if (0 <= from.y || 0 <= from.x || 0 <= to.y || 0 <= to.x ||
		m_gridSize > from.y || m_gridSize > from.x || m_gridSize > to.y || m_gridSize > to.x)
	{
		arc = m_grid[mapIndex1.first][mapIndex1.second].getArc(&m_grid[mapIndex2.first][mapIndex2.second]);
	}

	return arc;
}

MapArc* Map::getArc(Tile* from, Tile* to)
{
	MapArc* arc = 0;

	if (from != nullptr && to != nullptr)
	{
		arc = from->getArc(to);
	}

	return arc;
}

void Map::clearMarks()
{
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			m_grid[row][col].setMarked(false);
		}
	}
}

void Map::clearPrevious()
{
	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			m_grid[row][col].setPrevious(nullptr);
		}
	}
}

void Map::aStar(Tile* t_start, Tile* t_dest, std::vector<Tile*>& t_path)
{
	//Clear the passed in path as we do not want to add in more tile to the path.
	t_path.clear();

	//Safety check in case for if we are trying to path to something that has
	//died or in the case we have died.
	if (t_start == nullptr || t_dest == nullptr)
	{
		return;
	}

	//Priority queue used to reorgenise the tiles after the queue is popped so that
	//the target with the lowest path cost is the one that will be proccessed next.
	std::priority_queue<Tile*, std::vector<Tile*>, TileSearchComperor> pq;

	for (int row = 0; row < m_gridSize; row++)
	{
		for (int col = 0; col < m_gridSize; col++)
		{
			//Sets the current path cost to the maximum possible value.
			m_grid[row][col].setPathCost(std::numeric_limits<int>::max());

			//Calculates the heuristic for the straight line distance to the target.
			m_grid[row][col].setHeuristicCost(abs(Thor::length(m_grid[row][col].getPosition() - t_dest->getPosition())));
		}
	}

	//Add in the starting node to the queue.
	t_start->setPathCost(0);
	pq.push(t_start);
	t_start->setMarked(true);

	while (!pq.empty() && pq.top() != t_dest)
	{
		auto iter = pq.top()->arcList().begin();
		auto endIter = pq.top()->arcList().end();

		for (; iter != endIter; iter++)
		{
			if ((*iter).node() == pq.top()->previous())
			{
				continue;
			}

			MapArc arc = (*iter);

			//We do this to only proccess the tilse that we can walk onto
			//except for the case wehn the not walkable tile is the target tile
			//we want to walk to.
			if (arc.node()->getIsWalkable() || arc.node() == t_dest)
			{
				int childCost = arc.weight() + pq.top()->getPathCost();

				if (childCost < arc.node()->getPathCost())
				{
					arc.node()->setPathCost(childCost);
					arc.node()->setPrevious(pq.top());

				}

				if (arc.node()->marked() == false)
				{
					pq.push(arc.node());
					arc.node()->setMarked(true);
				}
			}
		}

		pq.pop();
	}

	Tile* currentNode = t_dest;

	//We add the each of the tiles from destination to start to create the path.
	while (currentNode->previous() != nullptr)
	{
		t_path.push_back(currentNode);
		currentNode = currentNode->previous();
	}

	//We reverse the path so it begins at start tile.
	std::reverse(t_path.begin(), t_path.end());

	clearMarks();
	clearPrevious();
}


Tile* Map::getTileBasedOnPos(sf::Vector2f t_pos)
{
	sf::Vector2i mapIndex = getMapIndex(t_pos);

	return &m_grid[mapIndex.y][mapIndex.x];
}

std::vector<Tile*> Map::getTilesInRange(sf::Vector2f t_pos, float t_rangeRadius)
{
	std::vector<Tile*> tiles;

	sf::Vector2i minMapIndex = getMapIndex(t_pos + sf::Vector2f(-t_rangeRadius, -t_rangeRadius));
	sf::Vector2i maxMapIndex = getMapIndex(t_pos + sf::Vector2f(t_rangeRadius, t_rangeRadius));

	if (minMapIndex == maxMapIndex)
	{
		tiles.push_back(&m_grid[minMapIndex.y][minMapIndex.x]);
	}
	else
	{
		for (int row = minMapIndex.y; row <= maxMapIndex.y; row++)
		{
			for (int col = minMapIndex.x; col <= maxMapIndex.x; col++)
			{
				tiles.push_back(&m_grid[row][col]);
			}
		}
	}

	return tiles;
}

