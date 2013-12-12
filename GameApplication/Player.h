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
public:
	Player(int startPos){
		currentPos = startPos;
	};
	~Player(){};
	void SetMoveDirection(int dir);
	void update(float deltaTime);
	int checkPos(){
		return currentPos;
	}
};