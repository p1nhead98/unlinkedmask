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
#include "Cinematicas.h"
#include "Math.h"
#include "Sgb.h"
#include "CustomFade.h"

//importar mapas de cutscenes
IMPORT_MAP(intro_door);
IMPORT_MAP(doorCuts);
IMPORT_MAP(cinematicCape);
IMPORT_MAP(capeCuts1);
IMPORT_MAP(capeCuts2);
IMPORT_MAP(capeCuts7);
IMPORT_MAP(templeCuts);

IMPORT_MAP(linkedborder);

//importar fuentes de cutscenes
IMPORT_TILES(font);
IMPORT_TILES(fontCapeCuts);

UINT8 cs_counter = 0;
UINT8 cs_counter_2 = 0;
UINT8 cs_counter_3 = 0;
UINT8 cd_fade_idx = 0; 
UINT8 current_cs = 3;
UINT8 cs_cando_anim = 0;
UINT8 cs_anim_index = 0;

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
	BANKED_MAP(capeCuts1),
	BANKED_MAP(capeCuts2),
	BANKED_MAP(capeCuts7),
	BANKED_MAP(cinematicCape),
	BANKED_MAP(templeCuts),
};

const START_POS cs_start_positions[] = {
	{8, 96}, 
	{64, 87}, 
	{0, 96}, 
	{0, 96}, 
	{0, 96}, 
	{0, 96}, 
	{0, 96}, 
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


void FadeDMGCutscene(UINT8 fadeout) {
	
	UINT8 pals3[] = {0, 1, 2, 3};
    UINT8 pals2[] = {0, 0, 1, 2};
    UINT8 pals1[] = {0, 0, 0, 1};
	UINT8 pals0[] = {0, 0, 0, 0};

    BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(pals0[fadeout], pals1[fadeout], pals2[fadeout], pals3[fadeout] );
		
}


void FadeAllCutscene(){
    FadeDMGCutscene(3);
    PerDelay(20);
    NR50_REG = 0x55;
    FadeDMGCutscene(2);
    PerDelay(20);
    NR50_REG = 0x33;
    FadeDMGCutscene(1);
    PerDelay(20);
    NR50_REG = 0x11;
    FadeDMGCutscene(0);
    PerDelay(20);
    NR50_REG = 0x0;
    StopMusic;
    NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume
}





void FadeAllCapeCuts(){
	FadeDMGCutscene(0);
	FadeStepColorCustom(5);
	PerDelay(20);
	FadeDMGCutscene(1);
	FadeStepColorCustom(3);
	PerDelay(20);
	FadeDMGCutscene(2);
	FadeStepColorCustom(1);
	PerDelay(20);
	FadeDMGCutscene(3);
	FadeStepColorCustom(0);
	PerDelay(20);

}

void FadeIdx(UINT8 idx){
	DMGFadeCustom(idx);
	FadeStepColorCustom(idx);
}
void ClampScrollLimits();

void START() {
    const struct MapInfoBanked* level = &cs_levels[current_cs]; 
	// scroll_target = SpriteManagerAdd(SpritePlayer, 50, 50);
	

    //Se definen paletas para DMG
    BGP_REG = PAL_DEF(0, 1, 2, 3);
    OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);

	if(current_cs == 3 || current_cs == 7){
		scroll_offset_x = 0;
	}
	
    CRITICAL {
	    LOAD_SGB_BORDER(linkedborder);
    }
    
	CRITICAL {
#ifdef CGB
	if (_cpu == CGB_TYPE) {

		TMA_REG = 102u;
			
	}else{
	
		TMA_REG = 180u;
		
	}
#else
	TMA_REG = 180u;
		
#endif
	}

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

		case 3:
			SetHudWin(0);
			
			INIT_FONT(font, PRINT_WIN);
			cs_counter = 90;
			canDoInterrupt = 0;
			cs_counter_2 = 3;
			dialog = 0;
			can_dialog = 0;
			current_dialog = 9;
			state_interrupts = 0;
			break;
		case 4:
			SetHudWin(0);
			scroll_offset_x = 0;
			INIT_FONT(fontCapeCuts, PRINT_WIN);
			cs_counter = 50;
			canDoInterrupt = 0;
			cs_counter_2 = 3;
			dialog = 0;
			can_dialog = 0;
			current_dialog = 13;
			state_interrupts = 0;
			cs_cando_anim = 0;
			cs_anim_index = 0;
			break;
		case 5:
			SetHudWin(0);
			scroll_offset_x = 0;
			INIT_FONT(font, PRINT_WIN);
			cs_counter = 3;
			canDoInterrupt = 0;
			cd_fade_idx = 0;
			cs_counter_2 = 3;
			cs_counter_3 = 30;
			dialog = 0;
			can_dialog = 0;
			current_dialog = 16;
			state_interrupts = 0;
			cs_cando_anim = 0;
			cs_anim_index = 5;
			break;
        
		case 6:
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

		case 7:
			SHOW_SPRITES;
			scroll_offset_x = 0;
			can_scroll_y = 0;
			can_scroll_x = 0;
			SetHudWin(0);
			SpriteManagerAdd(SpritePlayerCutsTemple, cs_start_positions[current_cs].start_x, cs_start_positions[current_cs].start_y);
			INIT_FONT(font, PRINT_WIN);
			dialog = 0;
			can_dialog = 0;
			current_dialog = 0;
		break;
		
		default:
		
        break;
    }

	// scroll_target = 0;
	// clamp_enabled = 1;
	// scroll_x = 0;
	// ScrollRelocateMapTo(0,0);
	//scroll_x_vblank = 0 ;
	
	
	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

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

	}else  if(current_cs == 3 || current_cs == 4){
		if(--cs_counter == 0 && state_interrupts == 0){
			LYC_REG = 0;
			dialog_pos = 120;
			WY_REG = dialog_pos;
			state_interrupts = 1;
			dialog = 1;
		}

		if(current_cs == 4 && cs_cando_anim == 1){
			if(--cs_counter_2 == 0 && delta_time == 0){
				cs_counter_2 = _cpu == CGB_TYPE ? 6 : 2;
				if(cs_anim_index != 5 ){
					CapeCutsAnim(cs_anim_index);
					cs_anim_index++;
				}else{
					cs_cando_anim = 2;
					cs_counter_2 = 30;
				}
				
			}

		}else if(current_cs == 4 && cs_cando_anim == 2){
			if(--cs_counter_2 == 0){
				current_cs++;
				SetState(current_state);
			}
		}
	}else if(current_cs == 5 ){
		if(cs_cando_anim == 0){
			if(--cs_counter_2 == 0){
				cs_counter_2 = _cpu == CGB_TYPE ? 6 : 2;
				if(cs_anim_index != 14 ){
					CapeCutsAnim(cs_anim_index);
					cs_anim_index++;
				}else{
					cs_cando_anim = 1;
					cs_counter = 10;
					cs_counter_2 = _cpu == CGB_TYPE ? 6 : 2;
					cd_fade_idx = 5;
					FadeDMGCutscene(0);
					FadeStepColorCustom(5);
					CapeCutsAnim(cs_anim_index);
				}
			}
		}else if(cs_cando_anim == 1){
			if(--cs_counter_2 == 0){
				cs_counter_2 = _cpu == CGB_TYPE ? 6 : 2;
				if(cs_anim_index != 16 ){
					SHOW_WIN;
					CapeCutsAnim(cs_anim_index);
					cs_anim_index++;
					SHOW_WIN;
				}else{
					SHOW_WIN;
					CapeCutsAnim(cs_anim_index);
					SHOW_WIN;
					cs_anim_index = 14;
					
					
				}
			}

			if(--cs_counter == 0 && cd_fade_idx != 0){
				cs_counter = _cpu == CGB_TYPE ? 6 : 2;
				if(cd_fade_idx > 0){
					cd_fade_idx--;
					FadeIdx(cd_fade_idx);

				}
			}
			if(cs_counter_3 > 0 && cd_fade_idx == 0 ){
				cs_counter_3--;
				if(cs_counter_3 == 0 && dialog == 0){
					LYC_REG = 0;
					dialog_pos = 120;
					WY_REG = dialog_pos;
					state_interrupts = 1;
					dialog = 1;
				}
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
