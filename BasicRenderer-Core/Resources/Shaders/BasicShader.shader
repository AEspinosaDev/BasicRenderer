#shader vertex
#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 atexCoord;
layout(location = 3) in vec3 aTangent;

out vec3 pos;
out vec2 texCoord;
out mat3 TBN;
out mat4 viewv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

mat4 modelView = view*model;

void main()
{
    texCoord = atexCoord;
    pos = (view * vec4(aPos, 1.0)).xyz;
    vec3 T = normalize(vec3(modelView * vec4(aTangent, 0.0)));
    vec3 N = normalize(vec3(modelView * vec4(aNormal, 0.0)));
    vec3 B = cross(N, T);
    TBN = mat3(T, B, N);
    viewv = view;

    gl_Position = projection * modelView * vec4(aPos, 1.0f);
    
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec3 pos;
in vec2 texCoord;
in mat3 TBN;
in mat4 viewv;

uniform sampler2D colorTex;
uniform sampler2D normalTex;

//surface properties
vec3 ambientK = texture(colorTex, texCoord).rgb;
vec3 diffuseK = texture(colorTex, texCoord).rgb;
vec3 specularK;
vec3 normalK = texture(normalTex, texCoord).rgb;
float alpha;
vec3 N;


//sample point light
vec3 lightPos = vec3(viewv * vec4(vec3(0.0, 10.0, 20.0), 1.0));
//vec3 lightPos = vec3(0.0, 5.0, 3.0);
vec3 color = vec3(1, 1, 1);

vec3 shade();
vec3 shadePointLight(vec3 lightPos, vec3 color);
void main()
{
    alpha = 10;
    normalK = normalK * 2.0 - 1.0;
    N = normalize(TBN * normalK);
    FragColor = vec4(shadePointLight(lightPos, color), 0.0)*10;
    
}

vec3 shadePointLight(vec3 lightPos, vec3 color) {
    vec3 Ia = vec3(0.2);
    vec3 Id = vec3(1.0);
    vec3 Is = vec3(1.0);
    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;

    float d = length(lightPos - pos);
    float att = 1.0 / (constant + linear * d + quadratic * (d * d));

    vec3 c = vec3(0.0);
    vec3 ambient = Ia * ambientK;
    ambient *= att;

    vec3 L = normalize(lightPos - pos);
    vec3 diffuse = Id * diffuseK * dot(L, N);
    diffuse *= att;
    c += clamp(diffuse, 0.0, 1.0);


    vec3 V = normalize(-pos);
    vec3 R = normalize(reflect(-L, N));
    float factor = clamp(dot(R, V), 0.0, 1.0);
    vec3 specular = Is * specularK * pow(factor, alpha);
    specular *= att;
    c += clamp(specular, 0.0, 1.0);



    return c *= color;



}
