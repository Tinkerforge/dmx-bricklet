/* dmx-bricklet
 * Copyright (C) 2017 Olaf Lüke <olaf@tinkerforge.com>
 *
 * config_dmx.h: DMX specific configurations
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef CONFIG_DMX_H
#define CONFIG_DMX_H

#include "xmc_common.h"

#define DMX_LED_RED_PIN         P4_4
#define DMX_LED_YELLOW_PIN      P0_15

#define DMX_USIC_CHANNEL        USIC1_CH1
#define DMX_USIC                XMC_UART1_CH1

#define DMX_RX_PIN              P3_0
#define DMX_RX_INPUT            XMC_USIC_CH_INPUT_DX0
#define DMX_RX_SOURCE           0b100 // DX0E

#define DMX_TX_PIN              P2_12
#define DMX_TX_PIN_AF           (XMC_GPIO_MODE_OUTPUT_PUSH_PULL_ALT7 | P2_12_AF_U1C1_DOUT0)

#define DMX_NRXE_PIN            P2_11
#define DMX_TXE_PIN             P2_10

#define DMX_NRXE_AND_TXE_PORT   XMC_GPIO_PORT2
#define DMX_NRXE_PIN_NUM        11
#define DMX_TXE_PIN_NUM         10

#define DMX_TIMER_CCU4          CCU41
#define DMX_TIMER_CCU4_SLICE    CCU41_CC41

#define DMX_SERVICE_REQUEST_RX  2  // receive
#define DMX_SERVICE_REQUEST_TX  3  // transfer
#define DMX_SERVICE_REQUEST_TFF 4  // transfer frame finished
#define DMX_SERVICE_REQUEST_RXA 5  // alternate receive (parity error)

// Make sure that the priorities are as follows
// RX > TX = TFF
// TFF should never displace TX. TFF is unnecessary if we are in TX IRQ
// TX should never displace TFF. This would be a race condition
// RX interrupt will never be issued if TXE is set. If we are receiving a message,
// TX should never interrupt RX (we would lose data in this case)
// For full-duplex there is no TFF and RX should be higher priority then TX
#define DMX_IRQ_RX              11
#define DMX_IRQ_RX_PRIORITY     1
#define DMX_IRQCTRL_RX          XMC_SCU_IRQCTRL_USIC1_SR2_IRQ11

#define DMX_IRQ_TX              12
#define DMX_IRQ_TX_PRIORITY     1
#define DMX_IRQCTRL_TX          XMC_SCU_IRQCTRL_USIC1_SR3_IRQ12

#define DMX_IRQ_TFF             13
#define DMX_IRQ_TFF_PRIORITY    1
#define DMX_IRQCTRL_TFF         XMC_SCU_IRQCTRL_USIC1_SR4_IRQ13

#define DMX_IRQ_RXA             14
#define DMX_IRQ_RXA_PRIORITY    1
#define DMX_IRQCTRL_RXA         XMC_SCU_IRQCTRL_USIC1_SR5_IRQ14

#define DMX_IRQ_TIMER           21
#define DMX_IRQ_TIMER_PRIORITY  0
#define DMX_IRQCTRL_TIMER       XMC_SCU_IRQCTRL_CCU41_SR0_IRQ21

#endif
