in vec4 v2fcolor;
out vec4 outfragcolor;

void main ()
{
    //media ponderada para escala de cinza, conforme luminancia
    //double grayscale = 0.299*v2fcolor.r + 0.587*v2fcolor.g + 0.114*v2fcolor.b;
    outfragcolor = v2fcolor;
}
