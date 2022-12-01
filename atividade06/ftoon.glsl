#version 400

in vec3 fN;
in vec3 fV;
in vec3 fL;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;

out vec4 outfragcolor;

const int levels = 6;
const float scaleFactor = 1.0 / levels;


vec4 Phong(vec3 n)
{
    vec3 N = normalize(n);
    vec3 V = normalize(fV);
    vec3 L = normalize(fL);
    float NdotL = dot(N, L);
    vec3 R = normalize(2.0 * NdotL * N - L);
    float Kd = max(NdotL, 0.0);
    float Ks = (NdotL < 0.0) ? 0.0 : pow(max(dot(R, V), 0.0), shininess);
    vec4 diffuse = Kd  * diffuseProduct * floor(NdotL * levels) * scaleFactor;
    vec4 ambient = ambientProduct;
    vec4 specular = Ks * specularProduct;
    return ambient + diffuse + specular;
}

void main()
{
    outfragcolor = Phong(fN);
    outfragcolor.a = 1.0;
}
