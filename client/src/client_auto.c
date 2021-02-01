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

    t_msg.current = "here..."; // Имя выбранного пользователя в плейсхолдере
    msg_data.content = NULL;

    t_application.app = "PokeChat beta 0.9.5";
    t_application.user = getenv("USER");
}
