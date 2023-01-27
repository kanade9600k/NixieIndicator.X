/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F1938
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip software and any
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party
    license terms applicable to your use of third party software (including open source software) that
    may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

// 各ピンの名前設定
#define DIGIT_7 RB2
#define DIGIT_6 RB1
#define DIGIT_5 RB0
#define DIGIT_4 RA7
#define DIGIT_3 RA6
#define DIGIT_2 RA5
#define DIGIT_1 RA4
#define DIGIT_0 RA3
#define DIGIT_PREFIX RA2
#define DIGIT_UNIT RA1
#define DECODER_D RB7
#define DECODER_C RB6
#define DECODER_B RB5
#define DECODER_A RB4
#define DOT RB3

// 関数プロトタイプ
void send_to_decoder(unsigned char);

/*
                         Main application
 */
void main(void)
{
  // initialize the device
  SYSTEM_Initialize();

  // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
  // Use the following macros to:

  // Enable the Global Interrupts
  // INTERRUPT_GlobalInterruptEnable();

  // Enable the Peripheral Interrupts
  // INTERRUPT_PeripheralInterruptEnable();

  // Disable the Global Interrupts
  // INTERRUPT_GlobalInterruptDisable();

  // Disable the Peripheral Interrupts
  // INTERRUPT_PeripheralInterruptDisable();
  unsigned long tmp_count = 0;
  unsigned char digit = 0;

  while (1)
  {
    // Add your application code
    for (unsigned long count = 0; count < 99999999; count++)
    {
      for (unsigned char i = 0; i < 100; i++)
      {
        // 左(下位桁)から右(上位桁)に向けて表示
        DIGIT_UNIT = 1;
        send_to_decoder(0);
        __delay_us(200);
        DIGIT_UNIT = 0;

        DIGIT_PREFIX = 1;
        send_to_decoder(0);
        __delay_us(200);
        DIGIT_PREFIX = 0;

        tmp_count = count;
        for (unsigned char j = 0; j < 8; j++)
        {
          digit = tmp_count % 10;

          switch (j)
          {
          case 0:
            DIGIT_0 = 1;
            break;
          case 1:
            DIGIT_1 = 1;
            break;
          case 2:
            DIGIT_2 = 1;
            break;
          case 3:
            DIGIT_3 = 1;
            break;
          case 4:
            DIGIT_4 = 1;
            break;
          case 5:
            DIGIT_5 = 1;
            break;
          case 6:
            DIGIT_6 = 1;
            break;
          case 7:
            DIGIT_7 = 1;
            break;
          default:
            break;
          }

          send_to_decoder(digit);
          __delay_us(200);

          switch (j)
          {
          case 0:
            DIGIT_0 = 0;
            break;
          case 1:
            DIGIT_1 = 0;
            break;
          case 2:
            DIGIT_2 = 0;
            break;
          case 3:
            DIGIT_3 = 0;
            break;
          case 4:
            DIGIT_4 = 0;
            break;
          case 5:
            DIGIT_5 = 0;
            break;
          case 6:
            DIGIT_6 = 0;
            break;
          case 7:
            DIGIT_7 = 0;
            break;
          default:
            break;
          }

          tmp_count /= 10;
        }
      }
    }
  }
}

void send_to_decoder(unsigned char digit)
{
  switch (digit)
  {
  case 0:
    DECODER_D = 0;
    DECODER_C = 0;
    DECODER_B = 0;
    DECODER_A = 0;
    break;

  case 1:
    DECODER_D = 0;
    DECODER_C = 0;
    DECODER_B = 0;
    DECODER_A = 1;
    break;

  case 2:
    DECODER_D = 0;
    DECODER_C = 0;
    DECODER_B = 1;
    DECODER_A = 0;
    break;

  case 3:
    DECODER_D = 0;
    DECODER_C = 0;
    DECODER_B = 1;
    DECODER_A = 1;
    break;

  case 4:
    DECODER_D = 0;
    DECODER_C = 1;
    DECODER_B = 0;
    DECODER_A = 0;
    break;

  case 5:
    DECODER_D = 0;
    DECODER_C = 1;
    DECODER_B = 0;
    DECODER_A = 1;
    break;

  case 6:
    DECODER_D = 0;
    DECODER_C = 1;
    DECODER_B = 1;
    DECODER_A = 0;
    break;

  case 7:
    DECODER_D = 0;
    DECODER_C = 1;
    DECODER_B = 1;
    DECODER_A = 1;
    break;

  case 8:
    DECODER_D = 1;
    DECODER_C = 0;
    DECODER_B = 0;
    DECODER_A = 0;
    break;

  case 9:
    DECODER_D = 1;
    DECODER_C = 0;
    DECODER_B = 0;
    DECODER_A = 1;
    break;

  default:
    DECODER_D = 1;
    DECODER_C = 1;
    DECODER_B = 1;
    DECODER_A = 1;
    break;
  }
}

/**
 End of File
*/