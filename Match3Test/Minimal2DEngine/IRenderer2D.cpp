//
//  IRenderer2D.cpp
//  Match3Test
//
//  Created by Ankit Singh Kushwah on 01/05/22.
//

#include "IRenderer2D.hpp"
#include "Shader.h"

using namespace Minimal2DEngine;

IRenderer2D::IRenderer2D(const glm::mat4& pProjection, const glm::mat4& pView)
: mProjection(pProjection),mView(pView)
{
    
}

void IRenderer2D::UpdateView(const glm::mat4& view){
    this->mView = view;
}
