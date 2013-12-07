#include "GameComponent.h"

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;

public:
	Player();
	Player(int startPos);
	void update(float deltaTime);
	void SetMoveDirection(int dir);
};