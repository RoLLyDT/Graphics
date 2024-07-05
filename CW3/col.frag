#version 330 core

in vec3 col;
in vec3 nor;
in vec3 FragPos;
in vec2 tex; // Assuming tex coordinates are shared

out vec4 fragColour;

uniform vec3 lightColour;
uniform vec3 lightDirection;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform sampler2D Texture;
/*
float CalculateSpotIllumination()
{
	float amb = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 NToLight = normalize(lightPos - FragPos);
	float diff = max(dot(Nnor, NToLight), 0.f);

	vec3 NFromLight = -NToLight;
	vec3 refDir = reflect(NFromLight, Nnor);
	vec3 NcamDir = normalize(camPos - FragPos);
	float spec = pow(max(dot(NcamDir, refDir), 0.f), 128);

	float d = length(lightPos - FragPos);
	float c = 1.5f;
	float l = .05f;
	float q = .02f;
	float att = 1.f / (c + (l*d) + (q*(d*d)));

	float phi = cos(radians(15.f));
	vec3 NSpotDir = normalize(lightDirection);
	float theta = dot(NFromLight, NSpotDir);

	float i;
	if(theta > phi)
	{
		i = (amb + diff + spec) * att;
	}
	else
	{
		i = (amb) * att;
	}

	return i;
}
*/

/*
float CalculateDirectionalIllumination()
{
	float amb = 0.1f;

	vec3 Nnor = normalize(nor);
	vec3 Ntolight = normalize(-lightDirection);
	float diff = max(dot(Nnor, Ntolight), 0.f);

	vec3 Nfromlight = normalize(lightDirection);
	vec3 refDir = reflect(Nfromlight, Nnor);
	vec3 camDir = normalize(camPos - FragPos);
	float spec = pow(max(dot(camDir, refDir), 0.f), 128);

	float i = amb + diff + spec;

	return i;
}*/


void main()
{
    // Uncomment one of the following sections based on your condition

    // Option 1: Apply illumination to the texture
    //float phong = CalculateSpotIllumination();
    //fragColour = vec4(phong * texture(Texture, tex).xyz * lightColour, 1.0);

    // Option 2: Apply illumination to the color
    // float phong = CalculateSpotIllumination();
    // fragColour = vec4(phong * col * lightColour, 1.0);

    // Option 3: Use texture without illumination
     fragColour = texture(Texture, tex);

	//float phong = CalculateDirectionalIllumination();
	//fragColour = vec4(phong * texture(Texture, tex).xyz * lightColour, 10.0f);
}
