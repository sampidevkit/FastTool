/**
 * MVIO Generated Driver API Header File
 *
 * @file mvio.h
 *
 * @defgroup mvio MVIO
 *
 * @brief This header file provides APIs for the MVIO driver.
 *
 * @version MVIO Driver Version 1.1.1
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef MVIO_H
#define MVIO_H

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif 



/**
 * @ingroup mvio
 * @brief Initialize MVIO interface
 * @param none
 * @retval 0 - the MVIO init was successful
 * @retval 1 - the MVIO init was not successful
 */
int8_t MVIO_Initialize(void);

/**
 * @ingroup mvio
 * @brief API to check the status of MVIO interface
 * @param none
 * @retval true  - the VDDIO2 supply voltage is within the acceptable range for operation
 * @retval false - the VDDIO2 supply voltage is below the acceptable range for operation
 */
bool MVIO_isOK(void);

#ifdef __cplusplus
}
#endif

#endif    //MVIO_H
