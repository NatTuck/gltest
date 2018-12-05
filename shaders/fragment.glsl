#version 300 es /* -*- mode: c -*- */

precision mediump float;
out vec4 color;

void
main()
{
    if (abs(length(gl_PointCoord * 2.0 - 1.0)) > 1.0) {
        discard;
    }

    color = vec4(gl_PointCoord.x, gl_PointCoord.y, 0.5, 1.0);
}

