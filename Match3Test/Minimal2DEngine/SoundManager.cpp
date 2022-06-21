//#include "SoundManager.h"
//
//
//using namespace irrklang;
//
//
//namespace Minimal2DEngine
//{
//
//    SoundManager* SoundManager::mInstance = nullptr;
//    
//    SoundManager* SoundManager::GetInstance(){
//        if(SoundManager::mInstance == nullptr)
//            SoundManager::mInstance = new SoundManager();
//        return SoundManager::mInstance;
//    }
//    
//	SoundManager::SoundManager()
//	{
//		mEngine = createIrrKlangDevice();
//		
//		Init();
//	}
//
//
//	SoundManager::~SoundManager()
//	{
//		mEngine->drop();
//	}
//
//
//	void SoundManager::Init()
//	{
//		mEngine = createIrrKlangDevice();
//
//		if (!mEngine)
//			throw std::runtime_error("failed to initialize sound manager!");
//	}
//
//	void SoundManager::PlaySfx(const std::string & pLocation) const
//	{
//		mEngine->play2D(pLocation.c_str());
//	}
//
//	void SoundManager::PlayMusic(const std::string & pLocation) const
//	{
//		mEngine->play2D(pLocation.c_str(),true);
//	}
//
//}
