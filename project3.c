/*
 * project3.c
 *
 * Created: 5/6/2015 12:23:05 PM
 *  Author: Emily Puth and Chelsea Faustino
 */ 


#include <avr/io.h>
#include "avr.h"
#include "lcd.h"
#include "keypad.h"

// These values are round(((1/freq)/2)*0.00001)
// Increase precision by multiplying by 0.00001
// Also changed wait_avr to increase precision

#define A	114
#define AS	107
#define B	101
#define C	96
#define CS	90
#define D	85
#define DS	80
#define E	76
#define F	72
#define FS	68
#define G	64
#define GS	60
#define A2	57

// Durations
#define whole	8
#define half	4
#define quarter 2
#define eighth	1

typedef struct Note {
	unsigned long delay;
	unsigned char duration;
} note;

void play_note(unsigned char duration, unsigned long delay) {
	SET_BIT(DDRA, 0);
	int n = (2 * duration) / (2 * delay * 0.0001);
	for(int i=0; i < n; ++i) {
		SET_BIT(PORTA, 0);
		wait_avr(delay); // set time
		CLR_BIT(PORTA, 0);
		wait_avr(delay); // set time
	}
}

void play_song(note *song, int len) {
	int i;
	for (i=0; i < len; ++i) {	
		play_note(song[i].duration, song[i].delay);
		wait_avr(100);
	}
}

int main(void)
{	
	ini_lcd();
	clr_lcd();
	note FurElise[9] = {
		{E, eighth}, 
		{DS,eighth},
		{E, eighth}, 
		{DS,eighth},
		{E, eighth},
		{B, eighth}, 
		{D, eighth},
		{C, eighth},
		{A, quarter}
	};
	
	note Twinkle[14] = {
		{C, quarter},
		{C, quarter},
		{G, quarter},
		{G, quarter},
		{A2, quarter},
		{A2, quarter},
		{G, half},
		{F, quarter},
		{F, quarter},
		{E, quarter},
		{E, quarter},
		{D, quarter},
		{D, quarter},	
		{C, half}
	};
	while(1) {
		pos_lcd(0,0);
		puts_lcd2("Song:");
		if (get_key() == 1) {
			pos_lcd(1,0);
			puts_lcd2("Fur Elise");
			play_song(FurElise, 9);
			clr_lcd();
		}
		else if (get_key() == 2) {
			pos_lcd(1,0);
			puts_lcd2("Twinkle Twinkle");
			play_song(Twinkle, 14);
			clr_lcd();
		}
	}
	
	
}