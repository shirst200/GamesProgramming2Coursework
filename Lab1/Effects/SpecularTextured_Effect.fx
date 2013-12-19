float4x4 matWorld:WORLD<string UIWidget="NONE";>;
float4x4 matView:VIEW<string UIWidget="NONE";>;
float4x4 matProjection:PROJECTION<string UIWidget="NONE";>;

//float4 ambientMaterial={0.5f,0.5f,0.5f,1.0};

//float4 ambientLightColour={0.5f,0.5f,0.5f,1.0f};

float4 ambientMaterial:COLOR
<
	string UIName="Ambient Material";
	string UIWidget="Color";
>;
float4 ambientLightColour:COLOR
<
	string UIName="Ambient Light Color";
	string UIWidget="Color";
>;

//float4 diffuseMaterial={1.0f,0.0225f,0.0442f,1.0f};
float4 diffuseMaterial
<
	string UIName="Diffuse Material";
	string UIWidget="Color";
>;
//float4 diffuseLightColour={0.943f,1.0f,1.0f,1.0f};
float4 diffuseLightColour
<
	string UIName="Diffuse Light Color";
	string UIWidget="Color";
>;
//float3 lightDirection={1.0f,1.0f,-1.0f};
float3 lightDirection:DIRECTION;
//<
	//string Object="DirectionalLight";
//>;
float4 cameraPosition;
//float4 speculatMaterial={1.0f,1.0f,1.0f,1.0f};
float4 speculatMaterial
<
	string UIName="Specular material";
	string UIWidget="Color";
>;
//float4 specularLightColour={1.0f,1.0f,1.0f,1.0f};
float4 specularLightColour
<
	string UIName="Specular Light Color";
	string UIWidget="Color";
>;
float specularPower;
//<
	//string UIName="Specular Power";
	//string UIWidget="Slider";
	//float UIMin = 0.0; 
	//float UIMax = 50.0; 
	//float UIStep = 1.0; 

//>;
float time:TIME;
struct VS_INPUT
{
	float4 pos:POSITION;
	float3 normal:NORMAL;
	float2 texCoord:TEXCOORD0;
	float3 tangent:TANGENT;
};
Texture2D diffuseMap;
SamplerState WrapPointSampler
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float4 cameraDirection:VIEWDIR;
	float3 normal:NORMAL;
	float2 texCoord:TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	output.texCoord=input.texCoord;
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
	float specular=pow(saturate(dot(normal,halfVec)),30.0f);
	return float4(((speculatMaterial*specularLightColour*specular)+(ambientMaterial*ambientLightColour)+(diffuseMaterial*diffuseLightColour*diffuseHeightlight))*diffuseMap.Sample(WrapPointSampler,input.texCoord));
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
