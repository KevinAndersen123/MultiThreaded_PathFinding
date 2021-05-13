#include "Map.h"
#include "ThreadPool.h"
#include "Enemy.h"

#include <queue>
class Game
{
public:
	Game();
	~Game();
	void run();

	Map m_map;
private:
	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	sf::RenderWindow m_window;
	sf::View m_view;
	ThreadPool m_threadPool;
};
