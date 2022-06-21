#ifndef INC_SHADY_ENGINE_LOGGER_H
#define INC_SHADY_ENGINE_LOGGER_H




//C++ headers
#include<cstdio>
#include<cstdarg>
#include<memory>




namespace shady_engine
{

	class logger
	{

	
	public:
	

		~logger();

		inline static std::shared_ptr<logger> getInstance()
		{
			static std::shared_ptr<logger> instance(new logger());
			return instance;
		}


		void init(const char* pHeader);
	

		void log(const char* pFormat,...);


	private:


		FILE* file;

		logger();


		
	};

}

#endif