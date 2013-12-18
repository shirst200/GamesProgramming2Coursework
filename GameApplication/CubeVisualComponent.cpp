#include "CubeVisualComponent.h"
#include "../D3D10Renderer/Vertex.h"
#include "../D3D10Renderer/D3D10Renderer.h"

bool CubeVisualComponent::create(IRenderer * pRenderer)
{
	m_iNoVerts=8;
	Vertex verts[8];
	verts[0].position=XMFLOAT3(-0.5f,-0.5f,0.5f);
	verts[0].normal=XMFLOAT3(-0.25f,-0.25f,0.5f);
	verts[0].textureCoords=XMFLOAT2(0.0f,1.0f);
	

	verts[1].position=XMFLOAT3(-0.5f,0.5f,0.5f);
	verts[1].normal=XMFLOAT3(-0.25f,0.25f,0.5f);
	verts[1].textureCoords=XMFLOAT2(0.0f,0.0f);
	
	verts[2].position=XMFLOAT3(0.5f,-0.5f,0.5f);
	verts[2].normal=XMFLOAT3(0.25f,-0.25f,0.5f);
	verts[2].textureCoords=XMFLOAT2(1.0f,1.0f);

	verts[3].position=XMFLOAT3(0.5f,0.5f,0.5f);
	verts[3].normal=XMFLOAT3(0.25f,0.25f,0.5f);
	verts[3].textureCoords=XMFLOAT2(1.0f,0.0f);
	
	verts[4].position=XMFLOAT3(-0.5f,-0.5f,-0.5f);
	verts[4].normal=XMFLOAT3(-0.25f,-0.25f,-0.5f);
	verts[4].textureCoords=XMFLOAT2(0.0f,1.0f);
	
	verts[5].position=XMFLOAT3(-0.5f,0.5f,-0.5f);
	verts[5].normal=XMFLOAT3(-0.25f,0.25f,-0.5f);
	verts[5].textureCoords=XMFLOAT2(0.0f,0.0f);

	verts[6].position=XMFLOAT3(0.5f,-0.5f,-0.5f);
	verts[6].normal=XMFLOAT3(0.25f,-0.25f,-0.5f);
	verts[6].textureCoords=XMFLOAT2(1.0f,1.0f);
	
	verts[7].position=XMFLOAT3(0.5f,0.5f,-0.5f);
	verts[7].normal=XMFLOAT3(0.25f,0.25f,-0.5f);
	verts[7].textureCoords=XMFLOAT2(1.0f,0.0f);

	computeTangents(verts,m_iNoVerts);

	int indices[]={0,1,2,1,3,2,		//front 
					4,5,6,5,7,6,	//back
					4,5,0,1,0,5,
					2,3,7,6,7,2,
					1,5,7,7,3,1,
					0,4,2,4,6,2
					};
	m_iNoIndices=36;

	D3D10Renderer *pD3D10Renderer=static_cast<D3D10Renderer*>(pRenderer);

	m_pVertexBuffer=pD3D10Renderer->createVertexBuffer(m_iNoVerts,verts);
	m_pIndexBuffer=pD3D10Renderer->createIndexBuffer(m_iNoIndices,indices);
	

	return true;
}
void CubeVisualComponent::computeTangents(Vertex *pVerts,int vertexCount)
{
	 int triCount=vertexCount/3; 
    XMFLOAT3 * tan1=new XMFLOAT3[vertexCount]; 
    XMFLOAT3 * tan2=new XMFLOAT3[vertexCount]; 
  
    for (int i=0;i<triCount;i+=3) 
    { 
        XMFLOAT3 v1=pVerts[i].position; 
        XMFLOAT3 v2=pVerts[i+1].position; 
        XMFLOAT3 v3=pVerts[i+2].position; 
  
        XMFLOAT3 uv1=XMFLOAT3((float*)&pVerts[i].textureCoords); 
        XMFLOAT3 uv2=XMFLOAT3((float*)&pVerts[i+1].textureCoords); 
        XMFLOAT3 uv3=XMFLOAT3((float*)&pVerts[i+2].textureCoords); 
              
        float x1 = v2.x - v1.x; 
        float x2 = v3.x - v1.x; 
        float y1 = v2.y - v1.y; 
        float y2 = v3.y - v1.y; 
        float z1 = v2.z - v1.z; 
        float z2 = v3.z - v1.z; 
  
        float s1 = uv2.x - uv1.x; 
        float s2 = uv3.x - uv1.x; 
        float t1 = uv2.y - uv1.y; 
        float t2 = uv3.y - uv1.y; 
  
        float r=1.0f/(s1*t2-s2*t1); 
        XMFLOAT3 sdir = XMFLOAT3((t2 * x1 - t1 * x2) * r, (t2 * y1 - t1 * y2) * r, (t2 * z1 - t1 * z2) * r); 
        XMFLOAT3 tdir = XMFLOAT3((s1 * x2 - s2 * x1) * r, (s1 * y2 - s2 * y1) * r, (s1 * z2 - s2 * z1) * r); 
  
		tan1[i].x += sdir.x; 
		tan1[i].y += sdir.y; 
		tan1[i].z += sdir.z; 

		tan1[i+1].x += sdir.x; 
		tan1[i+1].y += sdir.y; 
		tan1[i+1].z += sdir.z;

		tan1[i+2].x += sdir.x; 
		tan1[i+2].y += sdir.y; 
		tan1[i+2].z += sdir.z;
  
		tan2[i].x += tdir.x; 
		tan2[i].y += tdir.y; 
		tan2[i].z += tdir.z; 

		tan2[i+1].x += tdir.x; 
		tan2[i+1].y += tdir.y; 
		tan2[i+1].z += tdir.z;

		tan2[i+2].x += tdir.x; 
		tan2[i+2].y += tdir.y; 
		tan2[i+2].z += tdir.z; 
    } 
    for (int i=0;i<vertexCount;i++) 
    { 
		XMFLOAT3 n=pVerts[i].normal; 
        XMFLOAT3 t=tan1[i]; 
		XMVECTOR nDotT=XMVector3Dot(XMLoadFloat3(&n), XMLoadFloat3(&t));
		XMFLOAT3 nDotT3;
		XMStoreFloat3(&nDotT3,nDotT);
		//XMFLOAT3 tmp = t - n * nDotT3); 
		XMFLOAT3 tmp = t;
		tmp.x=tmp.x-n.x*nDotT3.x;
		tmp.y=tmp.y-n.y*nDotT3.y;
		tmp.z=tmp.z-n.z*nDotT3.z;
        XMVECTOR v=XMVector3Normalize(XMLoadFloat3(&tmp)); 
		XMStoreFloat3(&pVerts[i].tangent,v);
		//pVerts[i].tangent = ; 
        //tangents[a].w = (Vector3.Dot(Vector3.Cross(n, t), tan2[a]) < 0.0f) ? -1.0f : 1.0f; 
  
    } 
    if (tan1) 
    { 
        delete [] tan1; 
        tan1=NULL; 
    } 
    if (tan2) 
    { 
        delete [] tan2; 
        tan2=NULL; 
    } 

}