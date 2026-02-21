#version 330

// constants
const float stepSize = 2.0;
const int sampleSize = 5;
const int shadowSoften = 10;


// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
in vec3 worldPos;

// Input uniform values - raylib handled
uniform sampler2D texture0;
uniform vec4 colDiffuse;

// Output fragment color
out vec4 finalColor;


// need to pass in the depth grid
uniform float depthGrid[10*20];
uniform vec2 windowSize;
uniform vec2 lightPos;
uniform int squareSize;
uniform ivec2 gridSize; 

// SHADER STORAGE BUFFER OBJECT LOOK INTO


float index(ivec2 pos)
{
    return depthGrid[int(pos.y) * gridSize.x + int(pos.x)];
}



void main()
{

    vec4 texelColor = texture(texture0, fragTexCoord);
    

    // Ray Marching
    
    vec2 pos = worldPos.xy;
    pos.y = windowSize.y - worldPos.y;

    ivec2 posInGrid = ivec2(int(pos.x/squareSize), int((windowSize.y - pos.y)/squareSize)); 
    float posDepth = index(posInGrid); // depth at current px

    vec2 traversePos = pos;
    vec2 lightPosFlipped = vec2(lightPos.x, windowSize.y - lightPos.y);
    vec2 rayDir = normalize(lightPosFlipped - pos);

    float occlusion = 0;

    for (int i = 0; i < sampleSize; i++)
    {
        traversePos += rayDir * stepSize;
        ivec2 traversePosInGrid = ivec2(int(traversePos.x/squareSize), int((windowSize.y - traversePos.y)/squareSize));
        float traverseDepth = index(traversePosInGrid); // depth of current point


        if (posDepth < traverseDepth)   // if the ray meets a depth higher than the original, the light is occluded
        {
            occlusion += 1;
        }
    }  
    //
    vec3 result = (colDiffuse.rgb) * (1.- occlusion/shadowSoften);
    finalColor = vec4(result, 1.0) * fragColor * texelColor;
    



}