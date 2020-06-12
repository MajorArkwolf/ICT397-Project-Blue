#version 410 core
layout (location = 0) in vec3 w_aPos;
layout (location = 1) in vec2 w_aTexCoord;
layout (location = 2) in vec3 w_normals;

out vec2 w_TexCoord;
out vec3 w_Normals;
out vec3 w_FragPos;

uniform mat4 w_model;
uniform mat4 w_view;
uniform mat4 w_projection;
uniform float w_time;

uniform float time;
float wave(float time, float freq, float amp) {
  float angle = (time+w_aPos.y)*freq;
  return sin(angle)*amp;
}
float waveNorm(float time, float freq, float amp) {
  float angle = (time+w_aPos.y)*freq;
  return -amp * freq * cos(angle);
}

void main()
{
    vec3 transformed = w_aPos;
    float freq = 3.0;
    float amp = 0.1;
    float freq1 = 1.0;
    float amp1= 0.05;
    transformed.z += wave(w_time,freq,amp) + wave(w_time,freq*2.0,amp/2.0) + wave(w_time,freq*3.5,amp*0.2);
    //float normWave = waveNorm(w_time,freq,amp) + waveNorm(w_time,freq*2.0,amp/2.0) + waveNorm(w_time,freq*3.5,amp*0.2);
    transformed.y += wave(w_time,freq1,amp1) + wave(w_time,freq1*2.0,amp1/2.0) + wave(w_time,freq1*3.5,amp1*0.2);
    //float normWave = waveNorm(w_time,freq1,amp1) + waveNorm(w_time,freq1*2.0,amp1/2.0) + waveNorm(w_time,freq1*3.5,amp1*0.2);
	w_FragPos = vec3(w_model * vec4(w_aPos, 1.0));
	gl_Position = w_projection * w_view * w_model * vec4(transformed, 1.0f);
	w_TexCoord = w_aTexCoord;
	w_Normals = mat3(transpose(inverse(w_model))) * w_normals;
}
