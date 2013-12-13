#include "Player.h"
#include "Transform.h"
#include "GameObject.h"

void Player::SetMoveDirection(int newDir){
	currentDir = newDir;
}

void Player::update(float deltaTime){
	waitTime-=deltaTime;
	if(waitTime>0){
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
		waitTime = 1/speed;
		lastDir = currentDir;
		//ROund the position to the closest grid spot
		m_pOwnerGameObject->getTransform().roundToGrid();
		if(lastDir==1) //up
			currentPos = currentPos-17;
		if(lastDir==2) //right
			currentPos = currentPos+1;
		if(lastDir==3) //down
			currentPos = currentPos+17;
		if(lastDir==4) //left
			currentPos = currentPos-1;
	}
}