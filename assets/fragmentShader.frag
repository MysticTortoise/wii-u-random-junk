#version 450

layout(location = 0) in vec2 TexCoord;
layout(location = 1) in float Alpha;
/*layout(binding = 0) uniform uf_data
{
    
};*/

layout(location = 0) out vec4 FragColor;

layout(binding = 0) uniform sampler2D spriteTexture;

void main()
{
    FragColor = texture(spriteTexture, TexCoord);
    FragColor.a *= Alpha;
}