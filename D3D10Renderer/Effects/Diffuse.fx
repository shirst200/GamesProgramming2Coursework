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

struct VS_INPUT
{
	float4 pos:POSITION;
	float3 normal:NORMAL;
};

struct PS_INPUT
{
	float4 pos:SV_POSITION;
	float3 normal:NORMAL;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output=(PS_INPUT)0;
	
	float4x4 matViewProjection=mul(matView,matProjection);
	float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
	
	output.pos=mul(input.pos,matWorldViewProjection);
	output.normal=mul(input.normal,matWorld);
	return output;
}

float4 PS(PS_INPUT input):SV_TARGET
{
	float3 normal=normalize(input.normal);
	float3 lightDir=normalize(lightDirection);
	float diffuseHeightlight=saturate(dot(normal,lightDir));
	return float4((ambientMaterial*ambientLightColour)+(diffuseMaterial*diffuseLightColour*diffuseHeightlight));
	//return float4(1.0f,1.0f,1.0f,1.0f);
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
