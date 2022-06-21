#include"Mat4.hpp"

namespace GPEngine
{
	namespace GPMath
	{
	
		//Private functions
		void Mat4::copyMat(const Mat4 &other)
		{
			for(int row=0 ; row<4 ; row++)
			{
				for(int col=0 ; col<4 ; col++)
				{
					this->elements[index(row,col)] = other(row,col);
				}
			}
		}


		
	//Public functions

	Mat4::Mat4()
	{
		reset();
	}

	
	Mat4::Mat4(const Mat4 &other)
	{
		copyMat(other);
	}


	Mat4::Mat4(const float* other)
	{
		std::copy(other,other+16,this->elements);
	}

	Mat4::Mat4(float valueToFill)
	{
		std::fill_n(this->elements,16,valueToFill);
	}


	Mat4::~Mat4(){}


	void Mat4::reset()
	{
		float identity[16] = 
		{
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		};

		std::copy(identity,identity+16,this->elements);
	}


	Mat4 Mat4::operator=(const Mat4 &other) 
	{
		if(this==&other)
			return *this;

		copyMat(other);

		return *this;
	}
	
	
	const float* const Mat4::valuePtr()
	{
		return this->elements;
	}

	
	//Matrix operations
	Mat4 Mat4::operator*(const Mat4& other ) const
	{
		float result[16];
		
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				float sum = 0.0f;
				for(int k=0;k<4;k++)
				{
					sum+=this->elements[index(i,k)]*other(k,j);
				}

				result[i*4+j] = sum;
			}
		}
		
		return Mat4(result);
	}

	}

}
