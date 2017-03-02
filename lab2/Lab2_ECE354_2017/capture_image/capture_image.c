#include "address_map_arm.h"
#include <time.h>
//#include "env.h"
#define _POSIX_SOURCE
#define KEY_BASE              0xFF200050
#define VIDEO_IN_BASE         0xFF203060
#define FPGA_ONCHIP_BASE      0xC8000000

/* This program demonstrates the use of the D5M camera with the DE1-SoC Board
 * It performs the following: 
 * 	1. Capture one frame of video when any key is pressed.
 * 	2. Display the captured frame when any key is pressed.		  
*/
/* Note: Set the switches SW1 and SW2 to high and rest of the switches to low for correct exposure timing while compiling and the loading the program in the Altera Monitor program.
*/

void VGA_text (int, int, char *);//function prototype for text
void VGA_text(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *) FPGA_CHAR_START;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr+1))
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}
void VGA_text2 (int, int, char *);//function prototype for text
void VGA_text2(int x, int y, char * text_ptr)
{
	int offset;
  	volatile char * character_buffer = (char *) FPGA_CHAR_START;	// VGA character buffer

	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr))
	{
		*(character_buffer + offset) = *(text_ptr);	// write to the character buffer
		++text_ptr;
		++offset;
	}
}
int main(void)
{
	
	//tzname[0] = "EST5EDT";
	//tzset();
	volatile int * KEY_ptr				= (int *) KEY_BASE;
	volatile int * Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
	volatile short * Video_Mem_ptr	= (short *) FPGA_ONCHIP_BASE;
	int i = 0;
	int x, y;
	int c=0;
	//char count = 0x30;
while (1)
	{
	
	*(Video_In_DMA_ptr + 3)	= 0x4;				// Enable the video

	while (1)
	{
		//display color image, no modifications
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			*(Video_In_DMA_ptr + 3) = 0x0;			// Disable the video to capture one frame
			while (*KEY_ptr != 0);				// wait for pushbutton KEY release
			break;
		}
	}

	while (1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
	//flip over horizontal axis
	for (y = 0; y < 120; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			short temp3 = *(Video_Mem_ptr + ((239-y) << 9) + x);
			*(Video_Mem_ptr + (y << 9) + x) = temp3;
			*(Video_Mem_ptr + ((239-y) << 9) + x) = temp2;
		}
	}
	
	while(1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
	//increment count
	c++;
	char count[2];
	char* str = &count;
	sprintf(str, "%i", c);
	
	time_t ltime;
	ltime=time(NULL)-5*60*60;
	while(1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
	VGA_text (34, 29, asctime(localtime(&(ltime)))); //display timestamp
	VGA_text2 (0, 0, str); //display count;
	
		for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			//average RGB for greyscale
			short red = (temp2>>0x0B)&0x1F;
			short green = (temp2>>0x06)&0x1F; //remove leading 0
			short blue = temp2&0x1F;
			short average = (red+green+blue)/3;
			temp2 = (average)+(average<<0x06)+(average<<0x0b);
			*(Video_Mem_ptr + (y << 9) + x) = temp2;
		}
		}
		while(1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
		// flip over vertical axis
	
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 160; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			short temp3 = *(Video_Mem_ptr + (y << 9) + (319-x));
			*(Video_Mem_ptr + (y << 9) + x) = temp3;
			*(Video_Mem_ptr + (y << 9) + (319-x)) = temp2;
		}
	}
		while(1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
	
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			//average RGB for greyscale
			short red = ~((temp2>>0x0B)&0x1F);
			short green = ~((temp2>>0x06)&0x1F); //remove leading 0
			short blue = ~(temp2&0x1F);
			short average = (red+green+blue)/3;
			temp2 = (average)+(average<<0x06)+(average<<0x0b);
			*(Video_Mem_ptr + (y << 9) + x) = temp2;
		}
		}
	
	while(1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			while (*KEY_ptr != 0);	
			break;
		}
	}
	
	}
}
