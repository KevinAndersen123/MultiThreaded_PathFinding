#include "Map.h"

Map::Map()
{
	m_texture.create(3000, 3000);
	m_tile.setPosition(sf::Vector2f(0.0f, 0.0f));

	m_edgeMulti.push_back(sf::Vector2i(-1, -1));
	m_edgeMulti.push_back(sf::Vector2i(1, -1));
	m_edgeMulti.push_back(sf::Vector2i(1, 1));
	m_edgeMulti.push_back(sf::Vector2i(-1, 1));

}

void Map::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_gridSprite);
}

void Map::createMap(float t_tileSize, float t_outline)
{
	m_tileSize = t_tileSize;
	m_diagonalTileSize = std::sqrt(((t_tileSize * t_tileSize) + (t_tileSize * t_tileSize)));
	float offset = m_tileSize + t_outline * 2;
	m_tile.setSize(sf::Vector2f(m_tileSize, m_tileSize));
	m_tile.setOrigin(sf::Vector2f(m_tileSize / 2, m_tileSize / 2));
	m_tile.setOutlineColor(sf::Color::Black);
	m_tile.setOutlineThickness(t_outline);

	for (int x = 0; x < m_width; x++)
	{
		std::vector<Tile*> col;
		for (int y = 0; y < m_height; y++) 
		{
			col.push_back(new Tile());
			col[y]->setPosition(sf::Vector2f(offset / 2 + (offset * x), offset / 2 + (offset * y)));
			col[y]->setIsWalkable(true);
		}
		m_grid.push_back(col);
	}
	m_gridSprite.setPosition(0, 0);
}

void Map::genTexture()
{
	m_texture.clear();
	for (int x = 0; x < m_width; x++)
	{
		for (int y = 0; y < m_height; y++)
		{
			m_tile.setPosition(m_grid[x][y]->getPosition());
			if (!m_grid[x][y]->getIsWalkable())
			{
				m_tile.setFillColor(sf::Color::Yellow);
			}
			else
			{
				m_tile.setFillColor(sf::Color::Blue);
			}
			m_texture.draw(m_tile);
		}
	}
	m_texture.display();
	m_gridSprite.setTexture(m_texture.getTexture());
}

void Map::processEvents(sf::Event& t_event)
{
	
}

void Map::generate30Map()
{
	clearGrid();
	m_width = 30;
	m_height = 30;
	createMap(90.0f, 5.0f);

	for (int i = 1; i < 28; i++)
	{
		m_grid[14][i]->setIsWalkable(false);
		m_grid[15][i]->setIsWalkable(false);

	}
	for (int i = 3; i < 25; i++)
	{
		m_grid[21][i]->setIsWalkable(false);
		m_grid[22][i]->setIsWalkable(false);
	}
	m_grid[16][20]->setIsWalkable(false);
	m_grid[17][20]->setIsWalkable(false);

	for (int i = 0; i < 27; i++)
	{
		m_grid[8][i]->setIsWalkable(false);
		m_grid[9][i]->setIsWalkable(false);
	}
	genTexture();
	setUpArcs();
}

void Map::generate100Map()
{
	clearGrid();
	m_width = 100;
	m_height = 100;
	createMap(25.0f, 2.0f);

	for (int i = 30; i < 100; i++)
	{
		m_grid[70][i]->setIsWalkable(false);
		m_grid[71][i]->setIsWalkable(false);
	}

	for (int i = 0; i < 55; i++)
	{
		m_grid[30][i]->setIsWalkable(false);
		m_grid[31][i]->setIsWalkable(false);
	}

	for (int i = 10; i < 90; i++)
	{
		m_grid[15][i]->setIsWalkable(false);
		m_grid[16][i]->setIsWalkable(false);

		m_grid[43][i]->setIsWalkable(false);
		m_grid[44][i]->setIsWalkable(false);

		m_grid[55][i]->setIsWalkable(false);
		m_grid[56][i]->setIsWalkable(false);

		m_grid[79][i]->setIsWalkable(false);
		m_grid[80][i]->setIsWalkable(false);
	}

	for(int i = 81; i < 94; i++)
	{
		m_grid[i][50]->setIsWalkable(false);
	}
	genTexture();
	setUpArcs();
}

void Map::generate1000Map()
{
	clearGrid();
	m_width = 1000;
	m_height = 1000;
	createMap(2.0f, 0.5f);

	for (int i = 0; i < 700; i++)
	{
		m_grid[60][i]->setIsWalkable(false);
		m_grid[61][i]->setIsWalkable(false);
	}
	for (int i = 0; i < 300; i++)
	{
		m_grid[500][i]->setIsWalkable(false);
		m_grid[501][i]->setIsWalkable(false);
	}
	for (int i = 400; i <1000; i++)
	{
		m_grid[750][i]->setIsWalkable(false);
		m_grid[751][i]->setIsWalkable(false);
	}
	for (int i = 300; i < 600; i++)
	{
		m_grid[210][i]->setIsWalkable(false);
		m_grid[211][i]->setIsWalkable(false);

		m_grid[470][i]->setIsWalkable(false);
		m_grid[471][i]->setIsWalkable(false);

		m_grid[630][i]->setIsWalkable(false);
		m_grid[631][i]->setIsWalkable(false);

		m_grid[320][i]->setIsWalkable(false);
		m_grid[321][i]->setIsWalkable(false);

		m_grid[110][i]->setIsWalkable(false);
		m_grid[111][i]->setIsWalkable(false);
	}
	for (int i = 500; i < 900; i++)
	{
		m_grid[150][i]->setIsWalkable(false);
		m_grid[151][i]->setIsWalkable(false);

		m_grid[650][i]->setIsWalkable(false);
		m_grid[651][i]->setIsWalkable(false);

		m_grid[420][i]->setIsWalkable(false);
		m_grid[421][i]->setIsWalkable(false);

		m_grid[560][i]->setIsWalkable(false);
		m_grid[561][i]->setIsWalkable(false);

		m_grid[813][i]->setIsWalkable(false);
		m_grid[814][i]->setIsWalkable(false);
	}

	genTexture();
	setUpArcs();
}


bool Map::checkIsWalkable(sf::Vector2f t_pos, float t_rangeRadius)
{
	sf::Vector2i minMapIndex = getMapIndex(t_pos + sf::Vector2f(-t_rangeRadius, -t_rangeRadius));
	sf::Vector2i maxMapIndex = getMapIndex(t_pos + sf::Vector2f(t_rangeRadius, t_rangeRadius));

	for (int row = minMapIndex.y; row < maxMapIndex.y; row++)
	{
		for (int col = minMapIndex.x; col < maxMapIndex.x; col++)
		{
			if (!m_grid[row][col]->getIsWalkable())
			{
				return false;
			}
		}
	}
	return true;
}


sf::Vector2i Map::getMapIndex(sf::Vector2f m_position)
{
	sf::Vector2i mapIndex = static_cast<sf::Vector2i>(m_position / m_tileSize);

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
		m_height < from.y || m_width < from.x || m_height < to.y || m_width < to.x)
	{
		proceed = false;
	}

	//If an arc already exists we should not proceed
	if (m_grid[mapIndex1.first][mapIndex1.second]->getArc(m_grid[mapIndex2.first][mapIndex2.second]) != nullptr)
	{
		proceed = false;
	}

	if (proceed == true)
	{
		// add the arc to the "from" node.
		m_grid[from.y][from.x]->addArc(m_grid[to.y][to.x], weight);
	}

	return proceed;
}

void Map::setUpArcs()
{
	for (int row = 0; row < m_width; row++)
	{
		for (int col = 0; col < m_height; col++)
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
				if (n_row >= 0 && n_row < m_width && n_col >= 0 && n_col < m_height)
				{
					//Check if the target node is in stright line with the start node.
					if (n_row == row || n_col == col)
					{
						//First half ofthe cost.
						int cost1 = m_grid[row][col]->getCostMulti() * m_tileSize / 2;

						//Second half of the cost.
						int cost2 = m_grid[n_row][n_col]->getCostMulti() * m_tileSize / 2;

						addArc(sf::Vector2i(col, row), sf::Vector2i(n_col, n_row), cost1 + cost2);
					}
					//Otherwise the target node is diagonal to the start node.
					else
					{
						//First half ofthe cost.
						int cost1 = m_grid[row][col]->getCostMulti() * m_diagonalTileSize / 2;

						//Second half of the cost.
						int cost2 = m_grid[n_row][n_col]->getCostMulti() * m_diagonalTileSize / 2;

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
		m_height > from.y || m_width > from.x || m_height > to.y || m_width > to.x)
	{
		arc = m_grid[mapIndex1.first][mapIndex1.second]->getArc(m_grid[mapIndex2.first][mapIndex2.second]);
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

void Map::clearMarks(int t_enemyID)
{
	for (int row = 0; row < m_width; row++)
	{
		for (int col = 0; col < m_height; col++)
		{
			m_grid[row][col]->setMarked(false, t_enemyID);
		}
	}
}

void Map::clearPrevious(int t_enemyID)
{
	for (int row = 0; row < m_width; row++)
	{
		for (int col = 0; col < m_height; col++)
		{
			m_grid[row][col]->setPrevious(nullptr, t_enemyID);
		}
	}
}

void Map::clearGrid()
{
	for (int row = 0; row < m_width; row++)
	{
		for (int col = 0; col < m_height; col++)
		{
			if(!m_grid.empty())
				m_grid[row][col]->clearArcs();
		}
	}
	m_grid.clear();
}

void Map::setH(Tile* t_targetTile)
{
	for (int row = 0; row < m_width; row++)
	{
		for (int col = 0; col < m_height; col++)
		{
			//Calculates the heuristic for the straight line distance to the target.
			m_grid[row][col]->setHeuristicCost(abs(Thor::length(m_grid[row][col]->getPosition() - t_targetTile->getPosition())));
		}
	}
}

void Map::aStar(Tile* t_start, Tile* t_dest, Enemy*t_enemy, Map*t_map)
{
	int id = t_enemy->getID();

	//Safety check in case for if we are trying to path to something that has
	//died or in the case we have died.
	if (t_start == nullptr || t_dest == nullptr)
	{
		return;
	}
	TileSearchComperor compare = TileSearchComperor(id);

	//Priority queue used to reorgenise the tiles after the queue is popped so that
	//the target with the lowest path cost is the one that will be proccessed next.
	std::priority_queue<Tile*, std::vector<Tile*>, TileSearchComperor> pq(compare);

	//Add in the starting node to the queue.
	t_start->setPathCost(0,id);
	pq.push(t_start);
	t_start->setMarked(true,id);

	while (!pq.empty() && pq.top() != t_dest)
	{
		auto iter = pq.top()->arcList().begin();
		auto endIter = pq.top()->arcList().end();

		for (; iter != endIter; iter++)
		{
			if ((*iter).node() == pq.top()->previous(id))
			{
				continue;
			}

			MapArc arc = (*iter);

			//We do this to only proccess the tilse that we can walk onto
			//except for the case wehn the not walkable tile is the target tile
			//we want to walk to.
			if (arc.node()->getIsWalkable() || arc.node() == t_dest)
			{
				int childCost = arc.weight() + pq.top()->getPathCost(id);

				if (childCost < arc.node()->getPathCost(id))
				{
					arc.node()->setPathCost(childCost,id);
					arc.node()->setPrevious(pq.top(),id);

				}

				if (arc.node()->marked(id) == false)
				{
					pq.push(arc.node());
					arc.node()->setMarked(true,id);
				}
			}
		}

		pq.pop();
	}

	Tile* currentNode = t_dest;
	std::vector<Tile*> path;

	//We add the each of the tiles from destination to start to create the path.
	while (currentNode->previous(id) != nullptr)
	{
		path.push_back(currentNode);
		currentNode = currentNode->previous(id);
	}

	//We reverse the path so it begins at start tile.
	std::reverse(path.begin(), path.end());
	t_enemy->m_path = path;
	t_enemy->enableMovement(true);
	t_map->clearPrevious(id);
	t_map->clearMarks(id);
}

Tile* Map::getTileBasedOnPos(sf::Vector2f t_pos)
{
	sf::Vector2i mapIndex = getMapIndex(t_pos);

	return m_grid[mapIndex.x][mapIndex.y];
}


