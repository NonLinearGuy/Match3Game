
#ifndef INC_GPENGINE_GPMATH_VEC2_H
#define INC_GPENGINE_GPMATH_VEC2_H


#include<cmath>


namespace GPEngine
{
	namespace GPMath
	{
	class Vec2
	{

		public:

		//Components
			float x,y;

		//Contructors
		Vec2();
		Vec2(float _x ,float _y);
		Vec2(float scalar);
		Vec2(const Vec2 & other);

		//Destructor
		~Vec2();

		//Assignment operator
		Vec2& operator = (const Vec2 &other);

		//Addition of Vec2tors
		Vec2 operator + (const Vec2 &other) const;

		//Subtracion of Vec2tors
		Vec2 operator - (const Vec2 &other) const;

		//Normalizes the Vec2tor
		Vec2 normalize() const;

		//returns the lenth of this Vec2tor
		float length() const ;
	
		//Calculates the dot product
		float dot(const Vec2 &other) const;

	};

	}
} 

#endif