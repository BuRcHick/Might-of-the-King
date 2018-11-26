#ifndef GRAPHICENGINE_HPP
#define GRAPHICENGINE_HPP

#include<Windows.h>

//-----Map-param-----------------------------------------------------------

#define MAP_W 3091
#define MAP_H 2040
#define STEP 20

//------Village-param----------------------------------------------------------

#define VILLAGE_H 112
#define VILLAGE_W 170
#define VILLAGES_COUNT 12
#define VILLAGES_CADS 6

//------Camp-param----------------------------------------------------------

#define CAMP_H 250
#define CAMP_W 300
#define CAMPS_COUNT 9
#define CAMPSS_CADS 6

//------Cave-param----------------------------------------------------------

#define CAVE_H 110
#define CAVE_W 188
#define CAVES_COUNT 5
#define CAVES_CADS 11

//------Tomb-param----------------------------------------------------------

#define TOMB_H 270
#define TOMB_W 255
#define TOMBS_COUNT 5
#define TOMBS_CADS 11

//------Castle-param----------------------------------------------------------

#define CASTLE_H 250
#define CASTLE_W 285
#define CASTLES_COUNT 4
#define CASTLE_1_CADS 15
#define CASTLE_2_CADS 15
#define CASTLE_3_CADS 20
#define CASTLE_4_CADS 7

//--------Timers-Params------------------------------------------------------------------------------------------------

#define TIMER_REDRAW 1
#define TIMER_ANIMATION 2
#define TIMER_TOMB 3
#define TIMER_CAVE 4
#define TIMER_CASTLE_1 5 
#define TIMER_CASTLE_2 6
#define TIMER_CASTLE_3 7 
#define TIMER_CASTLE_4 8

#define TIMREDRSPEED 17
#define TIMANIMSPEED 100
#define TIMETOMBSPEED 5000
#define TIMECAVESPEED 2000
#define TIMECS1_SPEED 10000
#define TIMECS2_SPEED 20000
#define TIMECS3_SPEED 200
#define TIMECS4_SPEED 130

//--------Grid-param------------------------------------------------------------------------------------------------
#define BLOCK_H 100
#define BLOCK_W 100
#define BLOCKS_W_COUNT 12
#define BLOCKS_H_COUNT 7


//--------Features------------------------------------------------------------------------------------------------

void DrawBitmap(HDC, HBITMAP, int, int);
void DrawTransperentBitmap(HDC, HBITMAP, short, short, COLORREF);
void Play_Sound();

#endif // !GRAPHICENGINE_HPP

