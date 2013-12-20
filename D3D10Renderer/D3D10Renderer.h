#pragma once

//http://www.gamedev.net/topic/506017-quick-question-about-id3d10inputlayout/
//The header file for the renderer interface
#include "../Renderer/Renderer.h"

#include <Windows.h>

#include <D3D10.h>
#include <D3DX10.h>

#define _XM_NO_INTRINSICS_
#include <xnamath.h>
#include <queue>
#include <vector>

#include "Vertex.h"

//D3D10Renderer implements the Renderer interface
class D3D10Renderer:public IRenderer
{
public:
        D3D10Renderer();
        ~D3D10Renderer();
        //notice these have the same signature as the pure methods
        //in the interface
        bool init(void *pWindowHandle,bool fullScreen);
        void clear(float r,float g,float b,float a);
        void present();
        void render();

        ID3D10Effect * loadEffectFromMemory(const char *pMem);
        ID3D10Effect * loadEffectFromFile(const char *pFilename);

        ID3D10Buffer * createVertexBuffer(int size,Vertex *pVerts);
        ID3D10Buffer * createIndexBuffer(int size,int *pIndices);
        ID3D10InputLayout * createVertexLayout(ID3D10Effect * pEffect);

        ID3D10ShaderResourceView * loadTexture(const char *pFilename);
        void addToRenderQueue(GameObject *pObject);

        void setProjection(XMMATRIX& projection)
        {
                m_Projection=projection;
        };

        void setView(XMMATRIX& view)
        {
                m_View=view;
        };
		//Sets the ambient light colour
        void setAmbientLightColour(float r,float g,float b,float a)
        {
                m_AmbientLightColour=XMFLOAT4(r,g,b,a);
        };

private:
        bool createDevice(HWND pWindowHandle,int windowWidth, int windowHeight,
bool fullScreen);
        bool createInitialRenderTarget(int windowWidth, int windowHeight);

        void render(GameObject *pCurrentObject);
private:
        typedef std::queue<GameObject*> RenderQueue;
		
        //D3D10 stuff
        ID3D10Device * m_pD3D10Device;
        IDXGISwapChain * m_pSwapChain;
        ID3D10RenderTargetView * m_pRenderTargetView;
        ID3D10DepthStencilView * m_pDepthStencelView;
        ID3D10Texture2D *m_pDepthStencilTexture;

        //Vertex Layout
        ID3D10InputLayout*      m_pDefaultVertexLayout;
        //this will be used if we have no Effect
        ID3D10Effect * m_pDefaultEffect;
        ID3D10EffectTechnique * m_pDefaultTechnique;

        RenderQueue m_RenderQueue;

        XMMATRIX m_View;
        XMMATRIX m_Projection;
		// Holds the Colour values for the main light
        XMFLOAT4 m_AmbientLightColour;
		XMFLOAT4 m_specularLightColour;
		XMFLOAT4 m_diffuseLightColour;
		XMFLOAT3 lightDirection;
		//Holds the main cameras position
		XMFLOAT3 m_camera;
		//Holds the MainCamera and Light
        GameObject * m_pMainCamera;
        GameObject * m_pMainLight;
};