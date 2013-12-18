#pragma once


#include "LightComponent.h"


class DirectionLightComponent:public LightComponent
{
public:
        DirectionLightComponent(){
                m_LightDirection=XMFLOAT3(0.0f,0.0f,-1.0f);
                m_Name="DirectionalLight";
				rotate=0;
				count = 0.0f;
				check =0.0f;
        };


        ~DirectionLightComponent(){};

        void setDirection(float x,float y,float z)
        {
                m_LightDirection=XMFLOAT3(x,y,z);
        };

		void update(float deltaTime);

        XMFLOAT3& getDirection()
        {
                return m_LightDirection;
        };

		void RotateOn()
        {
                rotate=1;
        };


        void RoatateOff()
        {
               rotate=0;
        };


private:
        XMFLOAT3 m_LightDirection;
		int rotate;
		float count;
		int check;
};