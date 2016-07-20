// CS148 Summer 2016 Homework 3 - Shaders

#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;


void main()
{

    //Ambient
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    //Diffuse
    vec3 normalized_normal = normalize(Normal);
    vec3 light_vector = normalize(lightPos - FragPos);
    float diff_scalar = max(dot(normalized_normal, light_vector), 0.0);
    vec3 diffuse = diff_scalar * lightColor;

    //Specular
    float specularStrength = 0.5f;
    vec3 view_vector = normalize(viewPos - FragPos);
    vec3 light_reflection = reflect(-light_vector, normalized_normal);
    float shininess = 32;
    float spec = pow(max(dot(view_vector, light_reflection), 0.0), shininess);

    vec3 specular = specularStrength * spec * lightColor;  

    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0f);


} 
