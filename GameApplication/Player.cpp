#include "Player.h"
#include "Transform.h"
#include "GameObject.h"

void Player::SetMoveDirection(int newDir){
	currentDir = newDir;
}

void Player::update(float deltaTime){
	Transform tForm = m_pOwnerGameObject->getTransform();
	if(waitTime>0){
		waitTime-=deltaTime;
		if(lastDir==1) //up
			tForm.translate(0.0f,0.0f,1.0f*deltaTime);
		if(lastDir==2) //right
			tForm.translate(1.0f*deltaTime,0.0f,0.0f);
		if(lastDir==3) //down
			tForm.translate(0.0f,0.0f,-1.0f*deltaTime);
		if(lastDir==4) //left
			tForm.translate(-1.0f*deltaTime,0.0f,0.0f);
	}
	else{
		waitTime = 1.0f;
		lastDir = currentDir;
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