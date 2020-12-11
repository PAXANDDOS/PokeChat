#include "../inc/client.h"

void avatar_random() {
    srand(time(NULL));                  // Initialization, should only be called once.
    int pick = rand() % 101 + 1;         // Returns a pseudo-random integer between 0 and RAND_MAX.

    int counter = 1;

    DIR* dir = NULL;
    struct dirent *sd = NULL;

    dir = opendir("client/data/avatars/");
    if(dir == NULL) return;

    while((sd = readdir(dir)) != NULL)
    {
        if(sd->d_name[0] == '.')
            continue;
        if(counter == pick)
            avatar_generated = mx_strjoin(avatar_generated, sd->d_name);
        counter++;
    }
    closedir(dir);
}

void pokemon_random() {
    DIR* dir = NULL;
    struct dirent *sd = NULL;

    // COUNTING FILES !!!! AMOUNT OF FILES IN /POKEMON/ AND /POKEMON-TEXT/ SHOULD BE THE SAME

    int num = 0;

    dir = opendir("client/data/pokemon/");
    if(dir == NULL) return;
    while ((sd = readdir(dir)) != NULL) {
        if (sd->d_type == DT_REG) { /* If the entry is a regular file */
            num++;
        }
    }
    closedir(dir);

    // CHOOSING IMAGE

    srand(time(NULL));
    int pick = rand() % num + 1;
    dir = NULL;
    sd = NULL;
 
    pokemon_fact_image = mx_strjoin(pokemon_fact_image, mx_itoa(pick));
    pokemon_fact_image = mx_strjoin(pokemon_fact_image, ".png");
    pokemon_fact_text = mx_strjoin(pokemon_fact_text, mx_itoa(pick));
    pokemon_fact_text = mx_strjoin(pokemon_fact_text, ".txt");
    pokemon_fact_audio = mx_strjoin(pokemon_fact_audio, mx_itoa(pick));
    pokemon_fact_audio = mx_strjoin(pokemon_fact_audio, ".wav");
}
