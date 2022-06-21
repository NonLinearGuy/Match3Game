#ifndef INC_Minimal2DEngine_SMATH_MATH_H
#define INC_Minimal2DEngine_SMATH_MATH_H


namespace Minimal2DEngine
{
	namespace smath
	{
		const float PIE = 3.1415926535f;

		//calculates the proper index in matrix
		inline int index(int row, int col)
		{
			return row * 4 + col;
		}


		//one radian
		inline float oneRadian()
		{
			return (180.0f / PIE);
		}


		//converts degrees to radians
		inline float radians(float angleInDegree)
		{
			return (angleInDegree / oneRadian());
		}


		//converts radians to degrees
		inline float degrees(float angleInRadian)
		{
			return (angleInRadian*oneRadian());
		}


		//Maps values from one range to another
		inline float map_to_range(
			float srcMin, 
			float srcMax, 
			float destMin, 
			float destMax, 
			float input
		)
		{
			float slope = (destMax - destMin) / (srcMax - srcMin);
			return (destMin + (slope*input));
		}

		//Returns the corresponding index of row and col in 2D array

		inline int index(int row, int col, int maxCol)
		{
			return (row*maxCol) + col;
		}
        
        inline float lerp(float a,float b,float t){
            return t * b + (1-t) * a;
        }

	}
}

#endif
