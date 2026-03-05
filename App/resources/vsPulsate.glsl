#version 330

// Input vertex attributes
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec3 vertexNormal;
in vec4 vertexColor;

// Input uniform values
uniform mat4 mvp;
uniform float t;
uniform vec2 centre;

// Output vertex attributes (to fragment shader)
out vec2 fragTexCoord;
out vec4 fragColor;


void main()
{
    // Send vertex attributes to fragment shader
    fragTexCoord = vertexTexCoord;
    fragColor = vertexColor;


    // Move to origin
    vec4 pos = vec4(vertexPosition.xy - centre, vertexPosition.z, 1.0);

    //Pulse
    float pulse = 1.0 + 0.25 * sin(t);
    pos.xy *= pulse;

    // Move back
    pos.xy += centre;

    // Calculate final vertex position
    gl_Position = mvp * pos;
}