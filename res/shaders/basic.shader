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

void main() {
    gl_Position = position;
}

//Outputs a color (a vec4 in rgba floats format)
#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main() {
    color = vec4(0.2, 0.3, 0.8, 1.0);
}