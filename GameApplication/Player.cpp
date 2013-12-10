#include "Player.h"
#include "GameController.h"
#include "Transform.h"
#include "GameObject.h"

void Player::SetMoveDirection(int newDir){
	currentDir = newDir;
}

void Player::update(){
	Transform t=m_pOwnerGameObject->getTransform();
	if(currentKey=="w")
	{
		desiredSpot = currentPos+17;
	}
	if(currentKey=="s")
	{
		desiredSpot = currentPos-17;
	}
	if(currentKey=="a")
	{
		desiredSpot = currentPos-1;
	}
	if(currentKey=="d")
	{
		desiredSpot = currentPos+1;
	}
}