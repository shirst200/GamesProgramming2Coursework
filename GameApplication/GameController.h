#include "GameComponent.h"

class GameController : public GameComponent
{
private:

public:
	GameController(){};
	~GameController(){};
	void spawnMap();
	bool checkGridSpot(int spot){
		return gridSpots[spot];
	};

private:
        static const int width = 17;
		static const int height = 21;
		int gridSpots[];
};