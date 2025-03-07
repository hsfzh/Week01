struct VS_INPUT
{
    float4 position : POSITION; 
    float4 color : COLOR;       
};

struct PS_INPUT
{
    float4 position : SV_POSITION; 
    float4 color : COLOR;          
};

cbuffer constants : register(b0)
{
    row_major float4x4 primitive;
    row_major float4x4 view;
    row_major float4x4 perspective;
}

PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;
    
    float4 position = input.position;
    position = mul(primitive, position);
    position = mul(view, position);
    output.position = mul(perspective, position);

    output.color = input.color;

    return output;
}

float4 mainPS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
