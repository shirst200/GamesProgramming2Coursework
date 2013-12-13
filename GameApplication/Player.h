#include "GameComponent.h"
#include <time.h>
using std::string;

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;
	int lastDir;
	float waitTime;
	float speed;
public:
	Player(int startPos){
		currentPos = startPos;
		waitTime = 0.5;
		speed = 2;
	};
	~Player(){};
	void SetMoveDirection(int dir);
	void update(float deltaTime);
	int checkPos(){
		return currentPos;
	}
};