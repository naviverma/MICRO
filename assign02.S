#include "hardware/regs/addressmap.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/regs/timer.h"
#include "hardware/regs/m0plus.h"

.syntax unified                                                 @ Unified assembly syntax
.cpu    cortex-m0plus                                           @ Select Cortex M0+ as the CPU type.
.thumb                                                          @ For RP2040, specify thumb assembly.
.global main_asm                                                @ Give the linker the program's starting address.
.align 4                                                        @ Code alignment specified.

 @Assigning absolute values to pins and timeouts
.equ    GPIO_BTN_ENTER,  21                 @ Set the "enter" button's pin.
.equ    GPIO_DIRECTION_IN,   0              @ Set the input direction of a GPIO pin.
.equ    GPIO_DIRECTION_OUT,  1              @ Specify output direction for a GPIO pin
.equ    ALRM_ISR_OFFSET, 0x40               @ Set the output direction of a GPIO pin.
.equ    DEFAULT_ALARM_TIME, 1000000         @ Set the timeout for the default alarm.
.equ    GPIO_ISR_OFFSET, 0x74               @ GPIO is integer #13
.equ    GPIO_PRESSED,   0x00400000
.equ    GPIO_RELEASED,    0x00800000

main_asm:
    bl      button_adder
    bl      initialise_buttons                                   @ To configure falling-edge interrupts, use the asm gpio set irq C function.
    bl      install_gpio_isr                                    
    bl      install_alrm_isr
    bl      set_alarm
    bl      loop

loop:  
    wfi                                                 @ Wait for an interruption.    
    b       loop                                        @ Infinite Loop

button_adder:
    push    {lr}
    ldr     r0, =button_state                            @ set r0 to the address of the variable button state
    str     r1, [r0]                                    @ keep the button_ state address in r1 as button state value 
    ldr     r0, =number_of_bits                          @ set r0 to the number of bits variable's address
    str     r2, [r0]                                    @ As the value of button state, save the number of bits address in r2.
    ldr     r0, =space_Adder
    str     r3, [r0]
    pop     {pc}

initialise_buttons:
    push    {lr}
    movs    r0, #GPIO_BTN_ENTER               @ Change the value of the button pin to r0.
    bl      asm_gpio_init                     @ Initialized pin
    movs    r0, #GPIO_BTN_ENTER               @ Change the value of the button pin to r0.
    movs    r1, #GPIO_DIRECTION_IN            @ Set the input pin's direction.
    bl      asm_gpio_set_dir                  @ Set the direction of the input pin.
    movs    r0, #GPIO_BTN_ENTER               @ Change the value of the button pin to r0.
    bl      asm_gpio_set_irq                  @ Set the pin's falling edge inturrupt.
    pop     {pc}

install_gpio_isr:
    ldr    r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)    @ Input the VTOR's address location into r2.
    ldr    r1, [r2]                                @ Fetch the VTOR's memory contents and save them to r1.
    movs   r2, #GPIO_ISR_OFFSET                   @ Specify the GPIO interrupt in which we are interested.
    add    r2, r1                                  @To the VTOR base address location, add the entry offset.
    ldr    r0, =gpio_isr                           @ Load the updated ALARM ISR's address to r0.
    str    r0, [r2]                                @ Return the updated SVC ISR to the proper VTOR entry.
    @ Clear and then set the ALARM0 IRQ to enable it.
    movs   r1, #1                                 @ Set a single bit to clear and then the appropriate interrupt.
    lsls   r1, #13                                @ Because GPIO is interrupt number 13, we shift left by zero.
    ldr    r2, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET) @ In r2, enter the value of the NVIC ICPR register (disables interrupts)
    str    r1, [r2]                                @ Disable the GPIO interrupt (bit offset previously stored in r1)
    ldr    r2, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET) @ In r2, enter the value of the NVIC ICPR register (enables interrupts)
    str    r1, [r2]                                @ Turn on the GPIO interrupt (bit offset previously stored in r1)
    bx     lr                                       @ Close the subroutine.


set_alarm:
    push   {lr}                                   @ Because we will be using nested subroutines, add LR to the stack.
    movs   r1, #1                                 @ ALARM0 target stored in r1
    ldr    r2, =TIMER_BASE                         @ Set the TIMER module's base address in r2.
    str    r1, [r2, #TIMER_INTE_OFFSET]            @ Enable the ALARM0 interrupt function (stored in r1)
    ldr    r1, [r2, #TIMER_TIMELR_OFFSET]          @ Take the lower 32-bit timer value and store it in register r1.
    ldr    r0, =timer
    ldr    r0, [r0]
    add    r1, r0                                  @ Add the desired delay to the timer value we already have.
    str    r1, [r2, #TIMER_ALARM0_OFFSET]          @ Save the new time we want the alarm to sound (current + delay).
    pop    {pc}
    
install_alrm_isr:
    push   {r2, lr}                               @ Push LR and any registers that will be changed to the stack.
    ldr    r2, =(PPB_BASE + M0PLUS_VTOR_OFFSET)    @ Input the VTOR's address location into r2.
    ldr    r1, [r2]                                @ Fetch the VTOR's memory contents and store them in r1.
    movs   r2, #ALRM_ISR_OFFSET                   @ Enter the ALARM interrupt that we're looking for (ALARM0 here)
    add    r2, r1                                  @ To the VTOR base address location, add the entry offset.
    ldr    r0, =alrm_isr                           @ Load the updated ALARM ISR's address to r0.
    str    r0, [r2]                                @ Return the updated SVC ISR to the proper VTOR entry.
    movs   r1, #1                                 @ Set a single bit to clear and then the appropriate interrupt.
    lsls   r1, #0                                 @ ALARM0 is interrupt number 0, so we shift left by 0.
    ldr    r2, =(PPB_BASE + M0PLUS_NVIC_ICPR_OFFSET) @ In r2, enter the value of the NVIC ICPR register (disables interrupts)
    str    r1, [r2]                                @ Turn off the ALARM0 interrupt (bit offset previously stored in r1)
    ldr    r2, =(PPB_BASE + M0PLUS_NVIC_ISER_OFFSET) @ In r2, enter the value of the NVIC ISER register (enables interrupts)
    str    r1, [r2]                                @ Turn on the ALARM0 interrupt (bit offset previously stored in r1)
    pop   {r2, pc}

.thumb_func
alrm_isr:
    push    {lr}                @ Because we will be using nested subroutines, add LR to the stack.
    mov     r0, sp              @ In r0, save the current stack pointer.
    bl      clear_interrupt    @ To clear the interrupt flag, call subroutine.
    ldr     r1, [r0, #4]        @ Load the stack address of the argument passed to the ISR into r1.
    bl      handle_alarm       @ With the passed argument, call the subroutine to handle the alarm.
    pop     {pc}                @ Return the LR from the stack to the PC to exit the ISR.

clear_interrupt:
    ldr     r0, =TIMER_BASE     @ Load the TIMER module's base address into r0.
    movs    r1, #1              @ ALARM0 target stored in r1
    str     r1, [r0, #TIMER_INTR_OFFSET]    @ To clear the pending interrupt, write to the TIMER INTR register.
    bx      lr                  @ Return to the subroutine

handle_alarm:
    push    {r0, lr}            @ r0 and LR are saved to the stack.
    mov     r0, r1              @ r0 should be copied with the passed argument.
    bl      space_setting       @ Subroutine is called to perform space setting operation with argument in r0.
    bl      set_alarm           @ Subroutine is called to set the next alarm.
    pop     {r0, pc}            @ Return from subroutine after removing r0 and LR from the stack.


.thumb_func
gpio_isr:

    push  {lr}
    @ Fetch the interrupt event from the status register
    ldr   r4, =(IO_BANK0_BASE + IO_BANK0_PROC0_INTS2_OFFSET) @ Set the INTS2 register's address in the IO Bank.
    ldr   r3, [r4]                                           @ To obtain the event, read the interrupt status register.
    movs  r1, r3                                            @ r3 should be loaded with its value.

    ldr   r5, =GPIO_RELEASED                                   @ Get the mask value used to detect a falling-edge event when you press the "down" button.
    tst   r3, r5                                             @ Check to see if the stored event matches the "down" button.
    beq   gpio_pressed

    ldr   r5, =GPIO_PRESSED                                  @ Get the mask value used to detect a falling-edge event when you press the "down" button.
    tst   r3, r5                                             @ Check to see if the stored event matches the "down" button.
    beq   gpio_released

    

gpio_pressed:
    push    {r0-r7}
    bl      set_alarm
    ldr     r0, = initial_time
    ldr     r1, =(TIMER_BASE + TIMER_TIMELR_OFFSET)         @ set r1 to the TIMELR address (system timestamp)
    ldr     r1, [r1]                                        @ set r1 to the TIMELR value
    str     r1, [r0]
    b       gpio_isr_done 

gpio_released:
    push    {r0-r7}
    bl      set_alarm
    ldr     r0, = end_time
    ldr     r1, =(TIMER_BASE + TIMER_TIMELR_OFFSET)                   @ set r1 to the TIMELR address (system timestamp)
    ldr     r1, [r1]                                                  @ set r1 to the TIMELR value
    str     r1, [r0]
    ldr     r0, [r0]
    ldr     r2, =initial_time
    ldr     r2, [r2]
    subs    r0,r0,r2
    ldr     r1, =maximum
    ldr     r1, [r1]
    cmp     r0, r1
    bhi     long_press_for_dash
    bls     short_press_for_dot

long_press_for_dash:
    ldr     r0, =button_state                                          @ set r0 to the address of the variable button state
    ldr     r2, [r0]                                                  @ set r2 to the value of button state (button state address)
    ldr     r1, [r2]
    lsls    r1, #1
    movs    r3, #0
    add     r1, r1, r3
    str     r1, [r2]                                                  @ The TIMELR value is saved in the button state variable.
    b       increment_num_bits

short_press_for_dot:
    ldr     r0, =button_state                                          @ set r0 to the address of the variable button state
    ldr     r2, [r0]                                                  @ set r2 to the value of button state (button state address)
    ldr     r1, [r2]
    lsls    r1, #1
    movs    r3, #1
    add     r1, r1, r3
    str     r1, [r2]                                                  @ The TIMELR value is saved in the button state variable.
    b       increment_num_bits

increment_num_bits:
    ldr     r0, =number_of_bits                                        @ set r0 to the address of the variable button state
    ldr     r2, [r0]                                                  @ set r2 to the value of button state (button state address)
    ldr     r1, [r2]
    movs    r0, #1
    add     r1, r1, r0
    str     r1, [r2]
    b       gpio_isr_done

gpio_isr_done:
    pop   {r0-r7} 
    ldr   r2, =(IO_BANK0_BASE + IO_BANK0_INTR2_OFFSET)        @ Set the INTR2 register's address in the IO Bank.
    str   r1, [r2]                                            @ To clear all pending interrupts, write to the GPIO INTR2 register.
    pop   {pc} 

space_setting:
    push   {lr}
    ldr    r0, =space_Adder
    ldr    r0,[r0]
    movs   r1, #1
    str    r1, [r0]
    pop    {pc}

@ Set data alignment
.data
button_state:    .word   1
number_of_bits:  .word   1
space_Adder:  .word   1
end_time:     .word   0
initial_time:      .word   0
maximum:      .word   150000
timer:          .word   DEFAULT_ALARM_TIME
    .align 4
