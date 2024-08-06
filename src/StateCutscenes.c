#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Keys.h"
#include "Dialogos.h"
#include "Print.h"
#include "Misc2.h"

//importar mapas de cutscenes
IMPORT_MAP(intro_door);

//importar fuentes de cutscenes
IMPORT_TILES(font);

UINT8 cs_state = 0;
UINT8 current_cs = 0;

extern UINT8 current_dialog;
extern UINT8 dialog_pos;
extern UINT8 dialog;
extern UINT8 can_dialog;

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};




const struct MapInfoBanked cs_levels[] = {
	BANKED_MAP(intro_door),

};




const START_POS cs_start_positions[] = {
	{8, 96}, //TitleScreen	----- current level = 0 

};


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
        break;

        default:
        break;
    }

}

void UPDATE() {
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
