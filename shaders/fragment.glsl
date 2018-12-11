#version 300 es /* -*- mode: c -*- */

precision mediump float;
out vec4 color;

void
main()
{
    float dist = abs(length(gl_PointCoord * 2.0 - 1.0));
    float delta = fwidth(dist);
    float weight = 1.0 - smoothstep(1.0 - delta, 1.0 + delta, dist);
    //color = weight * vec4(gl_PointCoord.x, gl_PointCoord.y, 0.5, 1.0);
    color = vec4(gl_PointCoord.x, gl_PointCoord.y, 0.5, weight);
}

