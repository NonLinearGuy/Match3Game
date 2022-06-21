//Declaration header
#include"SpriteRenderer.h"
#include"AssetManager.h"

#include "Shader.h"
#include "Texture2D.h"




namespace Minimal2DEngine
{


	SpriteRenderer::SpriteRenderer(const glm::mat4 pProjection,const glm::mat4 pView)
    : IRenderer2D(pProjection, pView)
	{

		logger::getInstance()->log("sprite renderer");
		
		mShader = AssetManager::GetInstance()->LoadShader(
			"unlit shader for sprite renderer",
			"Resources/shaders/sprite_renderer_vs.glsl",
			"Resources/shaders/sprite_renderer_fs.glsl"
			);

		mCircleShader = AssetManager::GetInstance()->LoadShader(
			"circle shader",
			"Resources/shaders/circle_vs.glsl",
			"Resources/shaders/circle_fs.glsl"
		);

		float points[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glGenBuffers(1, &mVBO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);


		/*
		I am  going to need same amount of texture
		coords as points so allocating 2*sizeof(points) buffer
		so that you can store texture coordinates later.
		*/

		glBufferData(GL_ARRAY_BUFFER, sizeof(points) * 2, 0, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenVertexArrays(1, &mVAO);

		glBindVertexArray(mVAO);

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)(sizeof(points)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

	}



	SpriteRenderer::~SpriteRenderer()
	{
		glDeleteVertexArrays(1, &mVAO);
		glDeleteBuffers(1, &mVBO);
	}



	void SpriteRenderer::DrawQuad(
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		const glm::vec4& pColor,
		float pRotationInRadians
	)
	{

		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPos, 0.0f));

		model = glm::translate(model, glm::vec3((0.5f*pSize), 0.0f));
		model = glm::rotate(model, pRotationInRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, glm::vec3((-0.5f*pSize), 0.0f));

		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
			The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->Use();

		mShader->SetMat4("projection",mProjection);
		mShader->SetMat4("view",mView);
		mShader->SetMat4("model",model);

		mShader->Set1i("use_color", 1);
		mShader->Set4fv("color", pColor);

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}



	void SpriteRenderer::DrawImage(
		const std::shared_ptr<Texture2D> pTexture,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
		float pRotationInRadians
	)

	{
		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPos, 0.0f));

		model = glm::translate(model,glm::vec3((0.5f*pSize),0.0f));
		model = glm::rotate(model,glm::radians(pRotationInRadians),glm::vec3(0.0f,0.0f,1.0f));
		model = glm::translate(model, glm::vec3((-0.5f*pSize), 0.0f));

        
		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates pSize is same as vertices pSize
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->Use();
	

		mShader->SetMat4("projection", mProjection);
		mShader->SetMat4("view", mView);
		mShader->SetMat4("model", model);

		mShader->Set1i("use_color", 0);
		mShader->Set1i("sampler0", 0);

		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}


	void SpriteRenderer::DrawCircle(
		const glm::vec2& pPosition,
		const glm::vec2& pSize,
		const glm::vec4& pColor
	)
	{

		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPosition, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mCircleShader->Use();

		mCircleShader->SetMat4("projection", mProjection);
		mCircleShader->SetMat4("view", mView);
		mCircleShader->SetMat4("model", model);

		mCircleShader->Set1i("usecolor", 1);
		mCircleShader->Set4fv("color",pColor);

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

	}

	void SpriteRenderer::DrawTexturedCircle(const glm::vec2 & pPosition, const glm::vec2 & pSize, std::shared_ptr<Minimal2DEngine::Texture2D> pTexture)
	{
		glm::mat4 model = glm::mat4();

		model = glm::translate(model, glm::vec3(pPosition, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));


		float texCoords[] =
		{
			0.0f,1.0f,
			1.0f,1.0f,
			0.0f,0.0f,
			1.0f,0.0f
		};

		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mCircleShader->Use();

		mCircleShader->SetMat4("projection", mProjection);
		mCircleShader->SetMat4("view", mView);
		mCircleShader->SetMat4("model", model);

		mCircleShader->Set1i("usecolor",0);
		mCircleShader->Set1i("sampler0",0);
		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}



	void SpriteRenderer::DrawImageRegion(
		const std::shared_ptr<Texture2D> pTexture,
		const glm::vec2& pSrcPos,
		const glm::vec2& pSrcDim,
		const glm::vec2& pPos,
		const glm::vec2& pSize,
        const glm::vec2& slicedSize
	)

	{

		glm::mat4 model = glm::mat4();
		model = glm::translate(model, glm::vec3(pPos, 0.0f));
		model = glm::scale(model, glm::vec3(pSize, 0.0f));

		//Mapping values from one range to other
		float dw = pSrcDim.x / slicedSize.x;
		float dh = pSrcDim.y / slicedSize.y;
		float dx = pSrcPos.x / slicedSize.x;
		float dy = pSrcPos.y / slicedSize.y;

		float texCoords[] =
		{
			dx,dy,
			dx + dw,dy,
			dx,dy + dh,
			dx + dw,dy + dh
		};


		glBindBuffer(GL_ARRAY_BUFFER, mVBO);

		/*
		The amount of texture coordinates size is same as vertices size
		*/

		glBufferSubData(GL_ARRAY_BUFFER, sizeof(texCoords), sizeof(texCoords), texCoords);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mShader->Use();

		mShader->SetMat4("projection", mProjection);
		mShader->SetMat4("view", mView);
		mShader->SetMat4("model", model);

		mShader->Set1i("sampler0", 0);
		mShader->Set1i("use_color", 0);
        
		glActiveTexture(GL_TEXTURE0);
		pTexture->bind();

		glBindVertexArray(mVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);

		glActiveTexture(GL_TEXTURE0);
		pTexture->unbind();


	}

	

}

