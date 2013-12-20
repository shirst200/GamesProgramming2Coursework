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
	//Directional light has a direction
        XMFLOAT3 m_LightDirection;
		//used to implement the roating light
		//rotate is set to 1 if we want the light to rotate
		int rotate;
		//the value of time we use for calculating the rotation
		float count;
		//used to check if it is the first time we are calculating the rotating direction
		int check;
};