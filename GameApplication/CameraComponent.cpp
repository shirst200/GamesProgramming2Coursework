#include "CameraComponent.h"
#include "Transform.h"
#include "GameObject.h"

void CameraComponent::update(){
	if(m_pOwnerGameObject)
	{
		Transform t=m_pOwnerGameObject->getTransform();
		XMFLOAT3 cameraPos=m_pOwnerGameObject->getTransform().getPosition();
		m_View=XMMatrixLookAtLH(XMLoadFloat3(&cameraPos),XMLoadFloat3(&m_LookAt),XMLoadFloat3(&m_Up));
		m_Projection=XMMatrixPerspectiveFovLH(m_FOV,m_AspectRatio,m_NearClip,m_FarClip);
	}
}