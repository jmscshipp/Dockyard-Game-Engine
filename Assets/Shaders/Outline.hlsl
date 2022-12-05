#pragma pack_matrix( row_major )

//  Constant Buffers
cbuffer CamData : register(b0)
{
	float4x4 View;
	float4x4 Projection;
};

cbuffer InstanceData : register(b1)
{
    float4x4 World;
    float4 SelectedColor;
    float OutlineSize;
};

// ******* Shader operations

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float4 PosMS : POSITION;
	float4 Norm : NORMAL;
    float4 Color : COLOR;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS( float4 Pos : POSITION, float4 Nor : NORMAL )
{
    float4 adjustedPos = Pos + normalize(Pos) * OutlineSize;
    adjustedPos.w = 1.0f;
    
    VS_OUTPUT output;
    output.Pos = mul(adjustedPos, World);
    output.Pos = mul(output.Pos, View);
    output.Pos = mul(output.Pos, Projection);
    output.Color = SelectedColor;
    return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS( VS_OUTPUT input ) : SV_Target
{
    return input.Color;
}
