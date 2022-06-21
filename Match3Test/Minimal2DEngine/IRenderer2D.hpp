//
//  IRenderer2D.hpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#ifndef IRenderer2D_hpp
#define IRenderer2D_hpp

#include <glm/glm.hpp>
#include <memory>






namespace Minimal2DEngine{
    class Shader;
    class IRenderer2D{
    protected:
        glm::mat4 mProjection;
        glm::mat4 mView;
        std::shared_ptr<Shader> mShader;
    public:
        IRenderer2D(const glm::mat4& pProjection, const glm::mat4& pView);
        void UpdateView(const glm::mat4& view);
        glm::mat4 GetProjection(){
            return mProjection;
        }
        glm::mat4 GetView(){
            return mView;
        }
    };
}

#endif /* IRenderer2D_hpp */
