float4x4 matWorld:WORLD<string UIWidget="None";>;
float4x4 matView:VIEW<string UIWidget="None";>;
float4x4 matProjection:PROJECTION<string UIWidget="None";>;


//Ambient
float4 ambientMaterial<
        string UIName="Ambient Material";
        string UIWidget="Color";
> =float4(0.5f,0.5f,0.5f,1.0f);


float4 diffuseMaterial<
        string UIName="Diffuse Material";
        string UIWidget="Color";
> =float4(0.8f,0.8f,0.8f,1.0f);


float4 specularMaterial<
        string UIName="Specular Material";
        string UIWidget="Color";
> =float4(1.0f,1.0f,1.0f,1.0f);


float4 ambientLightColour:AMBIENT;


float4 lightDirection:DIRECTION<
        string Object = "DirectionalLight";
>;


float4 diffuseLightColour:DIFFUSE<
        string Object = "DirectionalLight";
> =float4(1.0f,1.0f,1.0f,1.0f);


float4 specularLightColour:SPECULAR<
        string Object = "DirectionalLight";
> =float4(1.0f,1.0f,1.0f,1.0f);


float specularPower<
        string UIName="Specular Power";
        string UIWidget="Slider";
        float UIMin = 0.0;
        float UIMax = 100.0;
        float UIStep = 5.0;
> =25.0f;


float4 cameraPosition:POSITION<
        string Object ="Perspective";
>;


Texture2D diffuseTexture;
Texture2D specularTexture;


SamplerState wrapSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};


struct VS_INPUT
{
        float4 pos:POSITION;
        float2 texCoord:TEXCOORD;
        float3 normal:NORMAL;
};


struct PS_INPUT
{
        float4 pos:SV_POSITION;
        float3 normal:NORMAL;
        float3 cameraDirection:VIEWDIR;
        float3 lightDir:LIGHTDIR;
        float2 texCoord:TEXCOORD;
};


PS_INPUT VS(VS_INPUT input)
{
        PS_INPUT output=(PS_INPUT)0;
        
        float4x4 matViewProjection=mul(matView,matProjection);
        float4x4 matWorldViewProjection=mul(matWorld,matViewProjection);
        float4 worldPos=mul(input.pos,matWorld);
        output.normal=normalize(mul(input.normal,matWorld));
        output.cameraDirection=mul(normalize(cameraPosition-worldPos),matWorld);
        output.lightDir=lightDirection;                        
        
        
        output.pos=mul(input.pos,matWorldViewProjection);


        output.texCoord=input.texCoord;
        return output;
}




float4 PS(PS_INPUT input):SV_TARGET
{
        float3 normal=input.normal;        
        float3 lightDir=normalize(input.lightDir);
        
        float4 diffuseColour=diffuseMaterial;
        float4 specularColour=specularMaterial;
                
        float diffuse=saturate(dot(normal,lightDir));
        
        float3 halfVec=normalize(lightDir+input.cameraDirection);
        float specular=pow(saturate(dot(normal,halfVec)),specularPower);
        
        return ((ambientMaterial*ambientLightColour)+
        (diffuseColour*diffuseLightColour*diffuse)+
        (specularColour*specularLightColour*specular));
}


RasterizerState DisableCulling
{
    CullMode = NONE;
};


technique10 Render
{
        pass P0
        {
                SetVertexShader(CompileShader(vs_4_0, VS() ) );
                SetGeometryShader( NULL );
                SetPixelShader( CompileShader( ps_4_0,  PS() ) );
                SetRasterizerState(DisableCulling); 
        }
}
