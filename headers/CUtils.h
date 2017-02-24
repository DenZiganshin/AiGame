#ifndef CUTILSH
#define CUTILSH

#ifndef GL_BGRA_EXT
#define GL_BGRA_EXT 0x80E1
#endif

#ifndef GL_ABGR_EXT
#define GL_ABGR_EXT 0x8000
#endif

#include "globals.h"


typedef unsigned char byte;


class CUtils{
public:
	/* draw rectangle part(imgX,imgY,imgW,imgH) of texture(texId) in rectangle(x, y, w, h) */
	static void drawTex(GLuint texId, 	float x, float y, float w, float h,
								float imgX, float imgY, float imgW, float imgH, bool invert = false);
	
	/* draw rectangle part(float[4][2]) of texture(texId) in rectangle(float[4][2]) */
	static void drawTex(GLuint texId, 	float **drawRect, float **texRect);
	
	/* load bitmap data from bmp file(name). 
		outData - rgba data from file. Init inside.
		outWidth,outHeight - output size of image in pixels */
	static BYTE* loadData(const char filename[], unsigned& width, unsigned& height);
	
	/*	Uses loadData. Make texture from RGBA bitmap (*.bmp)file */
	static GLuint loadTexture(const char* name);

};



#endif







