#include "../inc/client.h"

void avatar_random() {
    srand(time(NULL));                  // Initialization, should only be called once.
    int pick = rand() % 101 + 3;         // Returns a pseudo-random integer between 0 and RAND_MAX.

    int counter = 1;

    DIR* dir = NULL;
    struct dirent *sd = NULL;
    
    dir = opendir("client/data/avatars/");
    if(dir == NULL) return;

    while((sd = readdir(dir)) != NULL)
    {
        if(counter == pick)
            avatar_generated = mx_strjoin(avatar_generated, sd->d_name);
        counter++;
    }
    closedir(dir);
}

void pokemon_random() {
    srand(time(NULL));                  // Initialization, should only be called once.
    int pick = rand() % 10 + 3;             // Returns a pseudo-random integer between 0 and RAND_MAX.
    int counter = 1;

    DIR* dir = NULL;
    struct dirent *sd = NULL;
    
    dir = opendir("client/data/pokemon/");
    if(dir == NULL) return;

    while((sd = readdir(dir)) != NULL)
    {
        if(counter == pick)
            pokemon_fact_image = mx_strjoin(pokemon_fact_image, sd->d_name);
        counter++;
    }
    closedir(dir);

    counter = 1;
    dir = opendir("client/data/pokemon-text/");
    if(dir == NULL) return;

    while((sd = readdir(dir)) != NULL)
    {
        if(counter == pick)
            pokemon_fact_text = mx_strjoin(pokemon_fact_text, sd->d_name);
        counter++;
    }
    closedir(dir);
}
