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
 * @brief Blocks execution until the input is a space
 */
void waitForOneSec()
{
    while (spaceOrNot == 0) {}
    spaceOrNot = 0;
}

/**
 * @brief Clears the console by printing 50 new lines
 */
void empty()
{
    for (int i = 0; i < 50; i++)
        printf("\n");
}