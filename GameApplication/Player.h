#include "GameComponent.h"

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;

public:
	Player();
	Player(int startPos);
	void update(float deltaTime);					// update the balloons position based on the translation
	void SetMoveDirection(int dir);
};