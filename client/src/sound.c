#include "../inc/client.h"

void event_play_audio(GtkWidget *widget, GdkEventButton *event, gpointer type)
{
    if(widget) {}
    if(event->type == GDK_BUTTON_PRESS && event->button == 1)
    {
        int num = (int)(intptr_t)type;
        play_audio(num);
    }
}

void play_audio(int type) {
    switch(type)
    {
        case 0: {
            Mix_Chunk *sound = Mix_LoadWAV(t_pokefact.pokemon_fact_audio);
            Mix_PlayChannel(-1, sound, 0);
            break;
        }
        case 1: {
            Mix_Chunk *sound = Mix_LoadWAV("client/data/sounds/low_pop.wav");
            Mix_PlayChannel(-1, sound, 0);
            break;
        }
        case 2: {
            Mix_Chunk *sound = Mix_LoadWAV("client/data/sounds/high_pop.wav");
            Mix_PlayChannel(-1, sound, 0);
            break;
        }
    }
}
