#pragma once

#include "../GameApplication/GameApplication.h"
#include "../GameApplication/ResourceHolder.h"

class MyGame:public CGameApplication
{
public:
	MyGame(){};
	~MyGame(){};
	bool initGame();

private:

        static const int width = 17;
		static const int height = 21;
		int gridSpots[];
};