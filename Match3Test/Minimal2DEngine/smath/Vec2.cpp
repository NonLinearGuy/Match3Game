#include"Vec2.hpp"
#include<iostream>


namespace GPEngine
{
	namespace GPMath
	{

	Vec2::Vec2() 
		: x(0.0f), y(0.0f)
	{
	
	}


	Vec2::Vec2(float _x,float _y)
		: x(_x),y(_y)
	{

	}


	Vec2::Vec2(float scalar) 
		: x(scalar), y(scalar)
	{
		
	}


	Vec2::~Vec2()
	{

	}


	Vec2::Vec2(const Vec2 &other)
		:x(other.x),y(other.y)
	{
	}


	Vec2& Vec2::operator = (const Vec2 &other)
	{
		if(this==&other)
			return *this;

		this->x = other.x;
		this->y = other.y;

		return *this;
	}


	Vec2 Vec2::operator + (const Vec2 &other) const
	{
		return Vec2(x + other.x , y + other.y);
	}


	Vec2 Vec2::operator - (const Vec2 &other)const
	{
		return Vec2(x - other.x , y - other.y);
	}


	Vec2 Vec2::normalize()const 
	{
		float len = length();
		return Vec2(x/len , y/len);
	}


	float Vec2::length() const 
	{
		return sqrt(x*x + y*y);
	}


	float Vec2::dot(const Vec2 &other)const 
	{
		return (x*other.x + y*other.y);
	}

	}
}
