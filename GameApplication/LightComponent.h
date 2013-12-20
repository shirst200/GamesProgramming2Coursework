
#pragma once


#include "GameComponent.h"


#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>




class LightComponent:public GameComponent
{
public:
        LightComponent()
        {
				//Innitialises the colour values
                m_Name="Light";
                m_Diffuse=XMFLOAT4(0.8f,0.8f,0.8f,1.0f);
                m_Specular=XMFLOAT4(0.1f,0.1f,0.1f,1.0f);
        };


        virtual ~LightComponent(){};

		//sets the diffuse value
        void setDiffuse(float r,float g,float b,float a)
        {
                m_Diffuse=XMFLOAT4(r,g,b,a);
        };

		//returns the diffuse value
        XMFLOAT4& getDiffuse()
        {
                return m_Diffuse;
        };

		//sets the specular
        void setSpecular(float r,float g,float b,float a)
        {
                m_Specular=XMFLOAT4(r,g,b,a);
        };

		void update(float dt);
		//returns the specular
        XMFLOAT4& getSpecular()
        {
                return m_Specular;
        };
protected:
	//Light only has a colour
        XMFLOAT4 m_Diffuse;
        XMFLOAT4 m_Specular;
};
