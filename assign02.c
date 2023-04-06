#include <stdio.h>
//#include "pico/stdlib.h"
//#include "hardware/gpio.h"



void welcome() 

{


  printf("\n+__________________________________________________________________________________+\n");
  printf("|                        Group 44                            |                       |\n");
  printf("|------------------------------------------------------------+-----------------------|\n");
  printf("|                                                            |      GAME LEVELS      |\n");
  printf("|                                                            |-----------------------|\n");
  printf("|                                                            |    LEVEL 1 - EASY     |\n");
  printf("|     __  __    _____    _____      _____   _______          |    LEVEL 2 - MEDIUM   |\n");
  printf("|    |  \\/  |  |  _  |  |  __  )  / _____| |   ____|         |                       |\n");
  printf("|    |  \\/  |  | | | |  | |__) |  ( ___    |  |____          |                       |\n");
  printf("|    | |  | |  | | | |  |  _  /       ) |  |  _____|         |-----------------------|\n");
  printf("|    | |  | |  | |_| |  | | | |    ___) /  |  |____          |                       |\n");
  printf("|    |_|  |_|  |_____|  |_| |_|  |____ /   |_______|         |                       |\n");
  printf("|    ______________________________________________          |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|      ___    _____    ____      _______                     |                       |\n");
  printf("|    / ___|  |  _  |  |  __ |   |   ____|                    |                       |\n");
  printf("|   | |      | | | |  | |  ) |  |  |____                     |                       |\n");
  printf("|   | |___   | |_| |  | |__) |  |  _____|                    |                       |\n");
  printf("|    \ ___|  |_____|  |____ /   |  |____                     |                       |\n");
  printf("|    ________________________   | ______|                    |                       |\n");
  printf("|    ____________________________________                    |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|            -- --- .-. ... . / -.-. --- -.. .               |                       |\n");
  printf("|                   --. .- -- . .--.                         |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("+____________________________________________________________+_______________________+\n");
  printf("\nWelcome player to our morse game!!\n");
  printf("\nTo succeed in this game you must enter the correct morse sequence ");
  printf("\nHold onto GP21 button for less than 20s for a dot and more than 20s for a dash.");
  printf("\nSelect difficultly level and begin.");

}
 


void endGame()
{ 

printf("\n+____________________________________________________________________________ +\n");
printf("|                                                                               |\n");
printf("|______________________________________________________________________________ |\n");
printf("|                                                                               |\n");
printf("|  _____       Ʌ        __  __   ______    ___   __        __  ______   _____   |\n");  
printf("| / ____|     /  \     |   V  | |  ____|  / __ \ \  \    /  / |  ____| |  __  ) |\n");
printf("|| |  __     /    \    |  \ / | | |__    | |  | | \  \ /  /   | |__    | |__) | |\n");
printf("|| | |_ |   /  /\  \   | | V| | |  __|   | |  | |  \  V  /    |  __|   |  _  /  |\n");
printf("|| |__| |  /   __   \  | |  | | | |____  | |__| |   \   /     | |____  | | | |  |\n");
printf("| \_____/ / _/    \_ \ |_|  |_| |______|  \____/      V       |______| |_| |_|  |\n");
printf("|                                                                               |\n");
printf("|                                                                               |\n");
printf("|             --. .- -- . / --- ...- .-. . /                                    |\n");
printf("|                                                                               |\n");
printf("|______________________________________________________________________________ |\n");
printf("|                                                                               |\n");
printf("+______________________________________________________________________________ +\n");
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
