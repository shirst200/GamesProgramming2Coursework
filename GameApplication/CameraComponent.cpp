#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"

void CameraComponent::update(){
	if(m_pOwnerGameObject)			//if the camera is attached to a game object
	{
		Transform t=m_pOwnerGameObject->getTransform();		//get the transform of this game object
		XMFLOAT3 cameraPos=m_pOwnerGameObject->getTransform().getPosition();	//set the position of the camera to that game object's position
		m_View=XMMatrixLookAtLH(XMLoadFloat3(&cameraPos),XMLoadFloat3(&m_LookAt),XMLoadFloat3(&m_Up));	//set the view matrix to (the camera's position, the point the camera looks at, the up direction)
		m_Projection=XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_Near,m_Far);	//set the projection matrix to (field of view, aspect ratio, near clipping plane, far clipping plane)
	}
}