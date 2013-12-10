#include "GameComponent.h"
using std::string;

class Player : public GameComponent
{
private:
	int currentPos;
	int currentDir;
	string currentKey;
	GameObject *gameController;
	int desiredSpot;

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
	void setController(GameObject *pController)
	{
		gameController=pController;
	};
	int checkDesired(){
		return desiredSpot;
	}
};