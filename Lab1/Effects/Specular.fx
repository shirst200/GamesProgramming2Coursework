float4x4 matWorld:WORLD<string UIWidget="NONE";>;
float4x4 matView:VIEW<string UIWidget="NONE";>;
float4x4 matProjection:PROJECTION<string UIWidget="NONE";>;

float4 ambientMaterial;
//<
//	string UIName="Ambient Material";
//	string UIWidget="Color";
//>;
float4 ambientLightColour;
//<
	//string UIName="Ambient Light Color";
	//string UIWidget="Color";
//>;
float4 diffuseMaterial;
//<
	//string UIName="Diffuse Material";
	//string UIWidget="Color";
//>;
float4 diffuseLightColour;
//<
	//string UIName="Diffuse Light Color";
	//string UIWidget="Color";
//>;
float3 lightDirection:DIRECTION;
//<
	//string Object="DirectionalLight";
//>;
float4 cameraPosition;
float4 speculatMaterial;
//<
	//string UIName="Specular material";
	//string UIWidget="Color";
//>;
float4 specularLightColour;
//<
	//string UIName="Specular Light Color";
	//string UIWidget="Color";
//>;
float specularPower;
//<
	//string UIName="Specular Power";
	//string UIWidget="Slider";
	//float UIMin = 0.0; 
	//float UIMax = 50.0; 
	//float UIStep = 1.0; 

//>;

float seconds:TIME;

struct VS_INPUT
{
	float4 pos:POSITION;
	float3 normal:NORMAL;
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float4 cameraDirection:VIEWDIR;
	float3 normal:NORMAL;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	
	float4x4 matViewProjection=mul(matView,matProjection);
	float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
	float4 worldPos=mul(input.pos,matWorld);
	
	output.cameraDirection=normalize(cameraPosition-worldPos);
	output.pos=mul(input.pos,matWorldViewProjection);
	output.normal=mul(input.normal,matWorld);
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float3 normal=normalize(input.normal);
	float3 lightDir=normalize(lightDirection);
	float diffuseHeightlight=saturate(dot(normal,lightDir));
	float3 halfVec=normalize(lightDir+input.cameraDirection);
	float specular=pow(saturate(dot(normal,halfVec)),50.0f);
	return (ambientMaterial*ambientLightColour)+(diffuseMaterial*diffuseLightColour*diffuseHeightlight)+(speculatMaterial*specularLightColour*specular);
	}

RasterizerState DisableCulling
{
	CullMode = NONE;
};

technique10 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0,VS()));
		SetGeometryShader( NULL );
		SetPixelShader(CompileShader( ps_4_0, PS()));
		SetRasterizerState(DisableCulling);
	}
}
