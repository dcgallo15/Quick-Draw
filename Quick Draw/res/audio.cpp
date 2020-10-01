#include "../include/audio.h"

Audio::Audio() 
{
   LOG_WARN("YOU DID NOT ENTER A FILEPATH IN THE AUDIO CONSTRUCTOR");
}

Audio::Audio(const char* filepath) 
{
    load(filepath);
}

Audio::~Audio() 
{
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
}

void Audio::load(const char* filename) 
{
    SDL_LoadWAV(filename, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
}

void Audio::play() 
{
    SDL_QueueAudio(deviceId, wavBuffer, wavLength);
    SDL_PauseAudioDevice(deviceId, 0);
}

void Audio::clear() 
{
    SDL_ClearQueuedAudio(deviceId);
}