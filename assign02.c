/**
 * @file assign02.c
 * @brief This file contains the source code for the assign02 project.
 */

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/multicore.h" 
#include "assign02.pio.h"
#include "assign02.h"
#include "hardware/structs/watchdog.h"
#define RGBW_FORMAT true
#define PIN_LIGHT 28
#define BUTTON_PIN 21
int waitButton;
int bitsNumber;
int spaceOrNot;
int previousState;
int livesNumber;

/**
 * @brief Wrapper to allow the assembly code to call the gpio_init()
 *        SDK function.
 * 
 * @param pin       The GPIO pin number to initialise.
 */
void asm_gpio_init(uint pin)
{
    gpio_init(pin);
}

/**
 * @brief Wrapper to allow the assembly code to call the gpio_set_dir()
 *        SDK function.
 * 
 * @param pin       The GPIO pin number of which to set the direction.
 * @param dir       Specify the direction that the pin should be set to (0=input/1=output).
 */
void asm_gpio_set_dir(uint pin, bool out)
{
    gpio_set_dir(pin, out);
}

/**
 * @brief Wrapper to allow the assembly code to call the gpio_get()
 *        SDK function.
 * 
 * @param pin       The GPIO pin number to read from.
 * @return int      Returns the current value of the GPIO pin.
 */
bool asm_gpio_get(uint pin)
{
    return gpio_get(pin);
}

/**
 * @brief Wrapper to allow the assembly code to call the gpio_put()
 *        SDK function.
 * 
 * @param pin       The GPIO pin number to write to.
 * @param value     Specify the value that the pin should be set to (0/1).
 */
void asm_gpio_put(uint pin, bool value)
{
    gpio_put(pin, value);
}


void asm_gpio_set_irq(uint pin)
{
    gpio_set_irq_enabled(pin, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
}

/**
 * @brief This function acts as the main entry-point for core #1.
 *        A function pointer is passed in via the FIFO with one
 *        incoming int32_t used as a parameter. The function will
 *        provide an int32_t return value by pushing it back on 
 *        the FIFO, which also indicates that the result is ready.
 */
void core1_entry()
{
    while (1)
    {
        int32_t (*func)() = (int32_t(*)())multicore_fifo_pop_blocking();
        int32_t p = multicore_fifo_pop_blocking();
        int32_t result = (*func)(p);
        multicore_fifo_push_blocking(result);
    }
}

/**
 * @brief This function writes a pixel to the PIO state machine.
 * 
 * @param pixel  The pixel value to write to the PIO state machine.
 */
static inline void put_pixel(uint32_t pixel)
{
    pio_sm_put_blocking(pio0, 0, pixel << 8u);
}

/**
 * @brief This function converts a RGB value to a 32-bit unsigned integer.
 * 
 * @param red The value of the red component.
 * @param green The value of the green component.
 * @param blue The value of the blue component.
 * @return uint32_t The 32-bit unsigned integer value of the RGB value.
 */
static inline uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)(red) << 8) |
           ((uint32_t)(green) << 16) |
           (uint32_t)(blue);
}

/**
 * @brief The current word buffer gets reset
 */
void bufferReset()
{
    waitButton = 1;
    bitsNumber = 0;
    previousState = 0;
    return;
}

/**
 * @brief Returns a pointer to an array of bits representing the given buffer, allowing other parts of the code to access the 
 *        buffer's binary information.
 * @param buffer The integer buffer to extract bits from.
 * @param bitsNumber The number of bits to extract from the buffer.
 * @return int* bits A pointer to an array of bits.
*/
int *arrBits(int buffer, int bitsNumber)
{
    int *bits = malloc(sizeof(int) * bitsNumber);
    for (int k = 0; k < bitsNumber; k++)
        bits[k] = (buffer & (1 << k)) >> k;
    return bits;
}

/**
 * @brief Compares the Morse code stored in the buffer with the Morse code of the letter at the specified index.
 * @param index The index of the letter to compare against the buffer.
 * @return int Returns 1 if the buffer's Morse code matches the letter's Morse code, 0 otherwise.
 */
int morseCodeCheck(int index)
{
    int *bits = arrBits(waitButton, bitsNumber);
    if (bitsNumber >= 6)
    {
        return 0;
    }
    else 
    {
        for (int i = 0; i < bitsNumber; i++)
        {
            if(bits[bitsNumber - i - 1] != (int)(morseCode[index][i + 1]) - 45) return 0;
        }
        if(morseCode[index][bitsNumber + 1] != '\0') return 0;
        return 1;
    }
}
/**
 * @brief Clears the console by printing 50 new lines
 */
void empty()
{
    for (int i = 0; i < 50; i++)
        printf("\n");
}
/* @brief Prints the welcome screen on the console
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
    printf("|___________________________________________________________ | LEVEL 1 - CODE GIVEN     |\n");
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
printf("|________________________________________________________________________________________|\n");
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
printf("|________________________________________________________________________________________|\n");
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
printf("|_______________________________________________________________________________________|\n");
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
printf("|_______________________________________________________________________________________|\n");
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
 /* @brief Prints the 'Level Two' screen to the console
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
/**
 * @brief Blocks execution until the input is a space
 */
void waitForOneSec()
{
    while (spaceOrNot == 0) {}
    spaceOrNot = 0;
}

/**
 * @brief Prints the current level information, including the lives, score, streak, and target letter with its Morse code.
 * @param level The current game level.
 * @param randomMorse The index of the random Morse code character in the morseCode array.
 * @param score The current score.
 * @param livesNumber The current number of lives.
 * @param streak The current streak.
 */
void printCurrentLevel(int level, int randomMorse, int score, int livesNumber, int streak)
{
    if(level == 1) {

        empty();
        printf("\nLives: %d \nScore: %d \nStreak: %d\nLetter to print:%c Code:", livesNumber, score, streak, morseCode[randomMorse][0]);
        for (int i = 1; morseCode[randomMorse][i] != '\0'; i++)
        {
            printf("%c", morseCode[randomMorse][i]);
        }
        printf("\n");
        return;
    }
    else if(level == 2) {
        empty();
        printf("\nLives: %d \nScore: %d \nStreak: %d\nLetter to print:%c\n", livesNumber, score, streak, morseCode[randomMorse][0]);
        return;
    }
    else return;
}
    
/** @brief Executes a countdown before starting the current level with the target letter.
 * @param level The current game level.
 * @param randomMorse The index of the random Morse code character in the morseCode array.
 * @param score The current score.
 * @param livesNumber The current number of lives.
 * @param streak The current streak.
 */
void countDown(int level, int randomMorse, int score, int livesNumber, int streak)
{
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("think.\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("think..\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("think...\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("Ready \n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("3\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("3 2\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("3 2 1\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("3 2 1 GO\n");
    waitForOneSec();
    watchdog_update();
    waitForOneSec();
    watchdog_update();
}

/**
 * @brief Designates a colour based on the lives left of the player
 * @param livesNumber The current number of lives
*/
void livesColor(int livesNumber) {
    if(livesNumber == 0) put_pixel(urgb_u32(0x7F, 0x00, 0x00));           // Red
    else if(livesNumber == 1) put_pixel(urgb_u32(0x00, 0x7F, 0x7F));      // Light Blue
    else if(livesNumber == 2) put_pixel(urgb_u32(0x80, 0x00, 0x80));      // Purple
    else put_pixel(urgb_u32(0x00, 0x7F, 0x00));                           // Green
}   

/**
 * @brief Waits for the user to input a Morse code sequence and returns the decoded character.
 * @return char The decoded character based on the user's input.
 */

char returnMorse()
{
    while (true)
    {
        if (waitButton != previousState && bitsNumber > 0)
        {

            int *bits = arrBits(waitButton, bitsNumber);
            for (int j = bitsNumber - 1; j >= 0; j--)
            {
                printf("%c", bits[j] + 45);
            }
            printf("\n");
            previousState = waitButton;
            if (bitsNumber >= 32)
            {
                bufferReset();
            }
        }

        if (spaceOrNot == 1)
        {
            spaceOrNot = 0;
            char result = '?';
            for(int i = 0; i < 36; i++)
            {
                if (morseCodeCheck(i) == 1)
                {
                    result = morseCode[i][0];
                }
            }
            return result;
        }
    }
}

/**
 * @brief Executes the first level of the game, where the user must input a given Morse code sequence to its corresponding character.
 * @return int 1 if the user completes the level successfully and moves to the next level, 0 otherwise.
 */
int levelOne()
{
    empty();
    bufferReset();
    put_pixel(urgb_u32(0x00, 0x7F, 0x00));
    startLevelOne();
    int score = 0;
    int level = 1;
    int livesNumber = 3;
    int streak = 0;

    while (true)
    {
        bufferReset();
        watchdog_update();
        if (livesNumber == 0)
        {
            livesColor(livesNumber);
            empty();
            endGame();
            return 0;
        }
        if (streak == 5)
        {
            empty();
            printf("Well Done! Level 2 can be unlocked now!\n");
            return 1;
        }
        int randomMorse = rand() % 36;

        countDown(level, randomMorse, score, livesNumber, streak);

        char result = returnMorse();

        if (result == morseCode[randomMorse][0])
        {
            score++;
            streak++;
            if(livesNumber < 3) {
                livesNumber++;
                livesColor(livesNumber);
            }
            waitForOneSec();
            watchdog_update();
            printf("Well Done! Character: %c\nStreak: %d\n", result, streak);
        }
        else
        {
            if (score > 0)
            {
                streak = 0;
            }
            livesNumber--;
            livesColor(livesNumber);
            waitForOneSec();
            watchdog_update();
            printf("Wrong! Character: %c\nStreak: %d\n", result, streak);
        }
    }
}

/**
 * @brief Executes the second level of the game, where the user must input the Morse code sequence to its corresponding character.
 *        Note that the morse code sequence is not given this time.
 * @return int 1 if the user completes the level successfully and moves to the next level, 0 otherwise.
 */
int levelTwo()
{
    empty();
    bufferReset();
    put_pixel(urgb_u32(0x00, 0x7F, 0x00));
    startLevelTwo();
    int score = 0;
    int level = 2;
    int livesNumber = 3;
    int streak = 0;
    while (true)
    {
        bufferReset();
        watchdog_update();
        if (livesNumber == 0)
        {
            livesColor(livesNumber);
            empty();
            endGame();
            return 0;
        }
        if (streak == 5)
        {
            empty();
            completedLevel();
            return 0;
        }
        int randomMorse = rand() % 36;

        countDown(level, randomMorse, score, livesNumber, streak);

        char result = returnMorse();

        if (result == morseCode[randomMorse][0])
        {
            score++;
            streak++;
            if(livesNumber < 3) {
                livesNumber++;
                livesColor(livesNumber);
            }

            waitForOneSec();
            watchdog_update();
            printf("Well Done! Character: %c\nStreak: %d\n", result, streak);
        }
        else
        {
            if (score > 0)
            {
                streak = 0;
            }
            livesNumber--;
            livesColor(livesNumber);
            waitForOneSec();
            watchdog_update();
            printf("Wrong! Character: %c\nStreak: %d\n", result, streak);
        }
    }
}

/* @brief The main process of the game that runs on core 1, handling user input and game progression.
 * @param fico A parameter not used in the function but required for core_1_process signature.
 * @return int32_t Always returns 0.
 */
int32_t core_1_process(int32_t fico)
{

    bufferReset();
    int status = 0;
    int continueProgress = 0;
    int isLocked = 0;
    while (true)
    {
        char result = returnMorse();
        if(result == '0') {

            continueProgress = levelOne();
            if (continueProgress == 1)
            {
                isLocked = 1;
            }
            status--;
        }
        else if(result == '1') 
        {
            if (isLocked == 1)
            {
                continueProgress = levelTwo();
            }
            else
            {
                bufferReset();
                empty();
                printf("\n\n Level 2 is locked, Please complete Level 1\n\n");
                waitForOneSec();
                watchdog_update();
                startGame();
            }
            status--;
        }
        else {
            bufferReset();
            if (status == 0)
            {
                startGame();
                status++;
            }
        }
    }
}

/**
 * @brief Main - Application entry point
 * @return int 0 return code
*/
int main()

{
    waitButton = 1;
    previousState = 0;
    spaceOrNot = 0;

    stdio_init_all();

    PIO pio = pio0;
    uint offset = pio_add_program(pio, &assign02_program);
    assign02_program_init(pio, 0, offset, PIN_LIGHT, 800000, RGBW_FORMAT);
    watchdog_enable(0x7fffff, 1);

    multicore_launch_core1(core1_entry);
    multicore_fifo_push_blocking((uintptr_t)&core_1_process);
    multicore_fifo_push_blocking(10);

    asm("movs r1, %0" ::"r"(&waitButton));
    asm("movs r2, %0" ::"r"(&bitsNumber));
    asm("movs r3, %0" ::"r"(&spaceOrNot));

    main_asm();

    return 0;
}
    
