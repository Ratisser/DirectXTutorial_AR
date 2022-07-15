
struct VS_INPUT
{
    float4 Position : POSITION;
};

struct PS_INPUT
{
    float4 Position : SV_Position;
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    output.Position = input.Position * 100.f;
    return output;
}

float4 PS(PS_INPUT input) : SV_Target0
{
    float4 color = { 1.0f, 0.0f, 0.0f, 1.0f };
    return color;
}