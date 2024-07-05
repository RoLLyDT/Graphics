#pragma once
#include <glad/glad.h> 
#include <iostream>
#include "bitmap.h"

GLuint setup_texture(const char* filename)
{
	glEnable(GL_TEXTURE_2D); //Enable texture
	glEnable(GL_BLEND);

	GLuint texObject;
	glGenTextures(1, &texObject); //Generate a texture object
	glBindTexture(GL_TEXTURE_2D, texObject);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //Draw texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);


	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	unsigned char* pxls = NULL; //Load bitmap file
	BITMAPINFOHEADER info;
	BITMAPFILEHEADER file;
	loadbitmap(filename, pxls, &info, &file);

	if (pxls != NULL)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info.biWidth, info.biHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pxls);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	delete[] pxls;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return texObject;
	//return 0;
}

GLuint setup_mipmaps(const char* filename[], int n)
{
	return 0;
}
