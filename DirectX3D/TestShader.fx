
// Vertex Shader
float4 VS_Test(float4 Pos : POSITION) : SV_POSITION
{
    return Pos;
}

// Pixel Shader
float4 PS_Test(float4 Pos : SV_POSITION) : SV_TARGET
{
    return float4(1.f, 0.f, 0.f, 1.f);
}


