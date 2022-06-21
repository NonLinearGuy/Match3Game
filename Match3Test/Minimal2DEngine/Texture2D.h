#ifndef INC_SHADY_ENGINE_TEXTURE2D_H
#define INC_SHADY_ENGINE_TEXTURE2D_H




//C++ Headers
#include<string>


//Third party libraries
#include<glad/glad.h>
#include<SOIL.h>
#include<glm/glm.hpp>




namespace Minimal2DEngine
{
	class Texture2D
	{


	public:
	

		//constructor and destructor
		Texture2D();

		Texture2D(
			unsigned char *pImage,
			GLint pWidth,
			GLint pHeight,
			GLenum pFormat
		);

		GLuint createTexture(
			unsigned char *pImage, 
			GLint pWidth, 
			GLint pHeight, 
			GLenum pFormat
		);
		
		
		~Texture2D();
		
		//Getters
		
		inline GLuint get_id() const { 
			return mID; 
		}

		
		inline glm::vec2 get_size() const {
			return mSize;
		}

		
		inline GLenum get_format() const {
			return mFormat; 
		}

		inline unsigned char* getPixels() const {
			return mImage;
		}
		
		//functions
	
		
		
		GLvoid bind()const;
		
		
		GLvoid unbind()const;



	private:


		GLuint mID;
		glm::vec2 mSize;
		GLenum mFormat;
		unsigned char* mImage;
	

	};


}

#endif
