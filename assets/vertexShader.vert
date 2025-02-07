#version 450

layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(binding = 0) uniform uTransformData
{
    float uf_x;
    float uf_y;
    float uf_rot;
    float uf_sx;
    float uf_sy;
    float uf_alpha;
    float uf_z;
};

layout(location = 0) out vec2 TexCoord;
layout(location = 1) out float Alpha;

void main()
{
    vec2 transformedPos = aPos;

    // I really should use matrices but.. honestly i dont want to bug the poor people of FTU anymore so this will do for now.

    // Rotate
    float s = sin(uf_rot);
    float c = cos(uf_rot);
    transformedPos.x = transformedPos.x * c - transformedPos.y * s;
    transformedPos.y = transformedPos.x * s + transformedPos.y * c;

    // Transform
    transformedPos += vec2(uf_x,uf_y);

    // Scale
    transformedPos *= vec2(uf_sx,uf_sy);

    TexCoord = aTexCoord;
    gl_Position = vec4(transformedPos.x, transformedPos.y, uf_z, 1.0f);


    Alpha = uf_alpha;
}