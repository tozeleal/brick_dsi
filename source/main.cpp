#include <nds.h>

#include <stdio.h>

// git adds a nice header we can include to access the data
// this has the same name as the image
#include "logo.h"

int main(void)
{
	
    // set the mode for 2 text layers and two extended background layers
	videoSetMode(MODE_3_2D);
	
    vramSetBankA(VRAM_A_MAIN_BG_0x06000000);	
	
	int konami=0;

	PrintConsole bottomScreen;
	
	

	int bg3 = bgInit(3, BgType_Bmp8, BgSize_B8_256x256, 0,0);
	dmaCopy(logoBitmap, bgGetGfxPtr(bg3), 256*256);
	dmaCopy(logoPal, BG_PALETTE, 256*2);
	consoleInit(&bottomScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
	consoleSelect(&bottomScreen);

	
	while(1) {
		//Konami Code EasterEgg
		scanKeys();
		if(keysDown()&KEY_UP && konami<2){
			konami++;
		}
		if(keysDown()&KEY_DOWN && konami>=2 && konami <4){
			konami++;
		}
		if((keysDown()&KEY_LEFT && konami==4) || (keysDown()&KEY_LEFT && konami==6)){
			konami++;
		}
		if((keysDown()&KEY_RIGHT && konami==5) ||(keysDown()&KEY_RIGHT && konami==7)){
			konami++;
		}
		if(keysDown()&KEY_B && konami==8){
			konami++;
		}
		if(keysDown()&KEY_A && konami==9){
			konami++;
		}
		if(keysDown()&KEY_START && konami==10){
			konami++;
			
		}
		if(konami>10){
			konami--;
			videoSetModeSub(MODE_0_2D);
			vramSetBankC(VRAM_C_SUB_BG);
			consoleInit(&bottomScreen, 3,BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);
			consoleSelect(&bottomScreen);
			consoleClear();
			printf("\x1b[2J");
			
			printf("\x1b[43mCongrats!\x1b[55m\nYou unlocked the secret area!");
			printf("\n\n\n\n");
			printf("Simply replace boot.nds on the \nroot of your SD card to achieve\nnormal functions");
			printf("\n\n\n\n");
			printf("Special thanks for Senpai for\nthe request");
			printf("\n\n\n\n");
			printf("To power off press the following keys:L, R, Start, Select");
			printf("\n\nMade by:\nTozeleal\n\n\n");
			printf("\x1b[44mFollow me on Twitter!\x1b[34m @tozeleal");
		}
		
		//iprintf("\x1b[10;0HKonami var = %d",konami); DEBUG konami code value
		
		//Shutdown KeyCombination
		//Pressing keys: Start, Up, L, R, Y, X, A
		if (keysDown()&KEY_START &&
			keysDown()&KEY_UP &&
			keysDown()&KEY_L &&
			keysDown()&KEY_R &&
			keysDown()&KEY_Y &&
			keysDown()&KEY_X &&
			keysDown()&KEY_A
			)break;
	}
	

	
	
	return 0;
	
}
