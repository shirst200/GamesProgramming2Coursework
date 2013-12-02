//#pragma once
//
//#include "GameComponent.h"
//#include "../Renderer/Renderer.h"
//#include "Windows.h"
//#define _XM_NO_INTRINSICS_
//#include <xnamath.h>
//#include <D3D10.h>
//#include <D3DX10.h>
//
//class LightComponent:public GameComponent
//{
//public:
//	LightComponent()
//	{
//		m_Name="Light";
//		m_Diffuse=XMCOLOR(0.8f,0.8f,0.8f,1.0f);
//        m_Specular=XMCOLOR(1.0f,1.0f,1.0f,1.0f);
//
//
//	};
//
//	 virtual ~LightComponent(){};
//
//	void setDiffuse(float r, float g, float b, float a)
//	{
//		m_Diffuse=XMCOLOR(r,g,b,a);
//	};
//
//	void setSpecular(float r, float g, float b, float a)
//	{
//		m_Specular=XMCOLOR(r,g,b,a);
//	};
//
//	XMCOLOR& getDiffuse()
//	{
//		return m_Diffuse;
//	};
//	
//	XMCOLOR& getSpecular()
//	{
//		return m_Specular;
//	};
//private:
//	//Represents te diffuse colour of the light
//	XMCOLOR m_Diffuse;
//	//Represents the specular colour of the light
//	XMCOLOR m_Specular;
//
//}

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
                m_Diffuse=XMCOLOR(0.8f,0.8f,0.8f,1.0f);
                m_Specular=XMCOLOR(1.0f,1.0f,1.0f,1.0f);
        };


        virtual ~LightComponent(){};


        void setDiffuse(float r,float g,float b,float a)
        {
                m_Diffuse=XMCOLOR(r,g,b,a);
        };


        XMCOLOR& getDiffuse()
        {
                return m_Diffuse;
        };


        void setSpecular(float r,float g,float b,float a)
        {
                m_Specular=XMCOLOR(r,g,b,a);
        };


        XMCOLOR& getSpecular()
        {
                return m_Specular;
        };
protected:
        XMCOLOR m_Diffuse;
        XMCOLOR m_Specular;
};

