#include "Tile.h"
#include <queue>
class Game
{
public:
	Game();
	~Game();
	void run();
private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	void initGrid();
	std::vector<std::vector<Tile>> m_tileArray;
	sf::RenderWindow m_window;
	sf::RectangleShape m_tile;
	int m_gridSize = 30;
	sf::View m_view;
};
