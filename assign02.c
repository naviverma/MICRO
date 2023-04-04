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
  printf("|                                                            |    LEVEL 2 - MEDIUM   |\n");
  printf("|                                                            |    LEVEL 3 - HARD     |\n");
  printf("|                                                            |    LEVEL 4 - EXTREME  |\n");
  printf("|                                                            |-----------------------|\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("|                                                            |                       |\n");
  printf("+____________________________________________________________+_______________________+\n");

}

void endGame()
{ 
  printf("\n+____________________________________________________________+\n");
  printf("|                                                            |\n");
  printf("|        ########        #      #       #   ########         |\n");
  printf("|        #             #   #    # #   # #   #                |\n");
  printf("|        #           #       #  #  # #  #   #                |\n");
  printf("|        #    ###    #########  #   #   #   ########         |\n");
  printf("|        #      #    #       #  #       #   #                |\n");
  printf("|        #      #    #       #  #       #   #                |\n");
  printf("|        ########    #       #  #       #   ########         |\n");
  printf("|                                                            |\n");
  printf("|         #######     #       #  #########   #######     #   |\n"),
  printf("|        #       #    #       #  #           #      #    #   |\n");
  printf("|        #       #    #       #  #           #      #    #   |\n");
  printf("|        #       #    #       #  #########   # # # #     #   |\n");
  printf("|        #       #    #       #  #           #  #        #   |\n");
  printf("|        #       #     #     #   #           #    #          |\n");
  printf("|         #######         #      ##########  #      #    #   |\n");
  printf("|                                                            |\n");
  printf("+____________________________________________________________+\n");


}

// Main entry point of the application
int main() {
    //stdio_init_all();              // Initialise all basic IO
    welcome();
    endGame();
    //main_asm();                    // Jump into the ASM code
    return 0;                      // Application return code
}
