#include <stdio.h>
//#include "pico/stdlib.h"
//#include "hardware/gpio.h"



void welcome() 

{


  printf("\n+____________________________________________________________________________________+\n");
  printf("|                        Group 44                            |                       |\n");
  printf("|------------------------------------------------------------+-----------------------|\n");
  printf("|                                                            |      GAME LEVELS      |\n");
  printf("|                                                            |-----------------------|\n");
  printf("|                                                            |    LEVEL 1 - EASY     |\n");
  printf("|     __  __ _____ _____   ____  ________  ____  _____       |    LEVEL 2 - MEDIUM   |\n");
  printf("|    |  `/  |     |  __  )/ ___| |   ____|                   |    LEVEL 3 - HARD     |\n");
  printf("|    |  `/  | |   | |__) |( ___  |  |____                    |    LEVEL 4 - EXTREME  |\n");
  printf("|    | |  | | |   |  _  /     ) ||  _____|    ____      __   |-----------------------|\n");
  printf("|    | |  | | |   | | | |  ___) /|  |____                    |                       |\n");
  printf("|    |_|  |_|_____|_| |_||____ / |_______| ____ ____ ___     |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|      ____ _____ ____ ____  _____ _____ ____      _    ____ |                       |\n");
  printf("|    / ___|     |  __  |  ___|                               |                       |\n");
  printf("|   | |   | |   | |  ) | |_|                                 |                       |\n");
  printf("|   | |__ | |   | | /  | |___                                |                       |\n");
  printf("|      ___|_____|____ /|_____| _____ ______ ______    ____   |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|            -- --- .-. ... . / -.-. --- -.. .               |                       |\n");
  printf("|                   --. .- -- . .--.                         |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("+____________________________________________________________+_______________________+\n");
  printf("\nWelcome player to our morse game!!\n");
  printf("\nTo succeed in this game you must enter the correct morse sequence ");
  printf("\nHold onto GP21 button for less than 20s for a dot and more than 20s dor a dash.");
  printf("\nSelect difficult level and begin.");

}

void endGame()
{ 

printf("\n+______________________________________________________________+\n");
printf("|                                                              |\n");
printf("|  ______  __      _____________      ___________      ____    |\n");
printf("|                                                              |\n");
printf("|  _____          __  __ ______    ______      ________ _____  |\n");  
printf("|/ ____|   / |  |   V  |  ____|  / __ | |    / /  ____|  __ )  |\n");
printf("| |  __   /   | |    / | |__    | |  | |  | / /| |__  | |__) | |\n");
printf("| | |_ | / /  | | | V| |  __|   | |  | ||  V / |  __| |  _  /  |\n");
printf("| |__| |/ ____ || |  | | |____  | |__| | |  /  | |____| | | |  |\n");
printf("|`_____/_/    |_|_|  |_|______|  (____/   V    |______|_| |_|  |\n");
printf("|                                                              |\n");
printf("|                                                              |\n");
printf("|             --. .- -- . / --- ...- .-. . /                   |\n");
printf("|                                                              |\n");
printf("|         ______________     __________  ____                  |\n");
printf("+______________________________________________________________+\n");
printf("\nGAME OVER!!! Better luck next time :) ");

}



// Main entry point of the application
int main() {
    //stdio_init_all();              // Initialise all basic IO
    welcome();
    endGame();
    //main_asm();                    // Jump into the ASM code
    return 0;                      // Application return code
}
