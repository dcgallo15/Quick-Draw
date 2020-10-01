#pragma once

#include <SDL.h>
#include "log.h"

class Audio {
    SDL_AudioSpec wavSpec;
    Uint32 wavLength;
    Uint8* wavBuffer;
    SDL_AudioDeviceID deviceId;
public:
    Audio();
    Audio(const char* filepath);
    ~Audio();
    void load(const char* filename);
    void play();
    void clear();
};