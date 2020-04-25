#version 430 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normals;
in vec4 HeightPoint;
in vec3 FragPos;  

// texture samplers

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform float tm_snowHeight;
uniform float tm_dirtHeight;
uniform float tm_grassHeight;
uniform float tm_sandHeight;

void main()
{
    float maxHeight = 255;
    vec4 snow = texture(texture1, TexCoord);
    vec4 grass = texture(texture2, TexCoord);
    vec4 dirt = texture(texture3, TexCoord);
    vec4 sand = texture(texture4, TexCoord);

    if (HeightPoint[1] > tm_snowHeight) {
        FragColor = snow;
    } else if (HeightPoint[1] > tm_dirtHeight) {
        float blend_percent = (HeightPoint[1] - tm_dirtHeight) / (tm_snowHeight - tm_dirtHeight);
        FragColor = mix(dirt, snow, blend_percent);
    } else if (HeightPoint[1] > tm_grassHeight) {
        float blend_percent = (HeightPoint[1] - tm_grassHeight) / (tm_dirtHeight - tm_grassHeight);
        FragColor = mix(grass, dirt, blend_percent);
    } else {
        FragColor = grass;
    }
    if (HeightPoint[1] < tm_sandHeight) {
        FragColor = sand;
	}

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normals);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.05;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
        
    vec3 result = (ambient + diffuse + specular);
    FragColor = FragColor * vec4(result, 1.0);
}