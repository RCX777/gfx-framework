#version 330

// Input
in vec2 f_texture_coord;

// Uniform properties
uniform sampler2D texture_1;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // student: Apply the texture
    out_color = texture2D(texture_1, f_texture_coord);

    // student: Discard when alpha component < 0.75
    if (out_color.a < 0.75) {
        discard;
    }
}
