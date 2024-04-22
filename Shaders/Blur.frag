uniform sampler2D texture;
uniform float distance = 0.02f;

#define PI 3.14159265359

void main()
{
	vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

	for (float a = 0.0f; a < 2*PI; a+= .1f)
    {
        int count = 0;
        for (float d = 0.0f; d < distance; d+=.01f)
        {
            vec2 dir = vec2(cos(a), sin(a)) * d;
            vec2 pos = gl_TexCoord[0].xy + dir;
            if (pos.x <0) continue;
            if (pos.x >1) continue;
            if (pos.y <0) continue;
            if (pos.y >1) continue;
            count++;
            pixel = pixel + texture2D(texture, pos);
        }
        pixel /= count;
    }
	gl_FragColor = pixel;
}