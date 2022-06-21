#ifndef INC_GPENGINE_GPMATH_MAT4_H
#define INC_GPENGINE_GPMATH_MAT4_H


#include<cstdint>
#include<algorithm>

#include "Math.h"
#include "Vec4.hpp"

//Forward declaration

namespace GPEngine
{
	namespace GPMath
	{
	class Mat4
	{
		float elements[16];

		float& operator[](int index)
		{
			return this->elements[index];
		}

		void copyMat(const Mat4  &other);

	public:

		//Constructors
		Mat4();
		Mat4(const Mat4 &other);
		Mat4(const float* other);
		Mat4(float valueToFill);
		
		//Destructor
		~Mat4();

		//operators
		Mat4 operator=(const Mat4 &other);

		//loads the identity matrix
		void reset();

		//returns the element in the given index should be inline
		float operator()(int row,int col) const
		{
			return this->elements[index(row,col)];
		}

		//returns the matrix array
		const float* const valuePtr();

		//Mutliplies two Mat4 and resturns the resultant Mat4
		Mat4 operator*(const Mat4& other)const;

		//Friend transformation functions
		friend Mat4 translate(const Mat4& other,const Vec4 &direction);
		friend Mat4 scale(const Mat4& other,const Vec4 &units);
		friend Mat4 rotate(const Mat4& other,float angleInRadians,const Vec4 & axisOfRotation);	
		friend Mat4 ortho(float left,float right,float bottom,float top,float near,float far);
		friend Mat4 frustum(float left,float right,float bottom,float top,float near,float far);
		friend Mat4 perspective(float fieldOfView,float aspectRatio,float near,float far);
		friend Mat4 lookAt(const Vec4& position,const Vec4& direction,const Vec4& up);
		
	
	};

	}
}


#endif
