#include "GameComponent.h"

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;

public:
	Player(int startPos){
		currentPos = startPos;
	};
	~Player(){};
	void SetMoveDirection(int dir);
	void update();
};