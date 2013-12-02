//#pragma once
//
//#include "LightComponent.h"
//
//class DirectionLightComponent:public LightComponent
//{
//public:
//	DirectionLightComponent()
//	{
//		m_Name = "DirectionalLight";
//	};
//
//	~DirectionLightComponent(){};
//	
//	void setDirection(float x, float y, float z)
//	{
//		m_Direction=XMFLOAT3(x,y,z);
//	};
//
//	XMFLOAT3& getDirection()
//	{
//		return m_Direction;
//	};
//private:
//	//Represents the direction of the light
//	XMFLOAT3 m_Direction;
//}

#pragma once


#include "LightComponent.h"


class DirectionLightComponent:public LightComponent
{
public:
        DirectionLightComponent(){
                m_LightDirection=XMFLOAT3(0.0f,0.0f,-1.0f);
                m_Name="DirectionalLight";
        };


        ~DirectionLightComponent(){};

        void setDirection(float x,float y,float z)
        {
                m_LightDirection=XMFLOAT3(x,y,z);
        };


        XMFLOAT3& getDirection()
        {
                return m_LightDirection;
        };
private:
        XMFLOAT3 m_LightDirection;
};

