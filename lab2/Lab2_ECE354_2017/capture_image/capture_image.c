#include "address_map_arm.h"
#include <time.h>
#define KEY_BASE              0xFF200050
#define VIDEO_IN_BASE         0xFF203060
#define FPGA_ONCHIP_BASE      0xC8000000
#define SDRAM_START2          0xC8300000
volatile int * KEY_ptr				= (int *) KEY_BASE;
volatile int * Video_In_DMA_ptr	= (int *) VIDEO_IN_BASE;
volatile short * Video_Mem_ptr	= (short *) FPGA_ONCHIP_BASE;
volatile int *SW_switch_ptr = (int*) SW_BASE;
volatile short * storage_ptr = (short *) SDRAM_START;
volatile short * storage_ptr2 = (short *) SDRAM_START2;
int c=0;
int bool=0;
int x, y;
//function prototypes
void flipH(void);
void flipV(void);
void VGA_text2 (int, int, char *);
void VGA_text (int, int, char *);
void greyscale(void);
void capture(void);
void diff(void);
void diff(void){
	for (y = 0; y < 240; y++) {
		for (x = 0; x < 320; x++) {
			short temp1 = *(storage_ptr+ (y << 9) + x);
			short temp2 = *(Video_Mem_ptr + (y << 9) + x);
			//separate colors for each image
			short red = (temp2>>0x0B)&0x1F;
			short green = (temp2>>0x06)&0x1F; //remove LSB 
			short blue = temp2&0x1F;
			short red2 = (temp1>>0x0B)&0x1F;
			short green2 = (temp1>>0x06)&0x1F; //remove LSB
			short blue2 = temp1&0x1F;
			//if R,G,B difference above threshold, replace with corresponding colors
			if((abs(red-red2)>2)|(abs(green-green2)>2)|(abs(blue-blue2)>2)){
			*(Video_Mem_ptr + (y << 9) + x)=(0x1F>>11) + ((blue-blue2)<<6) + (red-red2);
		}
		}
		}
}
void capture(void){
	*(Video_In_DMA_ptr + 3)	= 0x4;
					while (1)
					{
						if (*KEY_ptr != 0)						// check if any KEY was pressed
						{
							*(Video_In_DMA_ptr + 3) = 0x0;			// Disable the video to capture one frame
							while (*KEY_ptr != 0);				// wait for pushbutton KEY release
							break;
						}
					}
}
void greyscale(void){
	for (y = 0; y < 240; y++) {
				for (x = 0; x < 320; x++) {
					short temp2 = *(storage_ptr + (y << 9) + x);
					//average RGB for greyscale
					short red = (temp2>>0x0B)&0x1F;
					short green = (temp2>>0x06)&0x1F; //remove LSB
					short blue = temp2&0x1F;
					short average = (red+green+blue)/3;
					temp2 = (average)+(average<<0x06)+(average<<0x0b);
					*(Video_Mem_ptr + (y << 9) + x) = temp2;
				}
			}
}
void invert(void){
	for (y = 0; y < 240; y++) {
				for (x = 0; x < 320; x++) {
					short temp2 = *(storage_ptr + (y << 9) + x);
					//isolate RGB and invert
					short red = ~((temp2>>0x0B)&0x1F)+0x01;
					short green = ~((temp2>>0x06)&0x1F)+0x01; //remove LSB
					short blue = ~(temp2&0x1F)+0x01;
					short average = (red+green+blue)/3;
					temp2 = (average)+(average<<0x06)+(average<<0x0b);
					*(Video_Mem_ptr + (y << 9) + x) = temp2;
				}
			}
}
void flipH(void){
	for (y = 0; y < 120; y++) {
				for (x = 0; x < 320; x++) {
					short temp2 = *(storage_ptr + (y << 9) + x);
					short temp3 = *(storage_ptr + ((239-y) << 9) + x);
					*(storage_ptr + (y << 9) + x) = temp3;
					*(Video_Mem_ptr + ((239-y) << 9) + x) = temp2;
				}
			}
}
void flipV(void){
	for (y = 0; y < 240; y++) {
				for (x = 0; x < 160; x++) {
					short temp2 = *(Video_Mem_ptr + (y << 9) + x);
					short temp3 = *(Video_Mem_ptr + (y << 9) + (319-x));
					*(Video_Mem_ptr + (y << 9) + x) = temp3;
					*(Video_Mem_ptr + (y << 9) + (319-x)) = temp2;
				}
			}
}
/* This program demonstrates the use of the D5M camera with the DE1-SoC Board
 * It performs the following: 
 * 	1. Capture one frame of video when any key is pressed.
 * 	2. Display the captured frame when any key is pressed.		  
*/
/* Note: Set the switches SW1 and SW2 to high and rest of the switches to low for correct exposure timing while compiling and the loading the program in the Altera Monitor program.
*/

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
int main(void)
{
	
	*(Video_In_DMA_ptr + 3)	= 0x4;				// Enable the video
while(1){
	
	while (1)
	{
		if (*KEY_ptr != 0)						// check if any KEY was pressed
		{
			*(Video_In_DMA_ptr + 3) = 0x0;			// Disable the video to capture one frame
			while (*KEY_ptr != 0);				// wait for pushbutton KEY release
			break;
		}
	}
	
	//store original image in SDRAM
	for (y = 0; y < 240; y++) {
					for (x = 0; x < 320; x++) {
					*(storage_ptr + (y << 9) + x) = *(Video_Mem_ptr + (y << 9) + x);
						}
					}
					
	if(bool == 0){
		c++; //increment counter for image capture
		bool = 1;
	}
	char count[2];
	char* str = &count;
	sprintf(str, "%i", c); //format count into string array for displaying
	VGA_text2(0,0,str); //display count
	
	time_t ltime;
	int SW_value=*(SW_switch_ptr);
	
	switch(SW_value){
		case 1: // turn greyscale
		greyscale();
		break;
		case 2: // turn greyscale then invert
		greyscale();
		invert();
		break;
		case 4: //flip over horizontal axis
		flipH();
		break;
		case 8: //flip over Vertical Axis
		flipV();
		break;
		case 16: //print timestamp to monitor
		ltime=time(NULL)-5*60*60;
		VGA_text (0, 5, asctime(localtime(&(ltime))));
		break;
		case 32: //bonus
		capture();
		diff();	
		break;
		case 64:
		break;
		case 512: //RESET
		VGA_text(0,0,str); //display count
		*(Video_In_DMA_ptr + 3)	= 0x4;	
		bool = 0;
		default:
		break;
	}
		
}

}
