#version 400

in vec4 fColors;
in vec2 fTextCoord;

uniform sampler2D sampler;

uniform int shader_effect;

out vec4 outfragcolor;


void rgb2hsl(vec3 rgb, out float h, out float s, float l)
{
    float maxval = max(rgb.r , max(rgb.g, rgb.b));
    float minval = min(rgb.r, min(rgb.g, rgb.b));
    float delta = maxval - minval;

    l = (minval + maxval) / 2.0;
    s = 0.0;
    if (l > 0.0 && l < 1.0)
        s = delta / (l < 0.5 ? 2.0 * l : 2.0 - 2.0 * l);
    h = 0.0;
    if (delta > 0.0)
    {
        if (rgb.r == maxval && rgb.g != maxval)
            h += (rgb.g - rgb.b ) / delta;
        if (rgb.g == maxval && rgb.b != maxval)
            h += 2.0  + (rgb.b - rgb.r) / delta;
        if (rgb.b == maxval && rgb.r != maxval)
            h += 4.0 + (rgb.r - rgb.g) / delta;
        h *= 60.0;
    }
}


void main()
{
    switch(shader_effect){
    case 0:
        outfragcolor = texture(sampler,fTextCoord);
        break;
    case 1:
        outfragcolor = texture(sampler,fTextCoord)*fColors;
        break;
//http://kodemongki.blogspot.com/2011/06/kameraku-custom-shader-effects-example.html
    case 2: //blur
        float step = 0.005;
        vec3 c1 = texture(sampler, vec2(fTextCoord.s - step, fTextCoord.t - step)).rgb;
        vec3 c2 = texture(sampler, vec2(fTextCoord.s + step, fTextCoord.t + step)).rgb;
        vec3 c3 = texture(sampler, vec2(fTextCoord.s - step, fTextCoord.t + step)).rgb;
        vec3 c4 = texture(sampler, vec2(fTextCoord.s + step, fTextCoord.t - step)).rgb;

        outfragcolor.a = 1.0;
        outfragcolor.rgb = (c1 + c2 + c3 + c4) / 4.0;
        break;
    case 3://sobel
        const float step_w = 0.001;
        const float step_h = 0.001;
        vec3 t1 = texture(sampler, vec2(fTextCoord.x - step_w, fTextCoord.y - step_h)).bgr;
        vec3 t2 = texture(sampler, vec2(fTextCoord.x, fTextCoord.y - step_h)).bgr;
        vec3 t3 = texture(sampler, vec2(fTextCoord.x + step_w, fTextCoord.y - step_h)).bgr;
        vec3 t4 = texture(sampler, vec2(fTextCoord.x - step_w, fTextCoord.y)).bgr;
        vec3 t5 = texture(sampler, fTextCoord).bgr;
        vec3 t6 = texture(sampler, vec2(fTextCoord.x + step_w, fTextCoord.y)).bgr;
        vec3 t7 = texture(sampler, vec2(fTextCoord.x - step_w, fTextCoord.y + step_h)).bgr;
        vec3 t8 = texture(sampler, vec2(fTextCoord.x, fTextCoord.y + step_h)).bgr;
        vec3 t9 = texture(sampler, vec2(fTextCoord.x + step_w, fTextCoord.y + step_h)).bgr;

        vec3 xx= t1 + 2.0*t2 + t3 - t7 - 2.0*t8 - t9;
        vec3 yy = t1 - t3 + 2.0*t4 - 2.0*t6 + t7 - t9;

        vec3 rr = sqrt(xx * xx + yy * yy);
        float y = (rr.r + rr.g + rr.b) / 3.0;
        if (y > 0.2)
            rr = vec3(0.0, 0.0, 0.0);
        else
            rr = vec3(1.0, 1.0, 1.0);
        outfragcolor.a = 1.0;
        outfragcolor.rgb = rr;
        break;
    case 4://blue seeker
        vec3 col = texture(sampler, fTextCoord).rgb;
        float h, s, l;
        rgb2hsl(col, h, s, l);
        float _y = 0.3 * col.r + 0.59 * col.g + 0.11 * col.b;
        vec3 result;

        if (h >= 180.0 && h <= 260.0)
            result = col;
        else
            result = vec3(_y, _y, _y);

        outfragcolor.a = 1.0;
        outfragcolor.rgb = result;
        break;
    }
}



