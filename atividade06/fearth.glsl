#version 400

in vec3 fN;
in vec3 fV;
in vec3 fL;
in vec2 ftextCoord;

uniform vec4 ambientProduct;
uniform vec4 diffuseProduct;
uniform vec4 specularProduct;
uniform float shininess;
uniform float cloudOffset;

uniform sampler2D layerEarth;
uniform sampler2D layerCloud;

out vec4 frag_color;

vec4 Phong(vec3 n)
{
    vec3 N = normalize(n);
    vec3 V = normalize(fV);
    vec3 L = normalize(fL);
    float NdotL = dot(N,L);
    vec3 R = normalize(2.0 *NdotL * N - L);
    float Kd = max(NdotL, 0.0);
    float contrnuvem = texture(layerCloud, vec2(ftextCoord.x + cloudOffset, ftextCoord.y)).r;

    vec4 mixtex = mix(texture(layerEarth, ftextCoord), texture(layerCloud, vec2(ftextCoord.x + cloudOffset, ftextCoord.y)), contrnuvem);
    vec4 diffuse = Kd * mixtex;
    vec4 ambient = ambientProduct;
    return ambient + diffuse;
}

void main()
{
    if (gl_FrontFacing)
    {
        frag_color = vec4(Phong(fN).xyz, 1);
    }
    else
    {
        frag_color = mix(vec4(Phong(-fN).xyz, 1), vec4(0.0, 1.0, 0.0, 1.0), 0.7);
    }
}
