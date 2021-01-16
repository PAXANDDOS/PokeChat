#include "../inc/client.h"

void fill_pokemon()
{
    t_pokefact.pokemon_fact_text = "client/data/pokemon-text/";
    t_pokefact.pokemon_fact_image = "client/data/pokemon/";
    t_pokefact.pokemon_fact_audio = "client/data/pokemon-audio/";
    pokemon_random();
}

void test_autofill()
{
    t_avatar.avatar_generated = "client/data/avatars/";
    avatar_random();

    t_chat.current = "Gazaris";

    t_application.app = "PokeChat alpha 0.7.9";
    t_application.user = getenv("USER");
}
