/*
	lcdchars.c

    Copyright (C) 2011  Arco van Geest
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	USAGE
       See the C include lcdchars.h file for a description of each function
*/
#ifndef LCDCHARS_C
#define LCDCHARS_C 1


#include <stdint.h>
#include <avr/pgmspace.h>
#include "lcdchars.h"


#if LCDCHARS_ENABLE_SEG7 ==1
/** 
*	Font 7-Segment LCD/LED
*
*     -----a-----
*    |           |
*    f           b
*    |           |
*     -----g-----
*    |           |
*    e           c
*    |           |
*     -----d-----
*                  *P	  
* Font and character definition based on MAX8650 datasheet
* 
*/

/* 7 segment font */
const int8_t lcdFont7[] PROGMEM =
{
//    Pgfedcba

	0b00000000, 	// <Blank> code32
	0b00000000, 	// !
	0b00100010, 	// "
	0b00000000, 	// #
	0b00000000, 	// $
	0b00000000, 	// %
	0b00000000, 	// &
	0b00000000, 	// '
	0b00000000, 	// (
	0b00000000, 	// )
	0b00000000, 	// *
	0b00000000, 	// +
	0b00000000, 	// ,
	0b01000000,     //-
	0b10000000,     //.
	0b00000000, 	// /
	
	// met comma
	0b10111111, 	//0
	0b10000110, 	//1
	0b11011011, 	//2
	0b11001111, 	//3
	0b11100110, 	//4
	0b11101101, 	//5
	0b11111101, 	//6
	0b10000111, 	//7
	0b11111111, 	//8
	0b11101111, 	//9

	
	0b00000100, 	// :
	0b00010100, 	// ;
	0b00100100, 	// <
	0b00001000, 	// =
	0b00000001, 	// >
	0b00101000, 	// ?
	0b00001010, 	// @

	0b01110111, 	//A
	0b01111100, 	//B
	0b00111001, 	//C
	0b01011110, 	//D
	0b01111001, 	//E
	0b01110001,		//F
	0b00111101, 	// G
	0b01110110, 	// H
	0b00000100, 	// I
	0b00011110, 	// J
	0b00110100, 	// K
	0b00111000, 	// L
	0b00110111, 	// M
	0b01010100, 	// N

	0b01011100, 	// O
	0b01110011, 	// P
	0b01100111, 	// Q
	0b01010000, 	// R
	0b01101101, 	// S
	0b01111000, 	// T
	0b00011100, 	// U
	0b00111000, 	// V
	0b00111110, 	// W
	0b01110110, 	// X
	0b01110010, 	// Y
	0b01011011, 	// Z


	


	
};

const int8_t lcdFont7org[] PROGMEM =
{
//    Pgfedcba
	0b00111111, 	//0
	0b00000110, 	//1
	0b01011011, 	//2
	0b01001111, 	//3
	0b01100110, 	//4
	0b01101101, 	//5
	0b01111101, 	//6
	0b00000111, 	//7
	0b01111111, 	//8
	0b01101111, 	//9
	0b01110111, 	//A
	0b01111100, 	//B
	0b00111001, 	//C
	0b01011110, 	//D
	0b01111001, 	//E
	0b01110001,		//F
	0b01000000,     //-
	0b10000000,     //.
	
};

/*
 @brief    Get 8bit character data
 @param    index hex value
 @return  byte containing display data 0b0Pgfedcda
*/
uint8_t lcd7Char( uint8_t karakter) {
	// table start at 0 
	
	if (karakter<32) karakter=32;
	//map lowercase to uppercase
	if (karakter >= 'a' && karakter<='z' ) karakter-=32;
	// unknown characters become space
	if (karakter>'Z') karakter=32;
	karakter-=32;	//tabel begint bij 32
	// return the lcd data in max8650 14 segement order abcdefg1g2hijklmP
	return (uint8_t)pgm_read_byte(&lcdFont7[ karakter ]);
} //lcd7Char
#endif //LCDCHARS_ENABLE_SEG7


#if LCDCHARS_ENABLE_SEG14 ==1
/* Font 14-Segment LCD/LED
* 
*     -----a-----
*    | \   |   / |
*    f  h  i  j  b
*    |   \ | /   |
*     -g1-- --g2-   g1=g g2=G
*    |   / | \   |
*    e  m  l  k  c
*    | /   |   \ |
*     -----d-----
*                  *P
*	               ,K 
* Font and character definition based on MAX8650 datasheet
*
*/
/* 14 segment font */
const int16_t lcdFont14[159] PROGMEM =
{
//    KPmlkjihGgfedcba
//    PmlkGjihKgfedcba

	0b0000000000000000, 	// <Blank> code32
	0b0010001000000000, 	// !
	0b0000000000100010, 	// "
	0b0000000000000000, 	// #
	0b0000000000000000, 	// $
	0b0000000000000000, 	// %
	0b0000000000000000, 	// &
	0b0000000000000000, 	// '
	0b0000000000000000, 	// (
	0b0000000000000000, 	// )
	0b0000000000000000, 	// *
	0b0000000000000000, 	// +
	0b0000000000000000, 	// ,
	0b0000000000000000, 	// -
	0b0100000000000000, 	// .
	0b0000000000000000, 	// /

//    KPmlkjihGgfedcba
//    PmlkGjihKgfedcba


	0b0100010000111111, 	// 0
	0b0000000000000110, 	// 1
	0b0000100001011011, 	// 2
	0b0000100000001111, 	// 3
	0b0000100001100110, 	// 4
	0b0000100001101101, 	// 5
	0b0000100001111101, 	// 6
	0b0000000000000111, 	// 7
	0b0000100001111111, 	// 8
	0b0000100001101111, 	// 9
	0b0000010000000000, 	// :
	0b0001010000000000, 	// ;
	0b0010010000000000, 	// <
	0b0000100001001000, 	// =
	0b0000000100000000, 	// >
	0b0010100000000011, 	// ?
	0b0000101000111011, 	// @

	0b0000100001110111, 	// A
	0b0010101000001111, 	// B
	0b0000000000111001, 	// C
	0b0010001000001111, 	// D
	0b0000000001111001, 	// E
	0b0000000001110001, 	// F
	0b0000100000111101, 	// G
	0b0000100001110110, 	// H
	0b0010001000001001, 	// I
	0b0000000000011110, 	// J
	0b0001010001110000, 	// K
	0b0000000000111000, 	// L
	0b0000001000110111, 	// M
	0b0001000100110110, 	// N

	0b0000000000111111, 	// O
	0b0000100001110011, 	// P
	0b0001000000111111, 	// Q
	0b0001100001110011, 	// R
	0b0000100001101101, 	// S
	0b0010001000000001, 	// T
	0b0000000000111110, 	// U
	0b0100010000110000, 	// V
	0b0101000000110110, 	// W
	0b0101010100000000, 	// X
	0b0010010100000000, 	// Y
	0b0100010000001001, 	// Z
};
const int16_t lcdFont14wms[59] PROGMEM =
{
//    KPmlkjihGgfedcba
	0b0000000000000000, 	// <Blank> code32
	0b0001010000000000, 	// !
	0b0000000000000000, 	// "
	0b0000000000000000, 	// #
	0b0000000000000000, 	// $
	0b0000000000000000, 	// %
	0b0000000000000000, 	// &
	0b0000000000000000, 	// '
	0b0000000000000000, 	// (
	0b0000000000000000, 	// )
	0b0000000000000000, 	// *
	0b0000000000000000, 	// +
	0b0000000000000000, 	// ,
	0b0000000000000000, 	// -
	0b0100000000000000, 	// .
	0b0000000000000000, 	// /
	0b0000110000111111, 	// 0
	0b0000000000000110, 	// 1
	0b0000000011011011, 	// 2
	0b0000000010001111, 	// 3
	0b0000000011100110, 	// 4
	0b0010000001101001, 	// 5
	0b0000000011111101, 	// 6
	0b0000000000000111, 	// 7
	0b0000000011111111, 	// 8
	0b0000000011101111, 	// 9
	0b0000110000000000, 	// :
	0b0001010000000000, 	// ;
	0b0010010000000000, 	// <
	0b0000000011001000, 	// =
	0b0000100100000000, 	// >
	0b0001000010000011, 	// ?
	0b0000001010111011, 	// @
	0b0000000011110111, 	// A
	0b0001001010001111, 	// B
	0b0000000000111001, 	// C
	0b0001001000001111, 	// D
	0b0000000001111001, 	// E
	0b0000000001110001, 	// F
	0b0000000010111101, 	// G
	0b0000000011110110, 	// H
	0b0001001000001001, 	// I
	0b0000000000001110, 	// J
	0b0010010001110000, 	// K
	0b0000000000111000, 	// L
	0b0000001000110111, 	// M
	0b0010000100110110, 	// N
	0b0000000000111111, 	// O
	0b0000000001110011, 	// P
	0b0010000000111111, 	// Q
	0b0010000001110011, 	// R
	0b0000000001101101, 	// S
	0b0001001000000001, 	// T
	0b0000000000111110, 	// U
	0b0000110000100000, 	// V
	0b0010100000110110, 	// W
	0b0010110100000000, 	// X
	0b0001010100000000, 	// Y
	0b0000110000001001, 	// Z
};

/*
 @brief    Get 16bit character data
 @param    character ( ascii value )
 @return  word containing display data 0b0Pmlkjih(g2)(g1)fedcda
*/
uint16_t lcd14Char( uint8_t karakter) {
	// table start at space (32)
	if (karakter<32) karakter=32;
	//map lowercase to uppercase
	if (karakter >= 'a' && karakter<='z' ) karakter-=32;
	// unknown characters become space
	if (karakter>'Z') karakter=32;
	karakter-=32;	//tabel begint bij 32
	// return the lcd data in max8650 14 segement order abcdefg1g2hijklmP
	return (uint16_t)pgm_read_word(&lcdFont14[ karakter ]);
} //lcd14Char
#endif //LCDCHARS_ENABLE_SEG16

#if LCDCHARS_ENABLE_SEG16 ==1
/* Font 16-Segment LCD/LED
* 
*     --a1- --a2-
*    | \   |   / |
*    f  h  i  j  b
*    |   \ | /   |
*     -g1-- --g2-
*    |   / | \   |
*    e  m  l  k  c
*    | /   |   \ |
*     --d1- --d2-
*                  *P	  
* Font and character definition based on MAX8650 datasheet
*
*/

	#error "Not yet implemented"
#endif

#endif