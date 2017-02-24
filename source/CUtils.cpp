#include "globals.h"

//draw box from down to up
void CUtils::drawTex(GLuint texId, 	float x, float y, float w, float h,
							float imgX, float imgY, float imgW, float imgH, bool invert){

	float vert[4][2] = {
		{x,y},
		{x,y+h},
		{x+w,y+h},
		{x+w,y}
	};
	float tex[4][2];

	if(!invert){
		tex[0][0] = imgX+imgW;	tex[0][1] = imgY+imgH;
		tex[1][0] = imgX+imgW;	tex[1][1] = imgY;
		tex[2][0] = imgX;		tex[2][1] = imgY;
		tex[3][0] = imgX;		tex[3][1] = imgY+imgH;
	}else{
		tex[0][0] = imgX;		tex[0][1] = imgY+imgH;
		tex[1][0] = imgX;		tex[1][1] = imgY;
		tex[2][0] = imgX+imgW;	tex[2][1] = imgY;
		tex[3][0] = imgX+imgW;	tex[3][1] = imgY+imgH;
	}

	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texId);

	glVertexPointer(2,GL_FLOAT,0,vert);
	glTexCoordPointer(2,GL_FLOAT,0,tex);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS,0,4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void CUtils::drawTex(GLuint texId, 	float **drawRect, float **texRect){
	glColor4f(1.0f,1.0f,1.0f,1.0f);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texId);

	glVertexPointer(2,GL_FLOAT,0,drawRect);
	glTexCoordPointer(2,GL_FLOAT,0,texRect);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glDrawArrays(GL_QUADS,0,4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

BYTE* CUtils::loadData(const char filename[],unsigned& width, unsigned& height){
	//initialize GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
	
	//Create Bitmap object from file
	std::string *tempSt = new std::string(filename);
	std::wstring *wst = new std::wstring(tempSt->begin(), tempSt->end());
	Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(wst->c_str());
	delete tempSt;
	delete wst;
	if(!bitmap)
		return NULL;

	//get frames / dimensions
	UINT dimensionCount;
	GUID *dimensionIds(NULL);
	dimensionCount = bitmap->GetFrameDimensionsCount();
	dimensionIds = new GUID[dimensionCount];
	bitmap->GetFrameDimensionsList(dimensionIds, dimensionCount);

	//create bitmap data
	Gdiplus::BitmapData* bitmapData = new Gdiplus::BitmapData;
	width = bitmap->GetWidth();
	height = bitmap->GetHeight();
	Gdiplus::Rect rect(0, 0, width, height);

	//init data
	long size = width*height*4;
	BYTE *ret = new BYTE[size];
	//read bytes
	bitmap->SelectActiveFrame(&dimensionIds[0],0);
	bitmap->LockBits(
		&rect,
		Gdiplus::ImageLockModeRead,
		PixelFormat32bppARGB,
		bitmapData);
	BYTE *scan0 = (BYTE*)bitmapData->Scan0;
	memcpy(ret,scan0, size);
	bitmap->UnlockBits(bitmapData);


	//очистка
	delete dimensionIds;
	delete bitmapData;
	delete bitmap;
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return ret;
}

GLuint CUtils::loadTexture(const char* name){

	GLuint textureId;
	byte *data(NULL);
	unsigned w,h;

	if((data = CUtils::loadData(name, w, h)) == NULL)
		return -1;

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, data);

	delete data;

	return textureId;
}
