#version 330

// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 worldPos;


// Input uniform values
uniform sampler2D texture0;
uniform vec4 colDiffuse;

uniform int trailStart;
uniform int gridHeight;
uniform vec2 windowSize;
uniform int squareSize;

uniform float timePlaced;
uniform float currentTime;

// Output fragment color
out vec4 finalColor;

// NOTE: Add your custom variables here

void main()
{
    // Texel color fetching from texture sampler
    vec4 texelColor = texture(texture0, fragTexCoord);

    float age = currentTime - timePlaced;
    float lifetime = 0.25; 
    float timeFade = 1.0 - clamp(age / lifetime, 0.0, 1.0);


    vec2 pos = worldPos.xy;
    

    float dist = abs( pos.y/float(squareSize) - float(trailStart));
    float alpha = float(dist) / float(gridHeight);




    alpha = clamp(alpha*timeFade, 0.0, 1.0);


    finalColor = texelColor*colDiffuse*fragColor;
    finalColor.a = alpha;
}