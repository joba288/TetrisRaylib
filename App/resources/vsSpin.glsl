#version 330

in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

uniform mat4 mvp;
uniform float t;
uniform vec2 centre;

out vec2 fragTexCoord;
out vec4 fragColor;

void main()
{
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;

    // first transform to screen space
    vec4 pos = mvp * vec4(vertexPosition, 1.0);

    float s = sin(-t);
    float c = cos(-t);

    vec2 p = pos.xy - centre;

    p = vec2(
        p.x * c - p.y * s,
        p.x * s + p.y * c
    );

    pos.xy = p + centre;

    gl_Position = pos;
}