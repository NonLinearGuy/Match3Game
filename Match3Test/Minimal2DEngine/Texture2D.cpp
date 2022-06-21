//Declaration header
#include"Texture2D.h"




namespace Minimal2DEngine
{


	Texture2D::Texture2D()
	{

	}


	Texture2D::~Texture2D()
	{
		glDeleteTextures(1,&mID);
		SOIL_free_image_data(mImage);
	}



	Texture2D::Texture2D(
		unsigned char *pImage,
		GLint pWidth,
		GLint pHeight,
		GLenum pFormat
	)
	{


		mImage = pImage;
		mSize = glm::vec2(pWidth, pHeight);
		mFormat = pFormat;


		glGenTextures(1, &mID);

		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, mFormat, pWidth, pHeight, 0, pFormat, GL_UNSIGNED_BYTE, pImage);

		unbind();

	}

	GLuint Texture2D::createTexture(
		unsigned char *pImage,
		GLint pWidth,
		GLint pHeight,
		GLenum pFormat
	)
	{


		mImage = pImage;
		mSize = glm::vec2(pWidth,pHeight);
		mFormat = pFormat;


		glGenTextures(1,&mID);
	
		bind();
	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D,0,mFormat,mSize.x,mSize.y,0,mFormat,GL_UNSIGNED_BYTE,mImage);

		unbind();

		return mID;
	}


	void Texture2D::bind() const
	{
		glBindTexture(GL_TEXTURE_2D,mID);
	}


	void Texture2D::unbind()const
	{
		glBindTexture(GL_TEXTURE_2D,0);
	}


}
