/**********************************************************************************************************************
 * \file Cpu0_Main.c
 * \copyright Copyright (C) Infineon Technologies AG 2019
 * 
 * Use of this file is subject to the terms of use agreed between (i) you or the company in which ordinary course of 
 * business you are acting and (ii) Infineon Technologies AG or its licensees. If and as long as no such terms of use
 * are agreed, use of this file is subject to following:
 * 
 * Boost Software License - Version 1.0 - August 17th, 2003
 * 
 * Permission is hereby granted, free of charge, to any person or organization obtaining a copy of the software and 
 * accompanying documentation covered by this license (the "Software") to use, reproduce, display, distribute, execute,
 * and transmit the Software, and to prepare derivative works of the Software, and to permit third-parties to whom the
 * Software is furnished to do so, all subject to the following:
 * 
 * The copyright notices in the Software and this entire statement, including the above license grant, this restriction
 * and the following disclaimer, must be included in all copies of the Software, in whole or in part, and all 
 * derivative works of the Software, unless such copies or derivative works are solely in the form of 
 * machine-executable object code generated by a source language processor.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE 
 * COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN 
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
 * IN THE SOFTWARE.
 *********************************************************************************************************************/
 /*\title MULTICAN RX FIFO data transmission
 * \abstract MULTICAN is used to exchange data using RX FIFO structure between two nodes, implemented in the same device using Loop-Back mode.
 * \description The CAN messages are sent from CAN node 0 over CAN bus (in case of Loop-Back mode all nodes can access
 *              the internal bus). CAN node 1 receives the transmitted messages and stores them inside of RX FIFO
 *              buffer structure. Once the RX FIFO buffer threshold value has been reached, an interrupt service
 *              request is generated. CPU 1 handles the interrupt service request and reads the received CAN messages
 *              from the RX FIFO buffer. The content of the received data will be compared to the content of the
 *              transmitted CAN messages and in case of success, an LED is turned on to confirm the message reception.
 *
 * \name MULTICAN_RX_FIFO_1_KIT_TC297_TFT
 * \version V1.0.2
 * \board APPLICATION KIT TC2X7 V1.1, KIT_AURIX_TC297_TFT_BC-Step, TC29xTA/TX_B-Step
 * \keywords CAN, FIFO, INTERRUPT, LOOP-BACK, MULTICAN, MULTICAN_RX_FIFO_1, AURIX
 * \documents https://www.infineon.com/aurix-expert-training/Infineon-AURIX_MULTICAN_RX_FIFO_1_KIT_TC297_TFT-TR-v01_00_02-EN.pdf
 * \documents https://www.infineon.com/aurix-expert-training/TC29B_iLLD_UM_1_0_1_12_0.chm
 * \lastUpdated 2021-06-29
 *********************************************************************************************************************/
// These includes for the timer need to be placed here, otherwise compilation fails
// with "token <integer> deleted" on another include file
#include "IfxStm.h"
#include "Bsp.h"

#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"
#include "MULTICAN_RX_FIFO.h"
#include "CPU_Perf_Counters.h"

#include <stdio.h>

IfxCpu_syncEvent g_cpuSyncEvent = 0;
//IfxCpu_Perf g_perfCounts;                       /* Need to be global to display in the Watch View of the debugger   */

// This function with these parameters take maximum 3ms, while considering interrupts
void TASK25MS(void) {

    uint32 i;
    for(i = 0; i < 100000; i++) { }
    for(i = 0; i < 100000; i++) { }

}

// This function with these parameters take maximum 3ms, while considering interrupts
void TASK100MS(void) {

    uint32 i;
    for(i = 0; i < 100000; i++) { }
    for(i = 0; i < 100000; i++) { }
}

int core0_main(void)
{
    IfxCpu_enableInterrupts();

    /* !!WATCHDOG0 AND SAFETY WATCHDOG ARE DISABLED HERE!!
     * Enable the watchdogs and service them periodically if it is required
     */
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
    
    /* Wait for CPU sync event */
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    /* Application code: initialization of MULTICAN and transmission of the CAN messages */
    initMultican();
    initLed();

    // Amount of ticks needed to count a 25ms wait time
    Ifx_TickTime ticksFor25ms = IfxStm_getTicksFromMilliseconds(&MODULE_STM0, 25);

    uint8 i = 0;
    uint64 t1, t2, tdelta;
    while(1) {
//        IfxCpu_resetAndStartCounters(IfxCpu_CounterMode_normal);
        t1 = IfxStm_get(&MODULE_STM0);
        TASK25MS();
        i++;

        if(i == 4) {
            TASK100MS();
            i = 0;
        }
        t2 = IfxStm_get(&MODULE_STM0);

        // ticks passed since beginning of execution
        tdelta = t2 - t1;

//        g_perfCounts = IfxCpu_stopCounters();
//        printPerfCounters(g_perfCounts, 0);

        waitTime(ticksFor25ms - tdelta);
//        printf("Execution time: %d ticks.\n", tdelta);
    }

    return (1);
}