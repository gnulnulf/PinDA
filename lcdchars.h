/*
    Title: 7/14/16 lcd/led segment character definitions

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
*/
/**
	@defgroup lcd_chars LCD Chars
	@code #include <lcdchars.h> @endcode	
	@brief 7/14/16 lcd/led segment character definitions
	
	@author Arco van Geest
*/
/*@{*/
#ifndef LCDCHARS_INCLUDE
#define LCDCHARS_INCLUDE


// define which character segs are needed
/** 
 *  @name  Include 7 segment definitions
 *  Wheter or not the 7 segment display code should be included.
 */
#define LCDCHARS_ENABLE_SEG7 1	 /**< 0 or 1, to include the code */

/** 
 *  @name  Include 14 segment definitions
 *  Wheter or not the 14 segment display code should be included.
 */
#define LCDCHARS_ENABLE_SEG14 1 /**< 0 or 1, to include the code */
/** 
 *  @name  Include 16 segment definitions
 *  Wheter or not the 16 segment display code should be included.
 */
#define LCDCHARS_ENABLE_SEG16 0 /**< 0 or 1, to include the code */

#include <stdint.h>
#include <avr/pgmspace.h>


#if LCDCHARS_ENABLE_SEG7 ==1
/** 
*	@name Font 7-Segment LCD/LED
* <pre>
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
</pre>
* Font and character definition based on MAX8650 datasheet
* 
*/

/**
 @brief    Get 8bit character data
 @param    index hex value
 @return  byte containing display data 0b0Pgfedcda
*/
uint8_t lcd7Char( uint8_t index);

#endif //LCDCHARS_ENABLE_SEG7

#if LCDCHARS_ENABLE_SEG14 ==1
/** 
*	@name Font 14-Segment LCD/LED
* <pre>
*     -----a-----
*    | \   |   / |
*    f  h  i  j  b
*    |   \ | /   |
*     -g1-- --g2-
*    |   / | \   |
*    e  m  l  k  c
*    | /   |   \ |
*     -----d-----
*                  *P
*                  ,K	  
* </pre>
* Font and character definition based on MAX8650 datasheet
*
*/

/**
 @brief    Get 16bit character data
 @param    character ascii value
 @return  word containing display data 0bKPmlkjih(g2)(g1)fedcda
*/
uint16_t lcd14Char( uint8_t character);
#endif //LCDCHARS_ENABLE_SEG14

#if LCDCHARS_ENABLE_SEG16 ==1
/** 
* @name Font 16-Segment LCD/LED
* \b NOT YET IMPLEMENTED!
* <pre>
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
* </pre>
* Font and character definition based on MAX8650 datasheet
*
*/
/**
 @brief    Get 32bit character data
 @param    character ( ascii value )
 @return  uint32 containing display data 0b0Pmlkjih(g2)(g1)fe(d2)(d1)cb(a2)(a1)
*/
uint32_t lcd16Char( uint8_t character);

	#error "Not yet implemented"
#endif //LCDCHARS_ENABLE_SEG16


#endif //LCDCHARS_INCLUDE
/*@}*/