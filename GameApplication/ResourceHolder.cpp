#include "ResourceHolder.h"
#include "../GameApplication/GameApplication.h"

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

bool ResourceHolder::DeleteAllTextures()
{
	for (iterText = texture.begin(); iterText != texture.end(); ++iterText)
	{
		delete (*iterText).second;
		iterText=texture.erase(iterText);
	}
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

bool ResourceHolder::DeleteAllEffects()
{
	for (iterEffect = effect.begin(); iterEffect != effect.end(); ++iterEffect)
	{
		delete (*iterEffect).second;
		iterEffect=effect.erase(iterEffect);
	}
	return true;
}

GameObject* ResourceHolder::GetMesh(LPCSTR fileName, IRenderer *pRenderer)
{
	//Searches for mesh
	if(mesh.find(fileName)==mesh.end())
	{
		//If not found add and return it
		string file=string(fileName);
        string extension=file.substr(file.find('.')+1);

        if (extension.compare("fbx")==0)
                mesh[fileName]=RetreveMesh(fileName,pRenderer);

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

bool ResourceHolder::DeleteAllMeshes()
{
	for (iterMesh = mesh.begin(); iterMesh != mesh.end(); ++iterMesh)
	{
		delete (*iterMesh).second;
		iterMesh=mesh.erase(iterMesh);
	}
	return true;
}

GameObject* ResourceHolder::RetreveMesh(LPCSTR fileName, IRenderer *pRenderer)
{
	//Null Game Object
        GameObject *pRootObject=NULL;
        int noVerts=0;
        int noIndices=0;
        int *pIndices=NULL;
        Vertex * pVerts=NULL;

        FbxManager* lSdkManager = FbxManager::Create();
        FbxIOSettings *ios = FbxIOSettings::Create(lSdkManager, IOSROOT);
    lSdkManager->SetIOSettings(ios);

    // Create an importer using our sdk manager.
    FbxImporter* lImporter = FbxImporter::Create(lSdkManager,"");
        FbxGeometryConverter converter( lSdkManager);

    // Use the first argument as the filename for the importer.
		string file=string(fileName);
        if(!lImporter->Initialize(file.c_str(), -1, lSdkManager->GetIOSettings())) {
			OutputDebugStringA(lImporter->GetStatus().GetErrorString());
                return NULL;
    }

        // Create a new scene so it can be populated by the imported file.
    FbxScene* lScene = FbxScene::Create(lSdkManager,"myScene");
        FbxAxisSystem SceneAxisSystem = lScene->GetGlobalSettings().GetAxisSystem();


    INT iUpAxisSign;
        FbxAxisSystem::EUpVector UpVector = SceneAxisSystem.GetUpVector( iUpAxisSign );

    // Import the contents of the file into the scene.
    lImporter->Import(lScene);

    // The file has been imported; we can get rid of the importer.
    lImporter->Destroy();
        FbxNode* lRootNode = lScene->GetRootNode();
        FbxMesh * pMesh=NULL;
        if(lRootNode) {
                pRootObject=new GameObject();
                pRootObject->setName(lRootNode->GetName());
                for (int i=0;i<lRootNode->GetChildCount();i++){
                        FbxNode * modelNode=lRootNode->GetChild(i);
                        for(int i=0;i<modelNode->GetNodeAttributeCount();i++)
                        {
                                FbxNodeAttribute *pAttributeNode=modelNode->GetNodeAttributeByIndex(i);
                                if (pAttributeNode->GetAttributeType()==FbxNodeAttribute::eMesh)
                                {
                                        //found mesh
                                        pMesh=(FbxMesh*)pAttributeNode;
                                        if (pMesh)
                                        {
                                                GameObject *pChildGO=new GameObject();
                                                pChildGO->setName(pMesh->GetName());
                                                pMesh=converter.TriangulateMesh(pMesh);
                                                FbxVector4 * verts=pMesh->GetControlPoints();
                                                int noVerts=pMesh->GetControlPointsCount();

                                                int noIndices=pMesh->GetPolygonVertexCount();
                                                int *pIndices=pMesh->GetPolygonVertices();

                                                Vertex * pVerts=new Vertex[noVerts];
                                                for(int i=0;i<noVerts;i++)
                                                {

                                                                pVerts[i].position.x=verts[i][0];
                                                                pVerts[i].position.y=verts[i][1];
                                                                pVerts[i].position.z=verts[i][2];
                                                }
                                                for (int iPolygon = 0; iPolygon < pMesh->GetPolygonCount(); iPolygon++) { 
                                                        for (unsigned iPolygonVertex = 0; iPolygonVertex < 3; iPolygonVertex++) {        
                                                                int fbxCornerIndex = pMesh->GetPolygonVertex(iPolygon, iPolygonVertex);
                                                                FbxVector4 fbxVertex = verts[fbxCornerIndex];

                                                                FbxVector4 fbxNormal;        
                                                                pMesh->GetPolygonVertexNormal(iPolygon, iPolygonVertex, fbxNormal);        
                                                                fbxNormal.Normalize();        
                                                                pVerts[fbxCornerIndex].normal.x=fbxNormal[0];
                                                                pVerts[fbxCornerIndex].normal.y=fbxNormal[1];
                                                                pVerts[fbxCornerIndex].normal.z=fbxNormal[2];

                                                                FbxVector2 fbxUV = FbxVector2(0.0, 0.0);        
                                                                FbxLayerElementUV* fbxLayerUV = pMesh->GetLayer(0)->GetUVs();
                                                                // Get texture coordinate        
                                                                if (fbxLayerUV) {                
                                                                        int iUVIndex = 0;                
                                                                        switch (fbxLayerUV->GetMappingMode()) {        
                                                                                case FbxLayerElement::eByControlPoint:
                                                                                        iUVIndex = fbxCornerIndex;                                
                                                                                break;        
                                                                                case FbxLayerElement::eByPolygonVertex:
                                                                                        iUVIndex = pMesh->GetTextureUVIndex(iPolygon, iPolygonVertex, FbxLayerElement::eTextureDiffuse);        
                                                                                break;                
                                                                        }                
                                                                        fbxUV = fbxLayerUV->GetDirectArray().GetAt(iUVIndex);        
                                                                        pVerts[fbxCornerIndex].textureCoords.x=fbxUV[0];
                                                                        pVerts[fbxCornerIndex].textureCoords.y= 1.0f-fbxUV[1];
                                                                }
                                                        }
                                                }

                                                VisualComponent *pVisualComponent=new VisualComponent();
                                                pVisualComponent->createVertexBuffer(noVerts,pVerts,pRenderer);
                                                pVisualComponent->createIndexBuffer(noIndices,pIndices,pRenderer);
                                                pChildGO->addComponent(pVisualComponent);
                                                pRootObject->addChild(pChildGO);
                                                if (pVerts)
                                                {
                                                        delete [] pVerts;
                                                        pVerts=NULL;
                                                }
                                        }
                                }
                        }
                }
        }

        return pRootObject;
}