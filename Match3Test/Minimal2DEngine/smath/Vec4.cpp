#include"Vec4.hpp"


namespace GPEngine
{
	namespace GPMath
	{

	Vec4::Vec4() 
		: x(0.0f), y(0.0f), z(0.0f),w(1.0f)
	{
	
	}


	Vec4::Vec4(
		float _x,
		float _y,
		float _z,
		float _w
		)
		: x(_x),y(_y),z(_z),w(_w)
	{
	}


	Vec4::Vec4(float scalar) 
		: x(scalar), y(scalar) ,z(scalar),w(1.0f)
	{

	}


	Vec4::Vec4(const Vec4 &other)
		:x(other.x),y(other.y),z(other.z),w(other.w)
	{

	}


	Vec4::Vec4(const Vec3& other)
		:x(other.x), y(other.y) ,z(other.z),w(0.0f)
	{

	}


	Vec4::Vec4(const Vec2& other)
		:x(other.x), y(other.y) ,z(0.0f),w(1.0f)
	{

	}


	Vec4::~Vec4()
	{
	}


	Vec4& Vec4::operator = (const Vec4 &other)
	{
		if(this==&other)
			return *this;

		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;

		return *this;
	}


	Vec4 Vec4::operator + (const Vec4 &other) const
	{
		return Vec4(x + other.x , y + other.y , z + other.z);
	}


	Vec4 Vec4::operator - (const Vec4 &other)const
	{
		return Vec4(x - other.x , y - other.y ,z - other.z);
	}


	Vec4 Vec4::normalize()const 
	{
		float len = length();
		return Vec4(x/len , y/len, z/len);
	}


	float Vec4::length() const 
	{
		return sqrt(x*x + y*y + z*z);
	}


	float Vec4::dot(const Vec4 &other)const 
	{
		return (x*other.x + y*other.y + z*other.z);
	}


	Vec4 Vec4::cross(const Vec4 &other) const
	{
		return Vec4( (y*other.z - other.y*z) , (z*other.x - other.z*x) , (x*other.y - other.x*y) );
	}

	}
}
