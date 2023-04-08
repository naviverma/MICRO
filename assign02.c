/**
 * @brief Prints the welcome screen on the console
 */
void startGame()
{
    put_pixel(urgb_u32(0x00, 0x00, 0x7F));
    empty();
    printf("\n+_____________________________________________________________________________________+\n");
    printf("|                        Group 44                            |                          |\n");
    printf("|------------------------------------------------------------+--------------------------|\n");
    printf("|                                                            |        GAME LEVELS       |\n");
    printf("|                                                            |--------------------------|\n");
    printf("|      _________  ____   __________       ________           | LEVEL 1 - CODE GIVEN     |\n");
    printf("|                                                            | LEVEL 2 - CODE NOT GIVEN |\n");
    printf("|    #         #   ########  #######     ######   ########   |--------------------------|\n");
    printf("|    #  #   #  #  #        # #      #   #         #          |                          |\n");
    printf("|    #    #    #  #        # # ####       ####    #          |                          |\n");
    printf("|    #         #  #        # #     #           #  #####      |                          |\n");
    printf("|    #         #  #        # #      #          #  #          |                          |\n");
    printf("|    #         #    #######  #       #   #####    ########   |                          |\n");
    printf("|        #########   ########  #######    #########          |                          |\n");
    printf("|       #           #        # #       #  #                  |                          |\n");
    printf("|       #           #        # #        # #                  |                          |\n");
    printf("|       #           #        # #        # #######            |                          |\n");
    printf("|       #           #        # #       #  #                  |                          |\n");
    printf("|        #########   ########  #######    ##########         |                          |\n");
    printf("|                                                            |                          |\n");
    printf("| ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ |                          |\n");
    printf("|            -- --- .-. ... . / -.-. --- -.. .               |                          |\n");
    printf("|                   --. .- -- . .--.                         |                          |\n");
    printf("|                                                            |                          |\n");
    printf("|                                                            |                          |\n");
    printf("+____________________________________________________________+__________________________+\n");
    printf("\nWelcome player to our morse game!!\n");
    printf("\nTo succeed in this game you must enter the correct morse sequence ");
    printf("\nHold onto GP21 button for less than 1s for a dot and more than 1s for a dash.");
    printf("\nSelect level difficulty and begin.");
    printf("\n----- for level 1");
    printf("\n.---- for level 2");
    printf("\n");
}

/**
 * @brief Prints the 'Game Over' screen on the console
*/
void endGame()
{ 
empty();
printf("\n+________________________________________________________________________________________+\n");
printf("|                                                                                        |\n");
printf("|  ______  __      _____________      ___________      ____     ______________    _      |\n");
printf("|                                                                                        |\n");
printf("|                                                                                        |\n");
printf("|   #########    #     #        #  ########    #######   #        # #######  ######      |\n");  
printf("|  #          #     #  # #    # #  #          #       #   #      #  #        #     #     |\n");
printf("|  #    ##### #######  #    #   #  ######     #       #    #    #   ####     # ####      |\n");
printf("|  #        # #     #  #        #  #          #       #      # #    #        #     #     |\n");
printf("|    ######## #     #  #        #  ########     ######        #     #######  #     #     |\n");
printf("|                                                                                        |\n");
printf("|                                                                                        |\n");
printf("|                            --. .- -- . / --- ...- .-. . /                              |\n");
printf("|                                                                                        |\n");
printf("|         ______________     __________  ____     ___________________ _              __  |\n");
printf("+________________________________________________________________________________________+\n");
printf("\nGAME OVER!!! Better luck next time :) ");
}

/**
 * @brief Prints the 'Level Complete' screen on the console
*/
void completedLevel() {
empty();
printf("\n+_______________________________________________________________________________________+\n");
printf("|                                                                                       |\n");
printf("|                                                                                       |\n");
printf("|  ______  __      _____________      ___________      ____    ___________________      |\n");
printf("|                                                                                       |\n");
printf("|                                                                                       |\n");
printf("|               #        ######  #         #  ########  #                               |\n");
printf("|               #        #        #       #   #         #                               |\n");
printf("|               #        #####     #     #    #####     #                               |\n");
printf("|               #        #          #   #     #         #                               |\n");
printf("|               #######  #######      #       ########  #######                         |\n");
printf("|                                                                                       |\n");
printf("|      ######   #######  #       #  ###### #      #######  ######## ########            |\n");
printf("|     #        #       # # #   # #  #    # #      #           #     #                   |\n");
printf("|     #        #       # #   #   #  #####  #      ####        #     #####               |\n");
printf("|     #        #       # #       #  #      #      #           #     #                   |\n");
printf("|      #######  #######  #       #  #      ###### #######     #     ########            |\n");
printf("|                                                                                       |\n");
printf("|                               .-.. . ...- . .-.. /                                    |\n");
printf("|                      -.-. .--. .-.. --- --. ...- ..-. . -.-. .-                       |\n");
printf("|         ______________     __________  ____    __________             ___             |\n");
printf("+_______________________________________________________________________________________+\n");
printf("\nCONGRATULATIONS!! Level Complete");
}

/**
 * @brief Prints the 'Level One' screen to the console
*/
void startLevelOne() {
empty();
printf("\n+______________________________________________________________+\n");
printf("|                                                              |\n");
printf("|                                                              |\n");
printf("|  ______  __      _____________      ___________      ____    |\n");
printf("|                                                              |\n");
printf("| __         __________    ___ ________  __                    |\n");
printf("|                                                              |\n");
printf("|      #        ####### #         #  ########  #               |\n");
printf("|      #        #        #       #   #         #               |\n");
printf("|      #        #####     #     #    #####     #               |\n");
printf("|      #        #          #   #     #         #               |\n");
printf("|      #######  #######      #       ########  #######         |\n");
printf("|                                                              |\n");
printf("|               ########   #       #  #######                  |\n");
printf("|              #        #  # #     #  #                        |\n");
printf("|              #        #  #   #   #  #####                    |\n");
printf("|              #        #  #     # #  #                        |\n");
printf("|                #######   #       #  #######                  |\n");
printf("|                                                              |\n");
printf("|             .-.. . ...- .-.. / --- -. ..- .----.             |\n");
printf("|                                                              |\n");
printf("|         ______________     __________  ____                  |\n");
printf("+______________________________________________________________+\n");
printf("\nWelcome to level One!!!!");

}

/**
 * @brief Prints the 'Level Two' screen to the console
*/
void startLevelTwo() {
empty();
printf("\n+______________________________________________________________+\n");
printf("|                                                              |\n");
printf("|                                                              |\n");
printf("|  ______  __      _____________      ___________      ____    |\n");
printf("|                                                              |\n");
printf("|                                                              |\n");
printf("|         #        ######  #         #  ########  #            |\n");
printf("|         #        #        #       #   #         #            |\n");
printf("|         #        #####     #     #    #####     #            |\n");
printf("|         #        #          #   #     #         #            |\n");
printf("|         #######  #######      #       ########  #######      |\n");
printf("|                                                              |\n");
printf("|               ##########  #       #   ########               |\n");
printf("|                   #       #       #  #        #              |\n");
printf("|                   #       #   #   #  #        #              |\n");
printf("|                   #       #  #  # #  #        #              |\n");
printf("|                   #       #       #   ########               |\n");
printf("|                                                              |\n");
printf("|                                                              |\n");
printf("|             .-.. . ...- . .-.. / - --- ..-                   |\n");
printf("|                                                              |\n");
printf("|         ______________     __________  ____                  |\n");
printf("+______________________________________________________________+\n");
printf("\nWelcome to level Two!!!!");

}
