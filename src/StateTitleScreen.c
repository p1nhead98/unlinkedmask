#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Music.h"
#include "SGB.h"
#include "Palette.h"
#include "Keys.h"
#include "Misc2.h"
#include "Misc.h"
#include "WinController.h"


IMPORT_MAP(titleScreen);
IMPORT_MAP(linkedborder);
DECLARE_MUSIC(unlinkedtitlescreen);

UINT8 ts_counter = 0;
UINT8 ts_counter2 = 0;
UINT8 ts_anim = 0;
UINT8 ts_anim2 = 0;
UINT8 ts_state = 0;


extern UINT8 current_cs;

void TitleScreenAnimation(UINT8 index){
    const UINT8 BORDER_L_1  = 0;
    const UINT8 BORDER_L_2  = 1;
    const UINT8 BORDER_L_3  = 66;
    const UINT8 BORDER_L_4  = 67;
    const UINT8 BORDER_L_5  = 68;
    const UINT8 BORDER_L_6  = 69;
    const UINT8 BORDER_L_7  = 70;
    const UINT8 BORDER_L_8  = 71;
    const UINT8 BORDER_L_9  = 72;
    const UINT8 BORDER_R_1  = 3;
    const UINT8 BORDER_R_2  = 0;
    const UINT8 BORDER_R_3  = 74;
    const UINT8 BORDER_R_4  = 73;
    const UINT8 BORDER_R_5  = 76;
    const UINT8 BORDER_R_6  = 75;
    const UINT8 BORDER_R_7  = 77;
    const UINT8 BORDER_R_8  = 78;
    const UINT8 BORDER_R_9  = 79;
    
    const UINT8 BORDER_BLACK  = 2;

    const UINT8 LETSGO[] = {56, 57, 58, 59, 60, 61, 62, 63, 64};
    const UINT8 EXCLAMATION_1 = 55; 
    const UINT8 EXCLAMATION_2 = 65;

    switch(index){
        case 0:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_1);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_2);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_1);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_2);
            }
        break;
        case 1:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_3);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_4);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_3);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_4);
            }
        break;
        case 2:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_5);
                set_bkg_tiles(1, i, 1, 1, &BORDER_L_6);
                set_bkg_tiles(18, i, 1, 1, &BORDER_R_5);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_6);
            }
        break;
        case 3:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_7);
                set_bkg_tiles(1, i, 1, 1, &BORDER_BLACK);
                set_bkg_tiles(18, i, 1, 1, &BORDER_BLACK);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_7);
            }
        break;
        case 4:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_8);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_8);
            }
        break;
        case 5:
            for(UINT8 i = 0; i < 18 ; i++){
                set_bkg_tiles(0, i, 1, 1, &BORDER_L_9);
                set_bkg_tiles(19, i, 1, 1, &BORDER_R_9);
            }
        break;
        case 7:
            for(UINT8 i = 6; i < 15 ; i++){
                set_bkg_tiles(i, 12, 1, 1, &BORDER_BLACK);
            }
            set_bkg_tiles(14, 11, 1, 1, &BORDER_BLACK);
            set_bkg_tiles(13, 13, 1, 1, &BORDER_BLACK);
            break;
        case 8:
            for(UINT8 i = 6; i < 15 ; i++){
                set_bkg_tiles(i, 12, 1, 1, &LETSGO[i - 6]);
            }
            set_bkg_tiles(14, 11, 1, 1, &EXCLAMATION_1);
            set_bkg_tiles(13, 13, 1, 1, &EXCLAMATION_2);
        break;
    }
}

void FadeDMGTitleScreen(UINT8 fadeout) {
	
	UINT8 pals3[] = {0, 1, 2, 3};
    UINT8 pals2[] = {0, 0, 1, 2};
    UINT8 pals1[] = {0, 0, 0, 0};
	UINT8 pals0[] = {0, 0, 0, 1};

    BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(pals0[fadeout], pals1[fadeout], pals2[fadeout], pals3[fadeout] );
		
}

void FadeAllTitleScreen(){
    FadeDMGTitleScreen(3);
    pDelay(20);
    NR50_REG = 0x55;
    FadeDMGTitleScreen(2);
    pDelay(20);
    NR50_REG = 0x33;
    FadeDMGTitleScreen(1);
    pDelay(20);
    NR50_REG = 0x11;
    FadeDMGTitleScreen(0);
    pDelay(20);
    NR50_REG = 0x0;
    StopMusic;
    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
}

void START() {
    //Se carga borde de Super Game Boy
    CRITICAL {
	    LOAD_SGB_BORDER(linkedborder);
    }
    //Se define Tempos para cancion segun sistema
    CRITICAL {
#ifdef CGB
	if (_cpu == CGB_TYPE) {
		TMA_REG = 55u;
	}else{
		TMA_REG = 154u;
	}
#else
	TMA_REG = 154u;

#endif
	}
    
    //Se definen paletas para DMG
    BGP_REG = PAL_DEF(1, 0, 2, 3);
    OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);

    //Inicia la musica
    PlayMusic(unlinkedtitlescreen, 1);
	
    //Se carga mapa
	InitScroll(BANK(titleScreen), &titleScreen, 0, 0);
    SetHudWin(0);
    //Se da valor a variables
    current_cs = ts_state = ts_anim = ts_anim2 = 0;
    ts_counter = ts_counter2 = 3;
    
}

void UPDATE() {

    if(ts_state == 0){
        if(--ts_counter == 0){
            ts_counter = 10;
            TitleScreenAnimation(ts_anim);
            if(ts_anim < 6){
                ts_anim++;
            }else{
                ts_anim = 0;
                SpriteManagerAdd(SpriteTitleFlash, 16, 32);
            }
        }

        if(--ts_counter2 == 0){
            ts_counter2 = 20;
            ts_anim2 = ts_anim2 == 8 ? 7 : 8;
            TitleScreenAnimation(ts_anim2);
        }
        if(KEY_TICKED(J_START)){
            // start_fade = 1;
            ts_state++;
            ts_counter2 = 3;
            ts_counter = 50;
            // current_level++;
            //SetState(current_state);
        }
    }else{
        if(--ts_counter2 == 0){
            ts_counter2 = 5;
            ts_anim2 = ts_anim2 == 8 ? 7 : 8;
            TitleScreenAnimation(ts_anim2);
        }
        if(--ts_counter == 0){
            TitleScreenAnimation(8);
            FadeAllTitleScreen();
            current_state = StateCutscenes;
            SetState(current_state);
        }
    }

    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
}
