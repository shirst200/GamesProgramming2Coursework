#pragma once

#include "GameComponent.h"

#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>

class CameraComponent:public GameComponent
{
public:
        CameraComponent()							//basic constructor
        {
                m_Name="Camera";					//name of the component
                m_LookAt=XMFLOAT3(0.0f,0.0f,0.0f);	//represents the point the camera is looking at
                m_Up=XMFLOAT3(0.0f,1.0f,0.0f);		//represents the up direction of the camera
                m_View=XMMatrixIdentity();			//represents a view matrix
                m_Projection=XMMatrixIdentity();	//represents a projection matrix
                m_FOV=XM_PI/4;						//the field of view of the camera
                m_AspectRatio=800.0f/640.0f;		//the aspect ratio of the camera
                m_Near=0.1f;						//the near clip of the camera
                m_Far=1000.0f;						//the far clip of the camera
        };

        ~CameraComponent()							//basic deconstructor
        {
        }


        void update();								//called every frame

        void setLook(float x,float y,float z)		
        {
                m_LookAt=XMFLOAT3(x,y,z);			//set the point the camera is looking at to x, y, z
        };

        void setUp(float x,float y,float z)
        {
                m_Up=XMFLOAT3(x,y,z);				//set the up direction to x, y, z
        };

        void setFOV(float fov)
        {
                m_FOV=fov;							//set the camera's field of view
        };

        void setAspectRatio(float aspectRatio)
        {
                m_AspectRatio=aspectRatio;			//set the camera's aspect ratio
        };

        void setNearClip(float nearClip)
        {
                m_Near=nearClip;					//set the camera's near clipping plane
        };

        void setFarClip(float farClip)
        {
                m_Far=farClip;						//set the camera's far clipping plane
        };

        XMFLOAT3& getLookAt()
        {
                return m_LookAt;					//return the point the camera is looking at
        };

        XMFLOAT3& getUp()
        {
                return m_Up;						//return the up direction of the camera
        };

        float getFOV()
        {
                return m_FOV;						//return the field of view of the camera
        };

        float getAspectRatio()
        {
                return m_AspectRatio;				//return the aspect ratio of the camera
        };

        float getNear()
        {
                return m_Near;						//return the near clipping plane
        };

        float getFar()
        {
                return m_Far;						//return the far clipping plane
        };

        XMMATRIX& getView()
        {
                return m_View;						//return the view matrix
        };

        XMMATRIX& getProjection()
        {
                return m_Projection;				//return the projection matrix
        };
private:
        XMFLOAT3 m_LookAt;							//the point the camera is looking at
        XMFLOAT3 m_Up;								//the up direction of the camera
        float m_FOV;								//the field of view of the camera
        float m_AspectRatio;						//the aspect ratio of the camera
        float m_Near;								//the near clipping plane
        float m_Far;								//the far clipping plane
        XMMATRIX m_View;							//the view matrix
        XMMATRIX m_Projection;						//the projection matrix
};