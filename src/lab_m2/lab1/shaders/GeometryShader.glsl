#version 330

// Input and output topologies
layout(triangles) in;
layout(triangle_strip, max_vertices = 170) out;

// Input
in vec2 g_texture_coord[];

// Uniform properties
uniform mat4 View;
uniform mat4 Projection;
uniform int instances;

// student: Declare other uniforms here
uniform float scale_coeff;

// Output
out vec2 f_texture_coord;


void EmitPoint(vec3 pos, vec3 offset)
{
    gl_Position = Projection * View * vec4(pos + offset, 1.0);
    EmitVertex();
}


void main()
{
    vec3 p1 = gl_in[0].gl_Position.xyz;
    vec3 p2 = gl_in[1].gl_Position.xyz;
    vec3 p3 = gl_in[2].gl_Position.xyz;

    const vec3 INSTANCE_OFFSET = vec3(1.25, 0, 1.25);
    const int NR_COLS = 4;

    // student: Second, modify the points so that the
    // triangle shrinks relative to its center
    {
        vec3 offset = (1 - scale_coeff) * (p1 + p2 + p3) / 3;
        p1 = scale_coeff * p1 + offset;
        p2 = scale_coeff * p2 + offset;
        p3 = scale_coeff * p3 + offset;
    }

    for (int i = 0; i < instances; i++)
    {
        // student: First, modify the offset so that instances
        // are displayed on `NR_COLS` columns. Test your code by
        // changing the value of `NR_COLS`. No need to recompile.
        vec3 offset = INSTANCE_OFFSET * vec3(i / NR_COLS, 0, i % NR_COLS);

        f_texture_coord = g_texture_coord[0];
        EmitPoint(p1, offset);

        f_texture_coord = g_texture_coord[1];
        EmitPoint(p2, offset);

        f_texture_coord = g_texture_coord[2];
        EmitPoint(p3, offset);

        EndPrimitive();
    }
}
