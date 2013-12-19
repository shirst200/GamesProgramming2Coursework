float4x4 matWorld:WORLD<string UIWidget="NONE";>;
float4x4 matView:VIEW<string UIWidget="NONE";>;
float4x4 matProjection:PROJECTION<string UIWidget="NONE";>;

float4 ambientMaterial
<
	string UIName="Ambient Material";
	string UIWidget="Color";
>;
float4 ambientLightColour
<
	string UIName="Ambient Light Color";
	string UIWidget="Color";
>;
float4 diffuseMaterial
<
	string UIName="Diffuse Material";
	string UIWidget="Color";
>;
float4 diffuseLightColour
<
	string UIName="Diffuse Light Color";
	string UIWidget="Color";
>;
float3 lightDirection:DIRECTION
<
	string Object="DirectionalLight";
>;
float4 cameraPosition;
float4 speculatMaterial
<
	string UIName="Specular material";
	string UIWidget="Color";
>;
float4 specularLightColour
<
	string UIName="Specular Light Color";
	string UIWidget="Color";
>;
float specularPower
<
	string UIName="Specular Power";
	string UIWidget="Slider";
	float UIMin = 0.0; 
	float UIMax = 50.0; 
	float UIStep = 1.0; 

>;
struct VS_INPUT
{
	float4 pos:POSITION;
	float3 normal:NORMAL;
	float3 tangent:TANGENT;
	float2 texCoord:TEXCOORD0;
};

Texture2D diffuseMap;
Texture2D bumpMap;
Texture2D heightMap;
SamplerState WrapPointSampler
{
	Filter = MIN_MAG_LINEAR_MIP_POINT;
	AddressU = Wrap;
	AddressV = Wrap;
};
struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 cameraDirection:VIEWDIR;
	float3 normal:NORMAL;
	float3 lightDir:LIGHTDIR;
	float2 texCoord:TEXCOORD0;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	
	float4x4 matViewProjection=mul(matView,matProjection);
	float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
	
	float3x3 worldToTangent;
	worldToTangent[0]=mul(input.tangent,matWorld);
	worldToTangent[1]=mul(cross(input.tangent,input.normal),matWorld);
	worldToTangent[2]=mul(input.normal,matWorld);
	
	output.pos=mul(input.pos,matWorldViewProjection);
	output.normal=mul(input.normal,worldToTangent);
	float4 worldPos=mul(input.pos,matWorld);
	output.cameraDirection=mul((cameraPosition-worldPos.xyz),worldToTangent);
	output.lightDir=mul(lightDirection,worldToTangent);
	output.texCoord=input.texCoord;
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float scale=0.03;
	float bias=0.01;
	
	float heightVal=heightMap.Sample(WrapPointSampler,input.texCoord).x;
	float height=scale*heightVal-bias;
	
	float2 newTexCoord=height*input.cameraDirection.xy+input.texCoord;
	
	float3 normal=normalize((2*(bumpMap.Sample(WrapPointSampler,input.texCoord)))-1.0);
	float3 lightDir=normalize(input.lightDir);
	float diffuseHeightlight=saturate(dot(normal,lightDir));
	float3 halfVec=normalize(lightDir+input.cameraDirection);
	float specular=pow(saturate(dot(normal,halfVec)),50.0f);
	float4 diffuseTextureColour=diffuseMap.Sample(WrapPointSampler,newTexCoord);
	return float4(((speculatMaterial*specularLightColour*specular)+(ambientMaterial*ambientLightColour)+((diffuseMaterial+diffuseTextureColour)*diffuseLightColour*diffuseHeightlight)));
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
