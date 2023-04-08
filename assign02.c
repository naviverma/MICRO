/**
 * @brief Executes a countdown before starting the current level with the target letter.
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
    printf("3\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("2\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("1\n");
    waitForOneSec();
    watchdog_update();
    printCurrentLevel(level, randomMorse, score, livesNumber, streak);
    printf("GO\n");
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

/**
 * @brief The main process of the game that runs on core 1, handling user input and game progression.
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
    