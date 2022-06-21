#include"Transform.hpp"


namespace GPEngine
{

	namespace GPMath
	{
	
	Mat4 translate(const Mat4& other,const Vec4 &direction)
	{
		Mat4 tempMatrix;
		tempMatrix[index(3,0)] = direction.x;
		tempMatrix[index(3,1)] = direction.y;
		tempMatrix[index(3,2)] = direction.z;

		return other*tempMatrix;
	}


	Mat4 scale(const Mat4& other,const Vec4 & units)
	{
		Mat4 tempMatrix;

		tempMatrix[index(0,0)] = tempMatrix[index(0,0)]*units.x;
		tempMatrix[index(1,1)] = tempMatrix[index(1,1)]*units.y;
		tempMatrix[index(2,2)] = tempMatrix[index(2,2)]*units.z;

		return tempMatrix*other;
	}

	
	Mat4 rotate(const Mat4& other,float angleInRadians,const Vec4& axisOfRotation)
	{
		Mat4 tempMatrix;

		Vec4 n = axisOfRotation.normalize();
		
		float nx = n.x;
		float ny = n.y;
		float nz = n.z;
		
		float nxx = n.x*n.x;
		float nyy = n.y*n.y;
		float nzz = n.z*n.z;
		
		float nxny = n.x*n.y;
		float nynz = n.y*n.z;
		float nznx = n.z*n.x;
		
		float sine = sin(angleInRadians);
		float cosine = cos(angleInRadians);
		float one_cosine = 1-cosine;
		
		tempMatrix[index(0,0)] = nxx*one_cosine+cosine;
		tempMatrix[index(0,1)] = nxny*one_cosine+nz*sine;
		tempMatrix[index(0,2)] = nznx*one_cosine-ny*sine;
		
		tempMatrix[index(1,0)] = nxny*one_cosine-nz*sine;
		tempMatrix[index(1,1)] = nyy*one_cosine+cosine;
		tempMatrix[index(1,2)] = nynz*one_cosine+nx*sine;
		
		tempMatrix[index(2,0)] = nznx*one_cosine+ny*sine;
		tempMatrix[index(2,1)] = nynz*one_cosine-nx*sine;
		tempMatrix[index(2,2)] = nzz*one_cosine+cosine;

		return other*tempMatrix;
	}
	

	Mat4 ortho(float left,float right,float bottom,float top,float near,float far)
	{
		Mat4 tempMatrix;

		tempMatrix[index(0,0)] = 2.0f / (right - left); 
		tempMatrix[index(1,1)] = 2.0f / (top - bottom);
		tempMatrix[index(2,2)] = - 2.0f / (far-near);
		tempMatrix[index(3,0)] = - (right + left) / (right - left);
		tempMatrix[index(3,1)] = - (top + bottom) / (top - bottom);
		tempMatrix[index(3,2)] = - (far + near) / (far - near);

		return tempMatrix;
	}
	

	Mat4 frustum(float left,float right,float bottom,float top,float near,float far)
	{
		Mat4 tempMatrix(0.0f);

		tempMatrix[index(0,0)] = (2.0f * near) / (right - left);
		tempMatrix[index(1,1)] = (2.0f * near) / (top - bottom);
		tempMatrix[index(2,0)] = (right + left) / (right - left);
		tempMatrix[index(2,1)] = (top + bottom) / (top - bottom); 
		tempMatrix[index(2,2)] = - (far + near) / (far - near);
		tempMatrix[index(2,3)] = -1.0f;
		tempMatrix[index(3,2)] = - (2.0f * far * near) / (far - near);
		tempMatrix[index(3,3)] = 0.0f;
		
		return tempMatrix;
	}

	
	Mat4 perspective(float fieldOfView,float aspectRatio,float near,float far)
	{
		float tanHalfFov = tan(radians(fieldOfView/2.0f));
		float halfHeight = near*tanHalfFov;
		float halfWidth = halfHeight*aspectRatio;
		
		return frustum(-halfWidth,halfWidth,-halfHeight,halfHeight,near,far);
	}


	Mat4 lookAt(const Vec4& position,const Vec4& center,const Vec4& up)
	{
		Mat4 tempMatrix;

		Vec4 c_direction = Vec4(position-center).normalize();
		Vec4 c_right = Vec4(up.cross(c_direction)).normalize();
		Vec4 c_up = Vec4(c_direction.cross(c_right)).normalize();

		tempMatrix[index(0,0)] = c_right.x;
		tempMatrix[index(1,0)] = c_right.y;
		tempMatrix[index(2,0)] = c_right.z;

		tempMatrix[index(0,1)] = c_up.x;
		tempMatrix[index(1,1)] = c_up.y;
		tempMatrix[index(2,1)] = c_up.z;
		
		tempMatrix[index(0,2)] = c_direction.x;
		tempMatrix[index(1,2)] = c_direction.y;
		tempMatrix[index(2,2)] = c_direction.z;

		tempMatrix[index(3,0)] = -position.dot(c_right);
		tempMatrix[index(3,1)] = -position.dot(c_up);
		tempMatrix[index(3,2)] = -position.dot(c_direction);
		
		return tempMatrix;

	}


	}
}