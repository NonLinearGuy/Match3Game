#include"random.h"


using namespace std;


namespace Minimal2DEngine
{

	random::random()
	{
		mRandEngine.seed(chrono::steady_clock::now().time_since_epoch().count());
	}

	random::~random()
	{
		
	}


	void random::update()
	{
		mRandEngine.seed(chrono::steady_clock::now().time_since_epoch().count());
	}

	
	float random::real(float pMin, float pMax)
	{
		std::uniform_real_distribution<> distReal(pMin,pMax);
		return distReal(mRandEngine);
	}


	int random::integer(int pMin, int pMax)
	{
		std::uniform_int_distribution<> distReal(pMin, pMax);
		return distReal(mRandEngine);
	}


	glm::vec3 random::inside_unit_sphere()
	{
		
		std::uniform_real_distribution<> distReal(0.0f, 1.1f);
		glm::vec3 point; 
		point.x = distReal(mRandEngine);
		point.y = distReal(mRandEngine);
		point.z = distReal(mRandEngine);
		return point;

	}



} //End of namespace
