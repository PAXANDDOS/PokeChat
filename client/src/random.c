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
            t_avatar.avatar_generated = mx_strjoin(t_avatar.avatar_generated, sd->d_name);
        counter++;
    }
    closedir(dir);
}

char *get_avatar_by_number(int num)
{
    DIR* dir = NULL;
    struct dirent *sd = NULL;
    char *path = "client/data/avatars/";
    char *error_avatar = "client/data/avatars/0.png";

    dir = opendir(path);
    if(dir == NULL) return error_avatar;

    int max = 0;
    while ((sd = readdir(dir)) != NULL)
        if (sd->d_type == DT_REG)       /* If the entry is a regular file */
            max++;
    closedir(dir);
    if(num > max) 
        return error_avatar;

    path = mx_strjoin(path, mx_itoa(num));
    return mx_strjoin(path, ".png");
}

void pokemon_random() {
    DIR* dir = NULL;
    struct dirent *sd = NULL;

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
 
    t_pokefact.pokemon_fact_image = mx_strjoin(t_pokefact.pokemon_fact_image, mx_itoa(pick));
    t_pokefact.pokemon_fact_image = mx_strjoin(t_pokefact.pokemon_fact_image, ".png");
    t_pokefact.pokemon_fact_text = mx_strjoin(t_pokefact.pokemon_fact_text, mx_itoa(pick));
    t_pokefact.pokemon_fact_text = mx_strjoin(t_pokefact.pokemon_fact_text, ".txt");
    t_pokefact.pokemon_fact_audio = mx_strjoin(t_pokefact.pokemon_fact_audio, mx_itoa(pick));
    t_pokefact.pokemon_fact_audio = mx_strjoin(t_pokefact.pokemon_fact_audio, ".wav");
}
