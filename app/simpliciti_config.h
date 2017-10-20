//****************************************************************************
//
// simpliciti_config.h - Configuration options for the SimpliciTI low power RF
//                       stack.
//
// Copyright (c) 2010-2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9107 of the DK-LM3S9D96-EM2-CC2500-SIMPLICITI Firmware Package.
//
//****************************************************************************
#ifndef _SIMPLICITI_CONFIG_H_
#define _SIMPLICITI_CONFIG_H_

//****************************************************************************
//
// Radio configuration
//
//****************************************************************************
#define MRFI_CC1101

//*****************************************************************************
//
// Network Configuration Options
//
//*****************************************************************************

/**************************************************************************************************
  Filename:       smpl_nwk_config.dat
  Revised:        $Date: 2009-02-07 14:21:07 -0700 (Sat, 07 Feb 2009) $
  Revision:       $Revision: 19010 $
  Author:         $Author: lfriedman $

  Description:    This file supports the SimpliciTI Customer Configuration for overall network.

  Copyright 2007-2009 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights granted under
  the terms of a software license agreement between the user who downloaded the software,
  his/her employer (which must be your employer) and Texas Instruments Incorporated (the
  "License"). You may not use this Software unless you agree to abide by the terms of the
  License. The License limits your use, and you acknowledge, that the Software may not be
  modified, copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio frequency
  transceiver, which is integrated into your product. Other than for the foregoing purpose,
  you may not use, reproduce, copy, prepare derivative works of, modify, distribute,
  perform, display or sell this Software and/or its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS”
  WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY
  WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
  IN NO EVENT SHALL TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE
  THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY
  INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST
  DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY
  THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/


/* max hop count */
#define MAX_HOPS 3

/* max hops away from and AP. Keeps hop count and therefore replay
 * storms down for sending to and from polling End Devices. Also used
 * when joining since the EDs can't be more than 1 hop away.
 */
#define MAX_HOPS_FROM_AP 1

/* Maximum size of Network application payload. Do not change unless
 * protocol changes are reflected in different maximum network
 * application payload size.
 */
#define MAX_NWK_PAYLOAD 34

/* Maximum size of application payload */
#define MAX_APP_PAYLOAD 10

/* default Link token */
#define DEFAULT_LINK_TOKEN 0x01020304

/* default Join token */
#define DEFAULT_JOIN_TOKEN 0x05060708

/* Remove 'x' corruption to define Frequency Agility as active for this build */
#define xFREQUENCY_AGILITY

/* Remove 'x' corruption to enable application autoacknowledge support. Requires extended API as well */
#define xAPP_AUTO_ACK

/* Remove 'x' corruption to enable Extended API */
#define xEXTENDED_API

/* Remove 'x' corruption to enable security. */
#define xSMPL_SECURE

/* Remove 'x' corruption to enable NV object support. */
#define xNVOBJECT_SUPPORT

/* Remove 'x' corruption to enable software timer. */
#define SW_TIMER

/* Remove 'x' corruption to enable frequency hopping. */
#define xFREQUENCY_HOPPING

#define xBSP_TIMER_USED BSP_TIMER_A3

/* Remove 'x' corruption to make this device the reference clock. */
#define xNWK_PLL_REFERENCE_CLOCK

/* causes leds to blink in 00 -> 01 -> 11 -> 10 -> 00 rotation when FHSS enabled */
#define xNWK_PLL_SHOW_LOCATION_INDICATORS

//
// For Stellaris implementations, the following label defines which of the two
// EM2 adapter connections the radio daughter board is plugged in to.  It must
// be defined as either 0 or 1 to use the MOD1 or MOD2 connection respectively.
//
#define MOD2_CONNECTION 0

#endif // _SIMPLICITI_CONFIG_H_
