#ifndef _LAZY_SOUND_H
#define _LAZY_SOUND_H

//LAZY IMPLEMENTATION TO PLAY SOUND.

enum class EAudioSourceIndex
{
    MATCH = 0,
    SWAP,
    GEM_SETTLE
};

class SoundController
{
private:
  //  const int MAX_SOURCES = 3;
    static SoundController* mInstance;
    SoundController();
public:
    
    static SoundController* GetInstance(){
        if(mInstance == nullptr){
            mInstance = new SoundController();
        }
        return mInstance;
    }

    
    void PlayMatchSFX(float volume = 1.0f);
    void PlaySwapSFX(float volume = 1.0f);
    void PlayGemSettle(float volume = 1.0f);
};



#endif
