#include "Player.h"
#include "Transform.h"
#include "GameObject.h"

void Player::SetMoveDirection(int newDir){
	//Sets the movement direction for the player
	currentDir = newDir;
}

void Player::update(float deltaTime){
	//Update how long left to wait before making a new decision
	waitTime-=deltaTime;
	//Rotate the player
	m_pOwnerGameObject->getTransform().rotate(0.0f,0.0f,(1.0f*deltaTime)*speed);
	if(waitTime>0){
		//Move the player in it's chosen direction depending on how long since the last frame
		if(lastDir==1) //up
			m_pOwnerGameObject->getTransform().translate(0.0f,0.0f,(1.0f*deltaTime)*speed);
		if(lastDir==2) //right
			m_pOwnerGameObject->getTransform().translate((1.0f*deltaTime)*speed,0.0f,0.0f);
		if(lastDir==3) //down
			m_pOwnerGameObject->getTransform().translate(0.0f,0.0f,(-1.0f*deltaTime)*speed);
		if(lastDir==4) //left
			m_pOwnerGameObject->getTransform().translate((-1.0f*deltaTime)*speed,0.0f,0.0f);
	}
	else{
		//Set how long it takes for the player to move fully
		waitTime = 1/speed;
		//Store the direction at this time, current dir 
		//constantly changes so cant be used for movemenet
		lastDir = currentDir;
		//Round the position to the closest grid spot
		m_pOwnerGameObject->getTransform().roundToGrid();
		if(lastDir==1) //up
			currentPos = currentPos-17;
		if(lastDir==2) //right
			currentPos = currentPos+1;
		if(lastDir==3) //down
			currentPos = currentPos+17;
		if(lastDir==4) //left
			currentPos = currentPos-1;
		//Checks to see if the player is on the right hand teleporter
		if(currentPos==169 && currentDir == 2){
			//Move the player left and set its new position
			m_pOwnerGameObject->getTransform().setPosition(1.0f,1.0f,11.0f);
			currentPos = 155;
		}
		//Checks to see if the player is on the left hand teleporter
		if(currentPos==153 && currentDir == 4){
			//Move the player right and set its new position
			m_pOwnerGameObject->getTransform().setPosition(15.0f,1.0,11.0f);
			currentPos = 167;
		}
	}
}