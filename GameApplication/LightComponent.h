
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
                m_Name="Light";
                m_Diffuse=XMFLOAT4(0.8f,0.8f,0.8f,1.0f);
                m_Specular=XMFLOAT4(0.1f,0.1f,0.1f,1.0f);
        };


        virtual ~LightComponent(){};


        void setDiffuse(float r,float g,float b,float a)
        {
                m_Diffuse=XMFLOAT4(r,g,b,a);
        };


        XMFLOAT4& getDiffuse()
        {
                return m_Diffuse;
        };


        void setSpecular(float r,float g,float b,float a)
        {
                m_Specular=XMFLOAT4(r,g,b,a);
        };


        XMFLOAT4& getSpecular()
        {
                return m_Specular;
        };
protected:
        XMFLOAT4 m_Diffuse;
        XMFLOAT4 m_Specular;
};
