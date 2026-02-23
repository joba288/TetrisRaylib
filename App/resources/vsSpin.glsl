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

    float s = sin(-t);
    float c = cos(-t);
    mat4 rotationMat = mat4(
        c,  s, 0.0, 0.0,
       -s,  c, 0.0, 0.0,
        0.0,0.0,1.0, 0.0,
        0.0,0.0,0.0, 1.0
    );

    // Move to origin
    vec4 pos = vec4(vertexPosition.xy - centre, vertexPosition.z, 1.0);

    //Rotate
    pos *= rotationMat;
    // Move back
    pos.xy += centre;

    // Calculate final vertex position
    gl_Position = mvp * pos;
}