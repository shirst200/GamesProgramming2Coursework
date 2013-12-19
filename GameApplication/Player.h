#include "GameComponent.h"
#include <time.h>
using std::string;

class Player : public GameComponent
{
private:
	//Current grid position of player
	int currentPos;
	//Current direction of player
	int currentDir;
	//Stored version of direction, only updates when player makes a decision
	int lastDir;
	//How long to wait between movement decisions
	float waitTime;
	//Speed of the player in grid positions per second
	float speed;
public:
	//Set up the player
	Player(int startPos){
		//Set player start position
		currentPos = startPos;
		//Set the time between movement decisions
		waitTime = 0.5;
		//Set speed
		speed = 2;
	};
	~Player(){};
	//Used to set the direction of the player, done each frame
	void SetMoveDirection(int dir);
	//Updates the player by delta time each frame
	void update(float deltaTime);
	//Return the position of the player, used for collision in GameApplication
	int checkPos(){
		return currentPos;
	}
};