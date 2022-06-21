#ifndef INC_GPENGINE_GPMATH_VEC4_HPP
#define INC_GPENGINE_GPMATH_VEC4_HPP


#include<cmath>

#include"Vec2.hpp"
#include"Vec3.hpp"


namespace GPEngine
{
	namespace GPMath
	{
	class Vec4
	{

		public:

		//Components
			float x,y,z,w;

		//Contructors
		Vec4();
		Vec4(float x ,float y,float z,float w=1.0f);
		Vec4(float scalar);
		Vec4(const Vec4 & other);
		Vec4(const Vec2& other);
		Vec4(const Vec3& other);

		//Destructor
		~Vec4();

		//Assignment operator
		Vec4& operator = (const Vec4 &other);

		//Addition of Vec4tors
		Vec4 operator + (const Vec4 &other) const;

		//Subtracion of Vec4tors
		Vec4 operator - (const Vec4 &other) const;

		//Normalizes the Vec4tor
		Vec4 normalize() const;

		//returns the lenth of this Vec4tor
		float length() const ;
	
		//Calculates the dot product
		float dot(const Vec4 &other) const;

		//calculates the cross product
		Vec4 cross(const Vec4 &other) const;

	};

	}
} 

#endif