#include"Vec3.hpp"

#include"Vec2.hpp"


namespace GPEngine
{
	namespace GPMath
	{

	Vec3::Vec3() 
		: x(0.0f), y(0.0f), z(0.0f)
	{
	
	}


	Vec3::Vec3(
		float _x,
		float _y,
		float _z
		)
		: x(_x),y(_y),z(_z)
	{
	}


	Vec3::Vec3(float scalar) 
		: x(scalar), y(scalar) ,z(scalar)
	{

	}


	Vec3::~Vec3()
	{

	}


	Vec3::Vec3(const Vec3 &other)
		:x(other.x),y(other.y),z(other.z)
	{

	}


	Vec3& Vec3::operator = (const Vec3 &other)
	{
		if(this==&other)
			return *this;

		this->x = other.x;
		this->y = other.y;
		this->z = other.z;

		return *this;
	}


	Vec3 Vec3::operator + (const Vec3 &other) const
	{
		return Vec3(x + other.x , y + other.y , z + other.z);
	}


	Vec3 Vec3::operator - (const Vec3 &other)const
	{
		return Vec3(x - other.x , y - other.y ,z - other.z);
	}


	Vec3 Vec3::normalize()const 
	{
		float len = length();
		return Vec3(x/len , y/len, z/len);
	}


	float Vec3::length() const 
	{
		return sqrt(x*x + y*y + z*z);
	}


	float Vec3::dot(const Vec3 &other)const 
	{
		return (x*other.x + y*other.y + z*other.z);
	}


	Vec3 Vec3::cross(const Vec3 &other) const
	{
		return Vec3( (y*other.z - other.y*z) , (z*other.x - other.z*x) , (x*other.y - other.x*y) );
	}

	}
}
