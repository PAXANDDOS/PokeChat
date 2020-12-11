#include "../inc/client.h"

void play_audio() {
    Mix_Chunk *testSound = Mix_LoadWAV(pokemon_fact_audio);
    Mix_PlayChannel(-1, testSound, 0);
}
