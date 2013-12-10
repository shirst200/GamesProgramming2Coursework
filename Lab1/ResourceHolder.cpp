#include "ResourceHolder.h"

ID3D10Texture2D* ResourceHolder::GetTexture(LPCSTR fileName)
{
	//Searches for the resource
	if(texture.find(fileName)==texture.end())
	{
		//If not found add and return the added value
		ID3D10ShaderResourceView * m_pBaseTextureMap;
		D3DX10CreateShaderResourceViewFromFileA(m_pD3D10Device,fileName,NULL,NULL,&m_pBaseTextureMap,NULL);
		//texture[fileName]=;
		return texture.at(fileName);
	}
	//If found return
	return texture.at(fileName);
}

bool ResourceHolder::DeleteTexture(LPCSTR fileName)
{
	//Searches for the texture
	if(texture.find(fileName)==texture.end())
	{
		//If not found return false
		return false;
	}
	if(FAILED(texture.erase(fileName)))
	{
		//If failed to delete return false
		return false;
	}
	//If texture deleted return true
	return true;
}

ID3D10Effect* ResourceHolder::GetEffect(LPCSTR fileName)
{
	//Searches for effect
	if(effect.find(fileName)==effect.end())
	{
		//If not found add and return it
		DWORD dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
        dwShaderFlags |= D3D10_SHADER_DEBUG;
#endif

        ID3D10Blob * pErrorBuffer=NULL;
        if (FAILED(D3DX10CreateEffectFromFileA(fileName,
                NULL,
                NULL,
                "fx_4_0", //A string which specfies the effect profile to use, in this case fx_4_0(Shader model 4) - BMD
                dwShaderFlags, //Shader flags, this can be used to add extra debug information to the shader - BMD
                0,//Fx flags, effect compile flags set to zero - BMD
			    m_pD3D10Device, //ID3D10Device*, the direct3D rendering device - BMD
                NULL, //ID3D10EffectPool*, a pointer to an effect pool allows sharing of variables between effects - BMD
                NULL, //ID3DX10ThreadPump*, a pointer to a thread pump this allows multithread access to shader resource - BMD
                &m_pTempEffect, //ID3D10Effect**, a pointer to a memory address of the effect object. This will be initialised after this - BMD
                &pErrorBuffer, //ID3D10Blob**, a pointer to a memory address of a blob object, this can be used to hold errors from the compilation - BMD
                NULL )))//HRESULT*, a pointer to a the result of the compilation, this will be NULL - BMD
        {
                OutputDebugStringA((char*)pErrorBuffer->GetBufferPointer());
                return false;
        }
		effect[fileName]=m_pTempEffect;
		holder =(m_pTempEffect->GetTechniqueByName("Render"));

        m_pWorldEffectVariable[fileName]=m_pTempEffect->GetVariableByName("matWorld")->AsMatrix();
        m_pProjectionEffectVariable=m_pTempEffect->GetVariableByName("matProjection")->AsMatrix();
        m_pViewEffectVariable=m_pTempEffect->GetVariableByName("matView")->AsMatrix();
		return effect.at(fileName);
	}
	//If effect found return it
	return effect.at(fileName);
}

bool ResourceHolder::DeleteEffect(LPCSTR fileName)
{
	//Searches for effect
	if(effect.find(fileName)==effect.end())
	{
		//If effect not found return false
		return false;
	}
	if(FAILED(effect.erase(fileName)))
	{
		//If failed to delete effect return false
		return false;
	}
	//If resource was deleted return true
	return true;
}

GameObject * ResourceHolder::GetMesh(LPCSTR fileName)
{
	//Searches for mesh
	if(mesh.find(fileName)==mesh.end())
	{
		//If not found add and return it
		mesh.insert(fileName);

		return mesh.at(fileName);
	}
	//If found return it
	return mesh.at(fileName);
}

bool ResourceHolder::DeleteMesh(LPCSTR fileName)
{
	//Searches for mesh
	if(mesh.find(fileName)==mesh.end())
	{
		//If not found return false
		return false;
	}
	if(FAILED(mesh.erase(fileName)))
	{
		//If failed to delete return false
		return false;
	}
	//If deleted return true
	return true;
}
GameObject* RetreveMesh(LPCSTR fileName, IRenderer *pRenderer)
{

}