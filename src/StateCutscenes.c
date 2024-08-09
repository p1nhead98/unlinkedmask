#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Keys.h"
#include "Dialogos.h"
#include "Print.h"
#include "Misc2.h"
#include "WinController.h"


//importar mapas de cutscenes
IMPORT_MAP(intro_door);
IMPORT_MAP(doorCuts);
IMPORT_MAP(cinematicCape);



//importar fuentes de cutscenes
IMPORT_TILES(font);

UINT8 cs_counter = 0;
UINT8 cs_counter_2 = 0;
UINT8 current_cs = 0;


extern UINT8 current_dialog;
extern UINT8 dialog_pos;
extern UINT8 dialog;
extern UINT8 can_dialog;
extern UINT8 state_interrupts;

extern UINT8 canDoInterrupt;
extern UINT8 counterInterrupt;
extern UINT8 counterInterrupt2;
extern UINT8 can_scroll_x ;
extern UINT8 can_scroll_y ;

extern UINT16 scroller_y;

const struct MapInfoBanked cs_levels[] = {
	BANKED_MAP(intro_door),
	BANKED_MAP(doorCuts),
	BANKED_MAP(cinematicCape),
};

const START_POS cs_start_positions[] = {
	{8, 96}, 
	{64, 87}, 
	{0, 96}, 
};

void FillDoorCinemCs() {
    for (UINT8 y = 0u; y < 12u; y++)
	{
		for (UINT8 x = 0u; x < 20u; x++)
		{
				ScrollUpdateColumn(x, y);
		}
			
	}
}


void START() {
    const struct MapInfoBanked* level = &cs_levels[current_cs]; 
	// scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	

    //Se definen paletas para DMG
    BGP_REG = PAL_DEF(0, 1, 2, 3);
    OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);
    
    

    InitScroll(level->bank, level->map, 0, 0);
    
    switch(current_cs){
        case 0:
            SHOW_SPRITES;
            SpriteManagerAdd(SpritePlayerCutscenes, cs_start_positions[current_cs].start_x, cs_start_positions[current_cs].start_y);
            INIT_FONT(font, PRINT_WIN);
			dialog = 0;
			can_dialog = 0;
			current_dialog = 0;
		break;

		case 1:
			FillDoorCinemCs();
			SHOW_SPRITES;
			can_scroll_y = 0;
			SpriteManagerAdd(SpriteViewerH, cs_start_positions[current_cs].start_x, cs_start_positions[current_cs].start_y);
			INIT_FONT(font, PRINT_WIN);
			dialog = 0;
			can_dialog = 0;
			current_dialog = 5;
			state_interrupts = 2;
			scroll_y = 0;
			cs_counter = 3;
			cs_counter_2 = 90;
			counterInterrupt = counterInterrupt2 = 3;
			LYC_REG = 0;
		break;

		case 2:
			SHOW_SPRITES;
			can_scroll_y = 0;
			can_scroll_x = 0;
			SetHudWin(0);
			SpriteManagerAdd(SpritePlayerCutscenes, cs_start_positions[current_cs].start_x, cs_start_positions[current_cs].start_y);
			INIT_FONT(font, PRINT_WIN);
			dialog = 0;
			can_dialog = 0;
			current_dialog = 0;
			break;


        default:
        break;
    }

}

void UPDATE() {

	if(current_cs == 1){
		if(canDoInterrupt == 0){
			if(--cs_counter == 0){
				canDoInterrupt = 1;
			}
		}else if(canDoInterrupt == 2){
			if(--cs_counter_2 == 0){
				canDoInterrupt = 3;
				LYC_REG = 0;
				dialog_pos = 20;
				WY_REG = dialog_pos;
				state_interrupts = 1;
				dialog = 1;
			}
		}

	}


    if(dialog == 1){
		if(can_dialog == 0){
			SetDialog();
			can_dialog = 1;
		}
		if(KEY_TICKED(J_A) && can_dialog == 1){
			current_dialog++;
			// PlayFx(CHANNEL_1, 15, 0x3a, 0x9a, 0x91, 0xe0, 0x86);
			can_dialog = 0;
		}
	}
	
}
