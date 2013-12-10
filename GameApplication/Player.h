#include "GameComponent.h"

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;
	string currentKey;

public:
	Player(int startPos){
		currentPos = startPos;
	};
	~Player(){};
	void SetMoveDirection(int dir);
	void update();
	void setKey(string gotInput){
		currentKey = gotInput;
	};
};