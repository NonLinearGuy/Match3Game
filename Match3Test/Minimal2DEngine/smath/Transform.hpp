#ifndef INC_GPENGINE_GPMATH_TRANSFORM_HPP
#define INC_GPENGINE_GPMATH_TRANSFORM_HPP

#include"Mat4.hpp"
#include"Vec4.hpp"


namespace GPEngine
{
	namespace GPMath
	{
	
	Mat4 translate(const Mat4& other,const Vec4 &direction);
	Mat4 scale(const Mat4& other,const Vec4 &units);
	Mat4 rotate(const Mat4& other,float angleInRadians,const Vec4 & axisOfRotation);	
	Mat4 ortho(float left,float right,float bottom,float top,float near,float far);
	Mat4 frustum(float left,float right,float bottom,float top,float near,float far);
	Mat4 perspective(float fieldOfView,float aspectRatio,float near,float far);
	Mat4 lookAt(const Vec4& position,const Vec4& direction,const Vec4& up);
	
	}

}


#endif