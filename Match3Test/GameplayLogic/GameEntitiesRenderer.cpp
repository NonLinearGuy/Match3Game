//
//  GameEntitiesRenderer.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 04/05/22.
//

#include "GameEntitiesRenderer.hpp"
#include "../ExtendableHelperClasses/GameEntity.hpp"
#include "GemEntity.hpp"
#include <Minimal2DEngine/AssetManager.h>
#include <Minimal2DEngine/Shader.h>
#include <Minimal2DEngine/Texture2D.h>
#include <glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "SharedEnumsAndTypes.hpp"




using namespace Minimal2DEngine;

GameEntitiesRenderer::GameEntitiesRenderer(const glm::mat4& pProjection, const glm::mat4& pView)
: IRenderer2D(pProjection, pView)
{
    mShader = AssetManager::GetInstance()->LoadShader("batch_shader",
        "Resources/shaders/entity_inst_vs.glsl",
        "Resources/shaders/entity_inst_fs.glsl"
    );
    
  
    float vertexAttrs[] =
    {
        0.0f,1.0f, 0.0f,1.0f,
        1.0f,1.0f, 1.0f,1.0f,
        0.0f,0.0f, 0.0f,0.0f,
        1.0f,0.0f, 1.0f,0.0f
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexAttrs), vertexAttrs, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (GLvoid*)(sizeof(float) * 2));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

GameEntitiesRenderer::~GameEntitiesRenderer()
{
    glDeleteBuffers(1, &this->VBO);
    glDeleteVertexArrays(1, &this->VAO);
}


void GameEntitiesRenderer::Render(const EntityInstancingData& data,std::vector<std::shared_ptr<Minimal2DEngine::Texture2D>> pTextures)
{
    
    size_t instanceCount = data.translations.size();
    
    if(instanceCount == 0)
        return;
    
    glGenBuffers(1, &this->VBOoffsets);
    glGenBuffers(1,&this->VBOscales);
    
    glBindVertexArray(this->VAO);
    
    //SCALES
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOscales);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)* data.scales.size(), data.scales.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);
   
    
        //OFFSETS
    glBindBuffer(GL_ARRAY_BUFFER, this->VBOoffsets);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*data.translations.size(), data.translations.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(3, 1);
    
    glBindVertexArray(0);

   
    mShader->Use();
    mShader->SetMat4("projection",mProjection);
    mShader->SetMat4("view",mView);
    
    
    for(int i = 0; i < instanceCount ; i++){
        mShader->Set1i("texIndices[" + std::to_string(i) + "]",data.texIndices[i]);
    }
    
   
    glBindVertexArray(this->VAO);
    
    for(int i = 0; i < pTextures.size() ; i++){
        mShader->Set1i("samplers[" + std::to_string(i) + "]",i);
        
        glActiveTexture(GL_TEXTURE0 + i);
        pTextures[i]->bind();
    }
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instanceCount);
    
    for(int i = 0; i < pTextures.size() ; i++){
        mShader->Set1i("samplers[" + std::to_string(i) + "]",i);
        glActiveTexture(GL_TEXTURE0 + i);
        pTextures[i]->unbind();
    }
    
    
    glBindVertexArray(0);
    glDeleteBuffers(1, &this->VBOoffsets);
    glDeleteBuffers(1, &this->VBOscales);
    
   
    
}


