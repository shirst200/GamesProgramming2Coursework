#pragma once


#include "GameComponent.h"


#include <windows.h>
#define _XM_NO_INTRINSICS_
#include <xnamath.h>


#include <D3D10.h>
#include "../Renderer/Renderer.h"


#include <string>


using namespace std;


class Material:public GameComponent
{
public:
        Material()
        {
			//initislaises the variables
                m_Name="Material";
                m_pEffect=NULL;
                m_pCurrentTechnique=NULL;
                m_Ambient=XMFLOAT4(0.5f,0.5f,0.5f,0.5f);
                m_Diffuse=XMFLOAT4(0.5f,0.5f,0.5f,0.5f);
                m_Specular=XMFLOAT4(1.0f,1.0f,1.0f,1.0f);
                m_pDiffuseTexture=NULL;
                m_pSpecularTexture=NULL;
        };

		//Deconstructor
        ~Material()
        {
                if (m_pDiffuseTexture)
                {
                        m_pDiffuseTexture->Release();
                        m_pDiffuseTexture=NULL;
                }
                if (m_pSpecularTexture)
                {
                        m_pSpecularTexture->Release();
                        m_pSpecularTexture=NULL;
                }
                if (m_pEffect)
                {
                        m_pEffect->Release();
                        m_pEffect=NULL;
                }
        };

		//sets the ambient colour
        void setAmbient(float r,float g,float b,float a)
        {
                m_Ambient=XMFLOAT4(r,g,b,a);
        };


        XMFLOAT4& getAmbient()
        {
                return m_Ambient;
        };


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


        bool loadEffect(const string& filename,IRenderer * pRenderer);
        void switchTechnique(const string& name);


        ID3D10Effect * getEffect()
        {
                return m_pEffect;
        };


        ID3D10EffectTechnique * getCurrentTechnique()
        {
                return m_pCurrentTechnique;
        };

		//loads textures from files
        bool loadDiffuseTexture(const string& filename,IRenderer *pRenderer);
        bool loadSpecularTexture(const string& filename,IRenderer *pRenderer);
		bool loadHeightTexture(const string& filename,IRenderer *pRenderer);

        ID3D10ShaderResourceView * getDiffuseTexture()
        {
                return m_pDiffuseTexture;
        };


        ID3D10ShaderResourceView * getSpecularTexture()
        {
                return m_pSpecularTexture;
        };

		ID3D10ShaderResourceView * getHeightTexture()
        {
                return m_pSpecularTexture;
        };

private:
	//holds the colour values
        XMFLOAT4 m_Ambient;
        XMFLOAT4 m_Diffuse;
        XMFLOAT4 m_Specular;
		//holds the effect
        ID3D10Effect *m_pEffect;
        ID3D10EffectTechnique *m_pCurrentTechnique;
		//holds the tetures
        ID3D10ShaderResourceView * m_pDiffuseTexture;
        ID3D10ShaderResourceView * m_pSpecularTexture;
		ID3D10ShaderResourceView * m_pHeightTexture;
};
