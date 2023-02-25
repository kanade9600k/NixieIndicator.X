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
        Device            :  PIC16F1939
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
// 左のニキシー管から0, 1, ..., 9桁目という風にカウント
#define DIGIT_0 RB7
#define DIGIT_1 RB6
#define DIGIT_2 RB5
#define DIGIT_3 RB4
#define DIGIT_4 RB3
#define DIGIT_5 RB2
#define DIGIT_6 RB1
#define DIGIT_7 RB0
#define DIGIT_8 RD7
#define DIGIT_9 RD6
#define DECODER0_D RA0
#define DECODER0_C RA1
#define DECODER0_B RA2
#define DECODER0_A RA3
#define DOT0 RA4
#define DECODER1_D RA5
#define DECODER1_C RE0
#define DECODER1_B RE1
#define DECODER1_A RE2
#define DOT1 RA7
#define DECODER2_D RA6
#define DECODER2_C RC0
#define DECODER2_B RC1
#define DECODER2_A RC2
#define DOT2 RD0
// 定数
#define DIGITS 10           // ニキシー管の桁数
#define LIGHTING_TIME 800   // 点灯時間(us)
#define EXTINCTION_TIME 200 // 消灯時間(us)

typedef enum
{
  UPPER,
  MIDDLE,
  LOWER,
} NIXIE_GLOUP;

// 関数プロトタイプ

void show_character(char, char, signed char);
void on_digit(signed char);
void off_digit(signed char);

// グローバル変数
// 0,1: 最上位桁のドット, 数字・文字 ... 18, 19: 最下位桁のドット, 数字・文字 (現状10桁)
char chars[DIGITS * 2] = {'.', '0', '.', '1', ' ', '2', ' ', '3', ' ', '4', ' ', '5', '.', '6', ' ', '7', ' ', 'k', ' ', 'h'};

/* Main application */
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

  while (1)
  {
    show_character(chars[0], chars[1], 0);
    show_character(chars[8], chars[9], 4);
    show_character(chars[16], chars[17], 8);
    __delay_us(LIGHTING_TIME);
    off_digit(0);
    off_digit(4);
    off_digit(8);
    __delay_us(EXTINCTION_TIME);

    show_character(chars[2], chars[3], 1);
    show_character(chars[10], chars[11], 5);
    show_character(chars[18], chars[19], 9);
    __delay_us(LIGHTING_TIME);
    off_digit(1);
    off_digit(5);
    off_digit(9);
    __delay_us(EXTINCTION_TIME);

    show_character(chars[4], chars[5], 2);
    show_character(chars[12], chars[13], 6);
    __delay_us(LIGHTING_TIME);
    off_digit(2);
    off_digit(6);
    __delay_us(EXTINCTION_TIME);

    show_character(chars[6], chars[7], 3);
    show_character(chars[14], chars[15], 7);
    __delay_us(LIGHTING_TIME);
    off_digit(3);
    off_digit(7);
    __delay_us(EXTINCTION_TIME);
  }
}

/* ニキシー管に数字・文字を表示する関数
  引数:
    dot (char): ドットを表示するか('.': 表示, それ以外: 非表示)
    character (char): 表示する数字・文字
    digit (signed char): 表示したい桁
*/
void show_character(char dot, char character, signed char digit)
{
  // 表示するダイナミック制御のグループを選択
  NIXIE_GLOUP group;
  if (digit < 4)
  {
    group = UPPER;
  }
  else if (digit < 8)
  {
    group = MIDDLE;
  }
  else
  {
    group = LOWER;
  }

  // ドットの表示
  if (dot == '.')
  {
    switch (group)
    {
    case UPPER:
      DOT0 = 1;
      break;
    case MIDDLE:
      DOT1 = 1;
      break;
    case LOWER:
      DOT2 = 1;
    default:
      break;
    }
  }
  else
  {
    switch (group)
    {
    case UPPER:
      DOT0 = 0;
      break;
    case MIDDLE:
      DOT1 = 0;
      break;
    case LOWER:
      DOT2 = 0;
    default:
      break;
    }
  }

  // 表示する数値，文字の決定
  switch (character)
  {
  case '0':
  case 'u':
  case 'W':
    // 0, u, Wのときはデコーダに0を送る。さらに次の桁の文字が.の場合はドットを表示する
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 0;
      DECODER0_B = 0;
      DECODER0_A = 0;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 0;
      DECODER1_B = 0;
      DECODER1_A = 0;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 0;
      DECODER2_B = 0;
      DECODER2_A = 0;
      break;

    default:
      break;
    }
    break;

  case '1':
  case 'n':
  case 'A':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 0;
      DECODER0_B = 0;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 0;
      DECODER1_B = 0;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 0;
      DECODER2_B = 0;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;

  case '2':
  case '%':
  case 'O': // 大文字OはΩを表示
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 0;
      DECODER0_B = 1;
      DECODER0_A = 0;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 0;
      DECODER1_B = 1;
      DECODER1_A = 0;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 0;
      DECODER2_B = 1;
      DECODER2_A = 0;
      break;

    default:
      break;
    }
    break;

  case '3':
  case 'p': // 大文字PはPを表示, 小文字pはΠを表示
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 0;
      DECODER0_B = 1;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 0;
      DECODER1_B = 1;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 0;
      DECODER2_B = 1;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;

  case '4':
  case 'k':
  case 'S':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 1;
      DECODER0_B = 0;
      DECODER0_A = 0;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 1;
      DECODER1_B = 0;
      DECODER1_A = 0;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 1;
      DECODER2_B = 0;
      DECODER2_A = 0;
      break;

    default:
      break;
    }
    break;

  case '5':
  case 'M':
  case 'V':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 1;
      DECODER0_B = 0;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 1;
      DECODER1_B = 0;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 1;
      DECODER2_B = 0;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;

  case '6':
  case 'm':
  case 'H': // ヘルツ(Hz)はh, ヘンリー(H)はHで表示
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 1;
      DECODER0_B = 1;
      DECODER0_A = 0;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 1;
      DECODER1_B = 1;
      DECODER1_A = 0;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 1;
      DECODER2_B = 1;
      DECODER2_A = 0;
      break;

    default:
      break;
    }
    break;

  case '7':
  case '+':
  case 'h':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 0;
      DECODER0_C = 1;
      DECODER0_B = 1;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 0;
      DECODER1_C = 1;
      DECODER1_B = 1;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 0;
      DECODER2_C = 1;
      DECODER2_B = 1;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;

  case '8':
  case '-':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 1;
      DECODER0_C = 0;
      DECODER0_B = 0;
      DECODER0_A = 0;
      break;

    case MIDDLE:
      DECODER1_D = 1;
      DECODER1_C = 0;
      DECODER1_B = 0;
      DECODER1_A = 0;
      break;

    case LOWER:
      DECODER2_D = 1;
      DECODER2_C = 0;
      DECODER2_B = 0;
      DECODER2_A = 0;
      break;

    default:
      break;
    }
    break;

  case '9':
  case 'P':
  case 'F':
    switch (group)
    {
    case UPPER:
      DECODER0_D = 1;
      DECODER0_C = 0;
      DECODER0_B = 0;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 1;
      DECODER1_C = 0;
      DECODER1_B = 0;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 1;
      DECODER2_C = 0;
      DECODER2_B = 0;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;

  case ' ': // 空白もしくはその他の場合
  default:
    switch (group)
    {
    case UPPER:
      DECODER0_D = 1;
      DECODER0_C = 1;
      DECODER0_B = 1;
      DECODER0_A = 1;
      break;

    case MIDDLE:
      DECODER1_D = 1;
      DECODER1_C = 1;
      DECODER1_B = 1;
      DECODER1_A = 1;
      break;

    case LOWER:
      DECODER2_D = 1;
      DECODER2_C = 1;
      DECODER2_B = 1;
      DECODER2_A = 1;
      break;

    default:
      break;
    }
    break;
  }

  // 値の表示
  on_digit(digit);
}

void on_digit(signed char digit)
{
  switch (digit)
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
  case 8:
    DIGIT_8 = 1;
    break;
  case 9:
    DIGIT_9 = 1;
    break;
  default:
    break;
  }
}

void off_digit(signed char digit)
{
  switch (digit)
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
  case 8:
    DIGIT_8 = 0;
    break;
  case 9:
    DIGIT_9 = 0;
    break;
  default:
    break;
  }
}
// /**
//  End of File
// */