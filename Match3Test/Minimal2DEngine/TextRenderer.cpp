//Declaration header
#include"TextRenderer.h"

//shady_engine headers
#include"smath/math.h"
#include"AssetManager.h"
#include"Shader.h"
#include"Texture2D.h"



namespace Minimal2DEngine
{


	TextRenderer::TextRenderer()
	{

	}


	TextRenderer::~TextRenderer()
	{

		glDeleteBuffers(1,&mVBO);
		glDeleteVertexArrays(1,&mVAO);
	}


	TextRenderer::TextRenderer(const glm::mat4 pProjection,const glm::mat4 pView,std::shared_ptr<Texture2D> pTextureAtlas,
		const std::string& pPath)
		:
        mProjection(pProjection),
        mView(pView),
		mTextureAtlas(pTextureAtlas)

	{
		
		
		FILE *file = nullptr;

		file = fopen(pPath.c_str(), "r");

		if (!file) {
			throw std::runtime_error("failed to load to read font!");
		}

		while (true)
		{
			character c;
			int id;
			char result = fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,",
				&id,
				&c.position.x,
				&c.position.y,
				&c.size.x,
				&c.size.y,
				&c.offsets.x,
				&c.offsets.y,
				&c.advanceX
			);

			mCharacters.insert(std::pair<char, character>(static_cast<char>(id), c));

			if (result == EOF) break;
		}

		fclose(file);


		mShader = AssetManager::GetInstance()->LoadShader("shader for text rendering",
			"Resources/shaders/text_renderer_vs.glsl",
			"Resources/shaders/text_renderer_fs.glsl"
		);

		//Setting up quad
		float points[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			0.0f,1.0f,
			1.0f,1.0f
		};

		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));

		glBindVertexArray(0);

	}


	void TextRenderer::Init(
		const std::shared_ptr<Texture2D> pTextureAtlas,
		const std::string& pPath
	)

	{

		mTextureAtlas = pTextureAtlas;

		FILE *file = nullptr;
		file = fopen(pPath.c_str(), "r");

		if (!file) {
			std::cout << "failed to open font file";
			return;
		}

		while (true)
		{
			character c;
			int id;
			char result = fscanf(file, "%d,%d,%d,%d,%d,%d,%d,%d,",
				&id,
				&c.position.x,
				&c.position.y,
				&c.size.x,
				&c.size.y,
				&c.offsets.x,
				&c.offsets.y,
				&c.advanceX
			);

			mCharacters.insert(std::pair<char, character>(static_cast<char>(id), c));

			if (result == EOF) break;
		}

		fclose(file);

		AssetManager::GetInstance()->LoadShader("shader for text rendering",
			"Minimal2DEngine/shaders/text_renderer_vs.glsl",
			"Minimal2DEngine/shaders/text_renderer_fs.glsl"
		);

		mShader = AssetManager::GetInstance()->GetShader("shader for text rendering");

		//Setting up quad
		float points[] =
		{
			0.0f,0.0f,
			1.0f,0.0f,
			0.0f,1.0f,
			1.0f,1.0f
		};

		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

		//Position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(0));

		glBindVertexArray(0);

	}


	void TextRenderer::Text(
		const glm::vec2& pPosition,
		float pSize,
		const glm::vec3& pColor,
		const char* pFormat,
		...
	)
	{

		float width = smath::map_to_range(200.0f, 300.0f, .43f, .6f,pSize);
		float edge = 1.0f - smath::map_to_range(1.0f, 300.0f, 0.9f, 1.0f,pSize);
		pSize = smath::map_to_range(1.0,300.0f, 0.2f, 5.0,pSize);
		
		glm::vec2 tempPos = pPosition;

		//Initializing variable argument list
		va_list lst;
		va_start(lst, pFormat);
		std::string text;

		//Extracting data from variable argument list
		for (const char* traverse = pFormat; *traverse != '\0'; traverse++)
		{
			while (true)
			{
				if (*traverse == '%' || *traverse == '\0') break;

				text += *traverse;
				traverse++;
			}

			if (*traverse == '\0')
				break;
			traverse++;

			switch (*traverse)
			{
			case 'd':
				text += std::to_string(va_arg(lst, int));
				break;
			case 'f':
				text += std::to_string(va_arg(lst, double));
				break;
			}

		}

		va_end(lst);

		int primCounter = 0; //counts the number of text
		

		//Iterating through the string and calculating attributes of each character
		for (auto iter = text.begin(); iter != text.end(); iter++)
		{

			character c = mCharacters[*iter];


			if (*iter == '\n')
			{
				tempPos.y +=pSize*70.0f;
				tempPos.x = pPosition.x;
				continue;
			}

			

			float dx = float(c.position.x) / mTextureAtlas->get_size().x;
			float dy = float(c.position.y) / mTextureAtlas->get_size().y;
			float dw = float(c.size.x) / mTextureAtlas->get_size().x;
			float dh = float(c.size.y) / mTextureAtlas->get_size().y;


			mTexCoords.push_back(glm::vec4(dx,dy,dw,dh));


			mOffsets.push_back(tempPos + (glm::vec2(c.offsets)*pSize));
			mScalers.push_back(glm::vec2(c.size)*pSize);

			tempPos.x += (c.advanceX-8)*pSize;

			primCounter++;

		}


		//Generating some needed buffers for offsets,scales and texture coordinates

		glGenBuffers(1, &mVBOTexCoords);
		glGenBuffers(1,&mVBOOffsets);
		glGenBuffers(1, &mVBOScalers);
		
		

		glBindVertexArray(mVAO);


		//TEXTURE COORDS
		glBindBuffer(GL_ARRAY_BUFFER, mVBOTexCoords);
		glBufferData(GL_ARRAY_BUFFER, 
			sizeof(glm::vec4)*mTexCoords.size(), 
			mTexCoords.data(), 
			GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glVertexAttribDivisor(1, 1);

		//OFFSETS
		glBindBuffer(GL_ARRAY_BUFFER,mVBOOffsets);
		glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*mOffsets.size(),mOffsets.data(),GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,0);

		glVertexAttribDivisor(2, 1);

		//SCALERS
		glBindBuffer(GL_ARRAY_BUFFER, mVBOScalers);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*mScalers.size(), mScalers.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(3, 1);


		glBindVertexArray(0);

		mShader->Use();

		mShader->SetMat4("projection",mProjection);
		mShader->SetMat4("view",mView);


		mShader->Set3fv("font_color", pColor);
		mShader->Set1f("width", width);
		mShader->Set1f("edge", edge);
		mShader->Set1i("use_color", 1);

		//Binding the font texture at GL_TEXTURE0
		mShader->Set1i("texture_atlas", 0);
		glActiveTexture(GL_TEXTURE0);
		mTextureAtlas->bind();

		glBindVertexArray(mVAO);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4,primCounter);
		glBindVertexArray(0);


		glDeleteBuffers(1, &mVBOOffsets);
		glDeleteBuffers(1, &mVBOScalers);
		glDeleteBuffers(1, &mVBOTexCoords);

		mOffsets.clear();
		mScalers.clear();
		mTexCoords.clear();

	}

	
	void TextRenderer::TexturedText(
		const glm::vec2& pPosition,
		float pSize,
		std::shared_ptr<Texture2D> pFontTexture,
		const char* pFormat,
		...
	)

	{

		float width = smath::map_to_range(1.0f, 300.0f, .43f, .6f, pSize);
		float edge = 0.2f - smath::map_to_range(1.0f, 300.0f, 0.1f, 0.2f, pSize);
		pSize = smath::map_to_range(1.0, 300.0f, 0.2f, 5.0, pSize);

		glm::vec2 tempPos = pPosition;

		//Initializing variable argument list
		va_list lst;
		va_start(lst, pFormat);
		std::string text;

		//Extracting data from variable argument list
		for (const char* traverse = pFormat; *traverse != '\0'; traverse++)
		{
			while (true)
			{
				if (*traverse == '%' || *traverse == '\0') break;

				text += *traverse;
				traverse++;
			}

			if (*traverse == '\0')
				break;
			traverse++;

			switch (*traverse)
			{
			case 'd':
				text += std::to_string(va_arg(lst, int));
				break;
			case 'f':
				text += std::to_string(va_arg(lst, double));
				break;
			}

		}

		va_end(lst);

		unsigned int primCounter = 0; //counts the number of text


							 //Iterating through the string and calculating attributes of each character
		for (auto iter = text.begin(); iter != text.end(); iter++)
		{

			character c = mCharacters[*iter];


			if (*iter == '\n')
			{
				tempPos.y += pSize*70.0f;
				tempPos.x = pPosition.x;
				continue;
			}



			//Mapping texture coordinates from [0,texture dimenstions] to [0,1]
			float dx = float(c.position.x) / mTextureAtlas->get_size().x;
			float dy = float(c.position.y) / mTextureAtlas->get_size().y;
			float dw = float(c.size.x) / mTextureAtlas->get_size().x;
			float dh = float(c.size.y) / mTextureAtlas->get_size().y;


			mTexCoords.push_back(glm::vec4(dx, dy, dw, dh));


			mOffsets.push_back(tempPos + (glm::vec2(c.offsets)*pSize));
			mScalers.push_back(glm::vec2(c.size)*pSize);

			tempPos.x += (c.advanceX - 8)*pSize;

			primCounter++;

		}


		//Generating some needed buffers for offsets,scales and texture coordinates

		glGenBuffers(1, &mVBOTexCoords);
		glGenBuffers(1, &mVBOOffsets);
		glGenBuffers(1, &mVBOScalers);



		glBindVertexArray(mVAO);


		//TEXTURE COORDS
		glBindBuffer(GL_ARRAY_BUFFER, mVBOTexCoords);
		glBufferData(GL_ARRAY_BUFFER,
			sizeof(glm::vec4)*mTexCoords.size(),
			mTexCoords.data(),
			GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glVertexAttribDivisor(1, 1);

		//OFFSETS
		glBindBuffer(GL_ARRAY_BUFFER, mVBOOffsets);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*mOffsets.size(), mOffsets.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glVertexAttribDivisor(2, 1);

		//SCALERS
		glBindBuffer(GL_ARRAY_BUFFER, mVBOScalers);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*mScalers.size(), mScalers.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glVertexAttribDivisor(3, 1);


		mShader->Use();

		mShader->SetMat4("projection", mProjection);
		mShader->SetMat4("view", mView);

		mShader->Set1f("width", width);
		mShader->Set1f("edge", edge);
		mShader->Set1i("use_color", 0);

		//Binding the font texture at GL_TEXTURE0
		mShader->Set1i("texture_atlas", 0);
		glActiveTexture(GL_TEXTURE0);
		mTextureAtlas->bind();
		mShader->Set1i("font_texture", 1);
		glActiveTexture(GL_TEXTURE1);
		pFontTexture->bind();

		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, primCounter);
		glBindVertexArray(0);


		glDeleteBuffers(1, &mVBOOffsets);
		glDeleteBuffers(1, &mVBOScalers);
		glDeleteBuffers(1, &mVBOTexCoords);

		mOffsets.clear();
		mScalers.clear();
		mTexCoords.clear();

		

		} 



}//End of namespace 
