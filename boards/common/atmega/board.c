/*
 * Copyright (C) 2018 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_common
 * @{
 *
 * @file
 * @brief       Common implementations for Atmega boards
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 *
 * @}
 */

#include "board.h"
#include "cpu.h"
#include "irq.h"
#include "periph/gpio.h"

#ifndef CPU_ATMEGA_CLK_SCALE_INIT
#define CPU_ATMEGA_CLK_SCALE_INIT    CPU_ATMEGA_CLK_SCALE_DIV1
#endif

void led_init(void);

/*
 * Add an empty led_init() as fall back.
 * If at link time another implementation of led_init() not marked as weak
 * (a.k.a. a strong symbol) is present, it will be linked in instead.
 */
void __attribute__((weak)) led_init(void) {}

void board_init(void)
{
#ifdef CPU_ATMEGA32U4
    /* disable usb interrupt on Atmega32U4 */
    PRR1 |= 1<<PRUSB;
#endif

    atmega_set_prescaler(CPU_ATMEGA_CLK_SCALE_INIT);

    cpu_init();
    led_init();
    irq_enable();
}
