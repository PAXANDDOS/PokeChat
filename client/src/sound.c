#include "../inc/client.h"

void play_audio() {
    Mix_Chunk *testSound = Mix_LoadWAV(t_pokefact.pokemon_fact_audio);
    Mix_PlayChannel(-1, testSound, 0);
}
