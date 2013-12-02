#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>


class CameraComponent:public GameComponent
{
public:
	CameraComponent()																						//constructor for the class
	{
		m_LookAt=XMFLOAT3(0.0f,0.0f,0.0f);
		m_Up=XMFLOAT3(0.0f,1.0f,0.0f);
		m_FOV=XM_PI/4;
		m_AspectRatio=800.0f/640.0f;
		m_NearClip=0.1f;
		m_FarClip=1000.0f;
		m_View=XMMatrixIdentity();
		m_Projection=XMMatrixIdentity();
		m_Name="Camera";
	};			

	~CameraComponent(){};																					//deconstructor for the class

	void setLook(float x, float y, float z)																	//set function for the point the camera is looking at
	{
		m_LookAt = XMFLOAT3(x,y,z);
	};				

	void setUp(float x, float y, float z)																	//set function for the up direction of the camera
	{
		m_Up = XMFLOAT3(x,y,z);
	};	

	void setFOV(float fov)																					//set function for the field of the view of the camera
	{
		m_FOV = fov;
	};		

	void setAspectRatio(float ratio)																		//set function for the aspect ratio of the camera
	{
		m_AspectRatio = ratio;
	};	

	void setNearClip(float near)																			//set function for the near clip of the camera
	{
		m_NearClip = near
	};

	void setFarClip(float far)																				//set function for the far clip of the camera
	{
		m_FarClip = far
	};		

	XMFLOAT3& getLook()																						//get function for the point the camera is looking at
	{
		return m_LookAt;
	};				
	
	XMFLOAT3& getUp()																						//get function for the up direction of the camera
	{
		return m_Up;
	};		

	float getFOV()																							//get function for the field of view of the camera
	{
		return m_FOV;
	};	

	float getAspectRatio()																					//get function for the aspect ratio of the camera
	{
		return m_AspectRatio;
	};			

	float getNearClip()																						//get function for the near clip of the camera
	{
		return m_NearClip;
	};	

	float getFarClip()																						//get function for the far clip of the camera
	{
		return m_FarClip;
	};		

	XMMATRIX& getView()																						//get function for the view matrix
	{
		return m_View;
	};	

	XMMATRIX& getProjection()																				//get function for the projection matrix
	{
		return m_Projection;
	};		

	void update();																							//overridden from the base class

private:
	XMFLOAT3 m_LookAt;																						//This represents the point the camera is looking at
	XMFLOAT3 m_Up;																							//This represents the up direction of the camera
	float m_FOV;																							//The field of view of the camera
	float m_AspectRatio;																					//The aspect ratio of the camera
	float m_NearClip;																						//The near clip of the camera
	float m_FarClip;																						//The far clip of the camera
	XMMATRIX m_View;																						//Represents a view matrix
	XMMATRIX m_Projection;																					//Represents a projection matrix	
																											//Name held in base class to manage camera component
};