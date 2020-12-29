#version 330 core

struct Light
{
    vec3 position; 
    vec3  direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material 
{
    sampler2D diffuse;//��������ͼ  
    sampler2D specular;   ////�������
    float shininess;//�����
}; 

in vec3 Normal;//����
in vec3 FragPos;//Ƭ��λ��
in vec2 TexCoord;//��������

out vec4 FragColor;

uniform vec3 viewPos;//�۲���λ��
uniform Material material;//����
uniform Light light;//����

void main()
{
    //1.������ ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

    //2.������+������ diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;  

    //3.������+������+������� specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoord).rgb;  

    // ���Դ
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = (light.cutOff - light.outerCutOff);
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse  *= intensity;
    specular *= intensity;

    //˥�� attenuation
    float distance    = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    ambient  *= attenuation; 
    diffuse   *= attenuation;
    specular *= attenuation; 

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
    //FragColor = texture(material.diffuse, TexCoord);
}