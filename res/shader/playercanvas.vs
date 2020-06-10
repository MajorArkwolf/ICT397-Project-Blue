#version 410 core

out vec2 TexCoords;
uniform bool isAnimated;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 jointTransforms[MAX_JOINTS];

void main()
{
	mat4 bone_transform = jointTransforms[aJointID[0]] * aJointWeights[0];
		bone_transform += jointTransforms[aJointID[1]] * aJointWeights[1];
		bone_transform += jointTransforms[aJointID[2]] * aJointWeights[2];
		bone_transform += jointTransforms[aJointID[3]] * aJointWeights[3];

    vec4 boned_position;
    if (isAnimated == true) {
	    boned_position = bone_transform * vec4(aPos, 1.0);
	} else {
	    boned_position = vec4(aPos, 1.0);
	}

    TexCoords = aTexCoords;
    gl_Position = projection * view * model * boned_position;

}