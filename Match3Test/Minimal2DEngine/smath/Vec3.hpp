/*
	This Vec3tor class which can be used as 2d,3d and 4d Vec3tor
	note: arithmetic opearations shouldn't alter w component of Vec3tor
*/


#ifndef INC_GPENGINE_GPMATH_VEC3_HPP
#define INC_GPENGINE_GPMATH_VEC3_HPP


#include<cmath>


namespace GPEngine
{
	namespace GPMath
	{
	class Vec3
	{

		public:

		//Components
			float x,y,z;

		//Contructors
		Vec3();
		Vec3(float x ,float y,float z);
		Vec3(float scalar);
		Vec3(const Vec3 &other);

		//Destructor
		~Vec3();

		//Assignment operator
		Vec3& operator = (const Vec3 &other);

		//Addition of Vec3tors
		Vec3 operator + (const Vec3 &other) const;

		//Subtracion of Vec3tors
		Vec3 operator - (const Vec3 &other) const;

		//Normalizes the Vec3tor
		Vec3 normalize() const;

		//returns the lenth of this Vec3tor
		float length() const ;
	
		//Calculates the dot product
		float dot(const Vec3 &other) const;

		//calculates the cross product
		Vec3 cross(const Vec3 &other) const;

	};

	}
} 

#endif