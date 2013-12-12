#pragma once


#include "LightComponent.h"
#include <time.h>

class DirectionLightComponent:public LightComponent
{
public:
        DirectionLightComponent(){
                m_LightDirection=XMFLOAT3(0.0f,0.0f,-1.0f);
                m_Name="DirectionalLight";
				time(&start);
				count = 0.0f;
        };


        ~DirectionLightComponent(){};

        void setDirection(float x,float y,float z)
        {
                m_LightDirection=XMFLOAT3(x,y,z);
        };

		void update();

        XMFLOAT3& getDirection()
        {
                return m_LightDirection;
        };

private:
        XMFLOAT3 m_LightDirection;
		time_t start;
		time_t current;
		float count;
};