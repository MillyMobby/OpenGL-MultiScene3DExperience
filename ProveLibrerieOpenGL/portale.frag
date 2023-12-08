#version 330 core
out vec4 FragColor;
  

in vec2 TexCoord;

uniform sampler2D tex;

void main()
{
    vec4 texColor = texture(tex, TexCoord);
    if(texColor.a < 0.3)
        discard;
    FragColor = texColor;

    //FragColor = vec4(1.0, 0.0, 0.0, 1.0);
   
}