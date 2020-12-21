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

    t_account.username = "PAXANDDOS";
    t_account.name = "Paul";
    t_account.password = "lunarnet";
    t_account.code =  "926228672849";
    t_account.team = 1;
    t_account.theme = 2;
    t_account.background = 1;
    t_account.avatar_chosen = 54;
    t_account.avatar = get_avatar_by_number(t_account.avatar_chosen);

    t_application.app = "PokeChat alpha 0.7.1";
    t_application.user = getenv("USER");
}
