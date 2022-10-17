#shader vertex
#version 330 core

//After the draw call shaders are called sequentially
//Two kinds of shaders:
//- Vertex Shaders (called for each vertex you're trying to render)
//      Its primary purpose is to define where you should be seeing the vertices
//- Fragment Shaders
//      Also called pixel shader | is called when each pixel on the screen is rasterized
//      Primary purpose is to determine the color each pixel should be
//- other shaders

//Location = 0 is the id of the vertex attribute pointer
//vec4 because gl_Position wants a vec4 (you can create a vec2 and convert it later tho)
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

//Varying to pass texture coordinates to the fragment shader
out vec2 v_TexCoord;

void main() {
    gl_Position = position;
    v_TexCoord = texCoord;
}

//Outputs a color (a vec4 in rgba floats format)
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

//Varying to accept texture coordinates in the fragment shader
in vec2 v_TexCoord;

//Convention: what starts with u_ is a uniform variable
uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main() {
    //We need to send texCoords from the vertex shader to the fragment shader
    //we can do that with something called varying
    vec4 texColor = texture(u_Texture, v_TexCoord);
    //Assigning color [The output color of each fragment [pixel]] to the uniform color
    color = texColor;
    //Old fixed color
    //vec4(0.2, 0.3, 0.8, 1.0);

    //Old Pulsing color
    //color = uColor
}