
#import <Appkit/Appkit.h>

#include "SoundController.h"


SoundController* SoundController::mInstance = nullptr;

NSSound* sources[3];

SoundController::SoundController(){
    
    NSString* paths[3] = {
        @"Resources/sounds/match2",
        @"Resources/sounds/tick",
        @"Resources/sounds/gem_settle"
    };
    
    NSString * fileExts[3] = {
        @"aif",
        @"mp3",
        @"mp3"
    };
    for(int i =0 ; i < 3 ; i++){
       NSSound *player = [[NSSound alloc] initWithContentsOfFile:[[NSBundle mainBundle] pathForResource:paths[i] ofType:fileExts[i]] byReference:NO];
        sources[i] = player;
    }
}

void SoundController::PlayMatchSFX(float volume)
{
    [sources[0] setVolume:volume];
    [sources[0] play];
}

void SoundController::PlaySwapSFX(float volume)
{
    
    [sources[1] setVolume:volume];
    [sources[1] play];
}

void SoundController::PlayGemSettle(float volume)
{
    [sources[2] setVolume:volume];
    [sources[2] play];
}

