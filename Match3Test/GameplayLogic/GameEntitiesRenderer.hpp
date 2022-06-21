//
//  GameEntitiesRenderer.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 04/05/22.
//

#ifndef GameEntitiesRenderer_hpp
#define GameEntitiesRenderer_hpp

#include <stdio.h>
#include <memory>
#include <vector>
#include <glad/glad.h>
#include <Minimal2DEngine/IRenderer2D.hpp>

class GemEntity;
class SpriteSheetEntity;
class GemSlot;

namespace Minimal2DEngine{
    class Shader;
    class Texture2D;
}

struct EntityInstancingData
{
    std::vector<glm::vec2> translations;
    std::vector<glm::vec2> scales;
    std::vector<int> texIndices;
};

class GameEntitiesRenderer : public Minimal2DEngine::IRenderer2D{
    
private:

    GLuint VAO;
    GLuint VBO;

    GLuint VBOoffsets;
    GLuint VBOscales;
    
    

public:
    GameEntitiesRenderer(const glm::mat4& pProjection, const glm::mat4& pView);
    void Render(const EntityInstancingData& data,std::vector<std::shared_ptr<Minimal2DEngine::Texture2D>> pTextures);
    ~GameEntitiesRenderer();
};

#endif /* GameEntitiesRenderer_hpp */
