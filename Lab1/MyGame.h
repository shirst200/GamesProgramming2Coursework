#pragma once

#include "../GameApplication/GameApplication.h"

class MyGame:public CGameApplication
{
public:
	MyGame(){};
	~MyGame(){};
	bool initGame();

	bool checkGridSpot(int spot){
		return gridSpots[spot];
	};

private:
        static const int width = 4;
		static const int height = 4;

		bool gridSpots[];
};