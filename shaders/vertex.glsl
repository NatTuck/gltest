#version 300 es /* -*- mode: c -*- */

//#version 130 /* -*- mode: c -*- */

layout (location = 0) in vec3 pos;

//in vec3 pos;

void
main()
{
    // zoom in to (0,1)(0,1)
    //gl_Position = vec4(pos.x * 2.0 - 1.0, pos.y * 2.0 - 1.0, pos.z, 1.0);
    gl_PointSize = 40.0;
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}

