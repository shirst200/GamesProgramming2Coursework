#include "Material.h"


#include "../D3D10Renderer/D3D10Renderer.h"

//gets the effect
bool Material::loadEffect(const string& filename,IRenderer * pRenderer)
{
        D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);


        m_pEffect=pD3D10Renderer->loadEffectFromFile(filename.c_str());
        if (!m_pEffect)
        {
                return false;
        }
        m_pCurrentTechnique=m_pEffect->GetTechniqueByIndex(0);
        return true;
}

//gets the textures usinfg a file name
bool Material::loadDiffuseTexture(const string& filename,IRenderer *pRenderer)
{
        D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);
        m_pDiffuseTexture=pD3D10Renderer->loadTexture(filename.c_str());
        if (!m_pDiffuseTexture)
        {
                return false;
        }
        return true;
}


bool Material::loadSpecularTexture(const string& filename,IRenderer *pRenderer)
{
        D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);
        m_pSpecularTexture=pD3D10Renderer->loadTexture(filename.c_str());
        if (!m_pSpecularTexture)
        {
                return false;
        }
        return true;
}

bool Material::loadHeightTexture(const string& filename,IRenderer *pRenderer)
{
        D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);
        m_pHeightTexture=pD3D10Renderer->loadTexture(filename.c_str());
        if (!m_pHeightTexture)
        {
                return false;
        }
        return true;
}

void Material::switchTechnique(const string& name)
{
        if (m_pEffect)
        {
                m_pCurrentTechnique=m_pEffect->GetTechniqueByName(name.c_str());
                }
}