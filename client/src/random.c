#include "../inc/client.h"

void avatar_random() {
    int pick = rand() % 100 + 1;         // Returns a pseudo-random integer between 0 and RAND_MAX.
    t_avatar.avatar_num = pick;
    t_avatar.avatar_generated = mx_strjoin(t_avatar.avatar_generated, mx_itoa(pick));
    t_avatar.avatar_generated = mx_strjoin(t_avatar.avatar_generated, ".png");
}

char *get_avatar_by_number(int num)
{
    DIR* dir = NULL;
    struct dirent *sd = NULL;
    char *path = "client/data/avatars/";
    char *error_avatar = "client/data/images/group-people.png";

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

    int num = 65;

    // dir = opendir("client/data/pokemon/");
    // if(dir == NULL) return;
    // while ((sd = readdir(dir)) != NULL) {
    //     if (sd->d_type == DT_REG) { /* If the entry is a regular file */
    //         num++;
    //     }
    // }
    // closedir(dir);

    // CHOOSING IMAGE

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

char* random_phrase()
{
    int num = rand() % 57 + 1;
    char *phrase[] = {"There's no one here!",
    "Hey, I know. I’ll use my trusty frying pan as a drying pan.",
    "Don’t worry that pretty blue head of yours, I’ve got a plan.",
    "Err...my name is...Tom Ato!",
    "I see now that one’s birth is irrelevant. It’s what you do that determines who you are.",
    "We do have a lot in common. The same earth, the same air, the same sky. Maybe if we started looking at what’s the same, instead of looking at what’s different, well, who knows?",
    "A Caterpie may change into a Butterfree, but the heart that beats inside remains the same.",
    "There’s no sense in going out of your way to get somebody to like you.",
    "I didn't know Vikings still existed...",
    "I am the Flaming Moltres!",
    "It's following Pikachu around like its a streaker or something!",
    "Even If we don’t understand each other, that’s not a reason to reject each other.",
    "Everybody makes a wrong turn once in a while.",
    "Strong Pokemon. Weak Pokemon. That is only the selfish perception of people.",
    "Make your wonderful dream a reality, it will become your truth. If anyone can, it’s you.",
    "Take charge of your destiny!",
    "Do you always need a reason to help somebody?",
    "You see, sometimes friends have to go away, but a part of them stays behind with you.",
    "The important thing is not how long you live. It’s what you accomplish with your life.",
    "I will show you that my love for my friends permeates every cell in my body.",
    "Me give up? No way!",
    "12/10. Best Chat of 2021",
    "The Last of Chats",
    "Just a regular chat, but with a little bit of Pokemon",
    "Don't forget the plug in the microwave!",
    "Jason Citron has not seen this chat",
    "Houston, we have a problem",
    "Try to find a JoJo reference",
    "Yep, we have Easter Eggs in this chat",
    "Are you chatting, son?",
    "You’re a Pokemon trainer, Harry.",
    "First Time?",
    "I’m something of a Pokemon trainer",
    "Alright then, keep your secrets",
    "Pika-Pika-Pikachu",
    "ピカチュウ",
    "Stay at home and use PokeChat",
    "Who said 'Pika Pika'?",
    "*Angry Pokemon noises*",
    "Catch 'em all!",
    "Have you seen Vaporeon?",
    "Random Pokemon vibes",
    "12345 is a bad password!",
    "Absolutely no memes",
    "Have you seen Vaporeon?",
    "Déjà vu",
    "Don’t touch your face!",
    "Exclusive!",
    "Save the world – stay inside!",
    "Stay home and use PokeChat",
    "日本ハロー！",
    "한국 안녕하세요!",
    "Donate us",
    "github.com/PAXANDDOS",
    "Team Mystic!",
    "The future is now",
    "PAXANDDOS was here"};

    return phrase[num];
}
