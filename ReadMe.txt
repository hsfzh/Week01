각속도 코드
PS_INPUT mainVS(VS_INPUT input)
{
    PS_INPUT output;

    float3 scaledPos = input.position.xyz * Radius;

    float cosTheta = cos(Rotation);
    float sinTheta = sin(Rotation);

    float3 rotatedPos;
    rotatedPos.x = scaledPos.x * cosTheta - scaledPos.y * sinTheta;
    rotatedPos.y = scaledPos.x * sinTheta + scaledPos.y * cosTheta;
    rotatedPos.z = scaledPos.z;

    float3 translatedPos = rotatedPos + Offset;

    output.position = float4(translatedPos, input.position.w);

    output.color = input.color;

    return output;
}
UBall에 Rotation과 AngularVelocity를 추가하여 쉐이더에서 회전
