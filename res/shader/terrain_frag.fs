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

void main()
{
    vec4 t1 = texture(texture1, TexCoord);
    vec4 t2 = texture(texture2, TexCoord);
    vec4 t3 = texture(texture3, TexCoord);
    vec4 t4 = texture(texture4, TexCoord);

    if (HeightPoint[1] > 190) {
        float blend_percent = (HeightPoint[1] - 190) / 65;
        FragColor = mix(t3, t1, blend_percent);
    } else if (HeightPoint[1] > 170) {
        FragColor = t3;
    } else if (HeightPoint[1] > 150) {
        float blend_percent = (HeightPoint[1] - 150) / 20;
        FragColor = mix(t2, t3, blend_percent);
    } else {
        FragColor = t2;
    }
    if (HeightPoint[1] < 130) {
        FragColor = t4;
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