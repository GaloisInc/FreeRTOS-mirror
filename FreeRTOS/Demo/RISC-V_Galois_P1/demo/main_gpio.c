/*
 * FreeRTOS Kernel V10.1.1
 * Copyright (C) 2018 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

 /*
 * main_gpio() creates one task to test the GPIO and then starts the
 * scheduler.
 */

/* Standard includes. */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Demo includes. */
#include "gpio.h"

/*-----------------------------------------------------------*/

/*
 * Called by main when PROG=main_gpio
 */
void main_gpio( void );

/*
 * The tasks as described in the comments at the top of this file.
 */
static void vTestGPIO( void *pvParameters );

/*-----------------------------------------------------------*/

void main_gpio( void )
{
	/* Create GPIO test */
	xTaskCreate( vTestGPIO, "GPIO Test", 1000, NULL, 0, NULL );

	/* Start the kernel.  From here on, only tasks and interrupts will run. */
	vTaskStartScheduler();

	/* If all is well, the scheduler will now be running, and the following
	line will never be reached.  If the following line does execute, then
	there was insufficient FreeRTOS heap memory available for the Idle and/or
	timer tasks to be created.  See the memory management section on the
	FreeRTOS web site for more details on the FreeRTOS heap
	http://www.freertos.org/a00111.html. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vTestGPIO( void *pvParameters )
{
	/* vTestGPIO() tests the AXI GPIO on the VCU118 by 
  testing that the output pins and the LEDs can be written to.
  This should be verified by measuring the pins and looking
  at the LEDs. */

  (void) pvParameters;

  /* GPIO are already set in hardware to be outputs */
  for (;;) {
    /***** WRITE TO PINS *****/
    /* Write to GPIO pin #1 */
    gpio1_write(1);
    vTaskDelay( pdMS_TO_TICKS(1000) );

    /* Write to every other LED */
    gpio2_write(1);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(3);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(5);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(7);
    vTaskDelay( pdMS_TO_TICKS(1000) );

    /***** CLEAR PINS AND WRITE TO OTHERS PINS *****/
    /* Clear GPIO pin #1 */
    gpio1_clear(1);
    vTaskDelay( pdMS_TO_TICKS(1000) );

    /* Clear those every other LEDs */
    gpio2_clear(1);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_clear(3);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_clear(5);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_clear(7);
    vTaskDelay( pdMS_TO_TICKS(1000) );

    /* Write to GPIO pin #0 */
    gpio1_write(0);
    vTaskDelay( pdMS_TO_TICKS(1000) );

    /* Write to every other LED */
    gpio2_write(0);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(2);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(4);
    vTaskDelay( pdMS_TO_TICKS(1000) );
    gpio2_write(6);
    vTaskDelay( pdMS_TO_TICKS(1000) );
  }

  vTaskDelete( NULL );
}

/*-----------------------------------------------------------*/
