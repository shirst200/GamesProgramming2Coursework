float4x4 matWorld:WORLD<string UIWidget="NONE";>;
float4x4 matView:VIEW<string UIWidget="NONE";>;
float4x4 matProjection:PROJECTION<string UIWidget="NONE";>;

float4 ambientMaterial={0.5f,0.5f,0.5f,0.5f};
//<
//	string UIName="Ambient Material";
//	string UIWidget="Color";
//>;
float4 ambientLightColour={0.5f,0.5f,0.5f,0.5f};
//<
	//string UIName="Ambient Light Color";
	//string UIWidget="Color";
//>;
float4 diffuseMaterial={1.0f,0.0225f,0.0442f,1.0f};
//<
	//string UIName="Diffuse Material";
	//string UIWidget="Color";
//>;
float4 diffuseLightColour={0.943f,1.0f,1.0f,1.0f};
//<
	//string UIName="Diffuse Light Color";
	//string UIWidget="Color";
//>;
float3 lightDirection={10.0f,1.0f,1.0f};
//<
	//string Object="DirectionalLight";
//>;
float4 cameraPosition={0.0f,0.0f,0.0f,0.0f};
float4 speculatMaterial={1.0f,1.0f,1.0f,1.0f};
//<
	//string UIName="Specular material";
	//string UIWidget="Color";
//>;
float4 specularLightColour={1.0f,1.0f,1.0f,1.0f};
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
	float3 light = float3(sin(seconds), 0.0f, cos(seconds));
	float3 lightDir=normalize(light);
	float diffuseHeightlight=saturate(dot(normal,lightDir));
	float3 halfVec=normalize(lightDir+input.cameraDirection);
	float specular=pow(saturate(dot(normal,halfVec)),25.0f);
	//return float4((speculatMaterial*specularLightColour*specular)+(ambientMaterial*ambientLightColour)+(diffuseMaterial*diffuseLightColour*diffuseHeightlight));
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
