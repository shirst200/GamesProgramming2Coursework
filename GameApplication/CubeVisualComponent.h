#include "VisualComponent.h"

class CubeVisualComponent:public VisualComponent
{
public:
	CubeVisualComponent(){};
	~CubeVisualComponent(){};
	void computeTangents(Vertex *pverts, int vertexCount);
	bool create(IRenderer * pRenderer);
};