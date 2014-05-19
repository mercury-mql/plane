// fuck that shit.

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 resolution;

varying vec2 v_texCoord;
varying vec4 v_fragmentColor;

void main( void )
{
	float fPosX = v_texCoord.x;
	float fPosY = v_texCoord.y;
	
	float fR = 1.0;
	float fG = 1.0;
	float fB = 1.0;
	float fA = 1.0;

	float fTime = abs(sin(time));
	if(fTime < 0.3)
	{
		fTime = 0.3;
	}

	fR = fTime / abs(fPosX - 0.5) * 0.6;
	fG = fR * 0.3 * fTime;
	fB = fR * (1.0 - fPosY) * fTime;
	
    vec3 Color = vec3(fR, fG, fB);

	float fScale = 1.0;
	float fPercent = 0.2;
	float fDis = fPercent;
	if(fPosX < fPercent)
	{
		fDis = fPosX;
	}
	if(fPosX > 1.0 - fPercent)
	{
		fDis = 1.0 - fPosX;
	}
	fScale = fDis / fPercent;

	fA *= fScale;
	
	gl_FragColor.rgb = Color;
	gl_FragColor.a = fA;
}

