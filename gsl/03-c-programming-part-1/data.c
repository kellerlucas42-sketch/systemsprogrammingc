#include <stdio.h>
#include <stdint.h>

void numberer(uint8_t input)
{
    char barf = (char) input;
    printf("%c\n", barf);
}


int main()
{   
    // print meow as hex :3
    unsigned int meow = 3735928559;
    uint8_t donkey = 38;
    uint8_t horse = 37;
    uint8_t honkey = 39;
    numberer(donkey);
    numberer(horse);
    numberer(honkey);
    printf("%x\n", meow);
    printf("%o\n", donkey);
    printf("%d\n", horse);
    printf("%i\n", honkey);
    unsigned int barfsicle = 37373737;
    printf("%f\n", barfsicle);
    return 0;
}
