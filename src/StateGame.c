#include "Banks/SetAutoBank.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Palette.h"
#include "Music.h"
#include "Scroll.h"
#include "Misc.h"
#include "TileAnimation.h"
#include <gb/gb.h>
#include "Keys.h"
#include "BankManager.h"
#include "MapInfo.h"
#include <string.h>
#include "SGB.h"
#include "Print.h"
#include "Dialogos.h"
#include "Cinematicas.h"
#include "WinController.h"
#include "BossAttacks.h"
#include "OAMManager.h"

IMPORT_MAP(titleScreen);

//LEVELS
IMPORT_MAP(lvl_1);
IMPORT_MAP(lvl_2);
IMPORT_MAP(lvl_3);
IMPORT_MAP(lvl_4);
IMPORT_MAP(lvl_5);
IMPORT_MAP(lvl_6);
IMPORT_MAP(lvl_7);
IMPORT_MAP(lvl_8);
IMPORT_MAP(lvl_9);
IMPORT_MAP(lvl_10);
IMPORT_MAP(lvl_11);
IMPORT_MAP(lvl_12);
IMPORT_MAP(lvl_13);
IMPORT_MAP(lvl_14);
IMPORT_MAP(lvl_15);
IMPORT_MAP(lvl_16);
IMPORT_MAP(lvl_17);
IMPORT_MAP(lvl_18);
IMPORT_MAP(lvl_19);
IMPORT_MAP(lvl_20);
IMPORT_MAP(lvl_20);
IMPORT_MAP(bossfight1);

//CUTSCENES
IMPORT_MAP(intro_door);
IMPORT_MAP(cinematicCape);
IMPORT_MAP(capeCuts1);
IMPORT_MAP(capeCuts2);
IMPORT_MAP(capeCuts3);
IMPORT_MAP(capeCuts7);
IMPORT_MAP(capeCuts16);
IMPORT_MAP(templeCuts);

IMPORT_MAP(templeCuts);
IMPORT_MAP(doorCuts);
IMPORT_TILES(capeCuts3Tiles);
IMPORT_MAP(bossfightTrailer);



//BKG ANIM
IMPORT_TILES(cloudAnim1);
IMPORT_TILES(cloudAnim2);
IMPORT_TILES(spinChangerAnim);
IMPORT_TILES(spinChangerAnim2);
IMPORT_TILES(spinChangerAnim3);
IMPORT_TILES(spinChangerAnim4);

IMPORT_TILES(waterAnim1);
IMPORT_TILES(waterAnim2);

IMPORT_TILES(mugshots);


// IMPORT_MAP(window);
// IMPORT_MAP(window2);


IMPORT_MAP(linkedborder);

IMPORT_TILES(font);
IMPORT_TILES(fontCapeCuts);


DECLARE_MUSIC(song1);
DECLARE_MUSIC(unlinkedchainedsoul);
DECLARE_MUSIC(unlinkedrooftop);
DECLARE_MUSIC(unlinkedinside1);
DECLARE_MUSIC(unlinkedtitlescreen);

UINT8 collision_tiles[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 33, 34, 35, 36, 37, 38, 62, 63, 64, 65, 66, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 0};
UINT8 collision_tiles2[] = {4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 56, 57, 58, 59, 60, 61, 62, 63, 77, 78, 79, 80, 81, 82, 83, 84, 0};

UINT8 collision_boss1[] = {4, 8, 64, 68,  0};


UINT8 collision_boss_trailer[] = {59, 60, 61, 62, 63, 64, 65, 66, 67, 0};

UINT8 ct_lvl25[] = {4, 5, 6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 56, 57, 58, 59, 60, 61, 62, 63, 77, 78, 79, 80, 0};


UINT8 bossfight_col[] = {74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 0};

UINT8 windtower_tiles[] = {10,7,8,9,15,16,17,4,5,6,82,83,84,85,86,87,88,89,18,12, 0};

UINT8 door_sounds[] = { 0x49, 0x3F, 0x35, 0x2B, 0x21, 0x17 };



extern UINT8 door_time;
extern UINT8 door_time_btwn;
extern UINT8 door_time_btwn_start;
extern UINT8 door_open;
extern BOOLEAN door_button;



UINT8 current_level = 0;

UINT8 doAnimCount = 0;

UINT8 bossAttackCounter = 0;
UINT8 bossAttackState = 0;
UINT8 AnimCounter = 0;
UINT8 AnimCounter2 = 0;


UINT8 IsFirstLvl = 0;

UINT8 start_screen = 0;

UINT8 onoff_auto_time = 0;

UINT8 music_fade = 70;
UINT8 start_fade = 0;

struct TilesInfo* original_tiles = 0;
UINT8 original_lvl_bank = 0;

UINT8 state_counter = 0;


extern UINT8 state_interrupts;
extern UINT16 scroller_y;
extern UINT8 canDoInterrupt;
extern UINT8 counterInterrupt;
extern UINT8 counterInterrupt2;
// extern UINT16 scroller_x;

extern UINT8 max_life;
extern UINT8 current_life;
extern UINT8 stop_music_on_new_state;
extern UINT8 on_off;

extern UINT8 can_scroll_x;
extern UINT8 can_scroll_y;

extern UINT8 current_dialog;
extern UINT8 dialog_pos;

UINT8 event = 0;
UINT8 canDo = 0;
UINT8 dialog = 0;
UINT8 anim_index = 0;

UINT8 IsCutscene = 0;


IMPORT_TILES(spikesAnim);
IMPORT_TILES(spikesAnim2);
IMPORT_TILES(spikesAnim3);
IMPORT_TILES(spikesAnim4);

IMPORT_TILES(flameBoss);
IMPORT_TILES(flameBoss2);
IMPORT_TILES(flameBoss3);



// IMPORT_TILES(waterAnim);
// IMPORT_TILES(waterfallAnim);
// IMPORT_TILES(waterfallAnim2);


Sprite* player_sprite = 0;

Sprite* bossFireAttack_spr = 1;

UINT8 change_jump_count = 0;

struct MapInfoBanked {
	UINT8 bank;
	struct MapInfo* map;
};

#define BANKED_MAP(MAP) {BANK(MAP), &MAP}

const struct MapInfoBanked levels[] = {
	BANKED_MAP(titleScreen),
	BANKED_MAP(intro_door),
	BANKED_MAP(doorCuts),
	BANKED_MAP(lvl_1),
	BANKED_MAP(lvl_2),
	BANKED_MAP(lvl_3),
	BANKED_MAP(lvl_4),
	BANKED_MAP(lvl_5),
	BANKED_MAP(cinematicCape),
	BANKED_MAP(capeCuts1),
	BANKED_MAP(capeCuts2),
	BANKED_MAP(capeCuts7),
	BANKED_MAP(capeCuts16),
	BANKED_MAP(cinematicCape),
	BANKED_MAP(lvl_6),
	BANKED_MAP(lvl_7),
	BANKED_MAP(lvl_8),
	BANKED_MAP(lvl_9),
	BANKED_MAP(lvl_10),
	BANKED_MAP(templeCuts),
	BANKED_MAP(lvl_11),
	BANKED_MAP(lvl_12),
	BANKED_MAP(lvl_13),
	BANKED_MAP(lvl_14),
	BANKED_MAP(lvl_15),
	BANKED_MAP(lvl_16),
	BANKED_MAP(lvl_17),
	BANKED_MAP(lvl_18),
	BANKED_MAP(lvl_19),
	BANKED_MAP(lvl_20),
	BANKED_MAP(bossfight1),
	BANKED_MAP(bossfightTrailer),
	
};



typedef struct {
    UINT16 start_x;
    UINT16 start_y;
} START_POS;

const START_POS start_positions[] = {
	{8, 0}, //TitleScreen	----- current level = 0 
	{0, 96}, //IntroDoor	----- current level = 1
	{0, 96}, //IntroDoor	----- current level = 2
	{8, 144}, //Level 1 Player Start Position	----- current level = 3
	{8, 128}, //Level 2 Player Start Position	----- current level = 4
	{8, 112}, //Level 3 Player Start Position	----- current level = 5
	{8, 128}, //Level 4 Player Start Position	----- current level = 6
	{8, 96},  //Level 5 Player Start Position	----- current level = 7
	{0, 96}, //CinematicCape	----- current level = 8
	{0, 96}, //CinematicCape2	----- current level = 9
	{0, 96}, //CinematicCape2	----- current level = 10
	{0, 96}, //CinematicCape7	----- current level = 11
	{0, 96}, //CinematicCape16	----- current level = 12
	{0, 96}, //CinematicCape	----- current level = 13
	{8, 144},  //Level 6 Player Start Position	----- current level = 14
	{8, 112},  //Level 7 Player Start Position	----- current level = 15
	{8, 96},  //Level 8 Player Start Position	----- current level = 16
	{8, 128},  //Level 9 Player Start Position	----- current level = 17
	{8, 128},  //Level 10 Player Start Position	----- current level = 18
	{0, 96}, //CinematicTemple	----- current level = 19
	{8, 144},  //Level 11 Player Start Position	----- current level = 20
	{8, 96},  //Level 12 Player Start Position	----- current level = 21
	{8, 96},  //Level 13 Player Start Position	----- current level = 22
	{8, 96},  //Level 14 Player Start Position	----- current level = 23
	{8, 96},  //Level 15 Player Start Position	----- current level = 24
	{8, 96},  //Level 16 Player Start Position	----- current level = 25
	{8, 96},  //Level 17 Player Start Position	----- current level = 26
	{8, 96},  //Level 18 Player Start Position	----- current level = 27
	{8, 96},  //Level 19 Player Start Position	----- current level = 28
	{8, 96},  //Level 20 Player Start Position	----- current level = 29
	{48, 136},  //boss fight Player Start Position	----- current level = 30
	{28, 30},  //boss fight Player Start Position	----- current level = 30
};








void START()
{
	const struct MapInfoBanked* level = &levels[current_level]; // Se declara mapa del nivel actual
	current_life = max_life; //se establece que la vida actual sea la maxima vida permitida
	start_screen = 0; // variable que determina si esta acitvada la pantalla de start o no

	//Se establecen la paleta de colores de los sprites en DMG//////////////////////////////
	OBP0_REG = PAL_DEF(3, 0, 1, 2);
	OBP1_REG = PAL_DEF(1, 0, 0, 0);
	/////////////////////////////////////////////////////////

	IsFirstLvl = current_level == 3 ? 1 : 0; // variable para realizar animacion de intro en primer nivel
	can_scroll_x = 1; // determina que se puede hacer scroll en el eje x

	music_fade = 70;
	start_fade = 0;

	event = 0;
	on_off = 0;
	change_jump_count = 0;
	// if(current_level == 10){
	// 	INIT_FONT(fontCapeCuts, PRINT_WIN);
	// }else{
	// 	INIT_FONT(font, PRINT_WIN);
	// }
	
	// if(current_level != 11){
	
		if(current_level == 31){
			InitScroll(level->bank, level->map, collision_boss_trailer, 0);

		}else if(current_level == 25){
			InitScroll(level->bank, level->map, ct_lvl25, 0);
		}else if(current_level == 30){
			InitScroll(level->bank, level->map, bossfight_col, 0);
		}else if( current_level < 20){
			InitScroll(level->bank, level->map, collision_tiles, 0);
		}else if( current_level > 19){
			InitScroll(level->bank, level->map, collision_tiles2, 0);
		}
	//}

	
	
	
		// CapeCutsAnim
	

	switch (current_level){
		case 0:
			PlayMusic(unlinkedtitlescreen, 1);
		break;
		case 1:
			SetHudWin(0);
			IsCutscene = 1;
			WY_REG = 144;
			SHOW_SPRITES;
			canDo = 0;
			dialog = 0;
			break;
		case 2:

			state_counter = 60;
			canDo = 0;
			dialog = 0;
			event = 0;
			SpriteManagerAdd(SpriteViewerH, 64, 87);
		
				
			FillDoorCinem();
			scroller_y = 0;
			canDoInterrupt = 0;
			LYC_REG = 0;
			state_interrupts = 2;
			counterInterrupt = 30;
			counterInterrupt2 = 30;
			
			break;
		// case 6:
		// 	PlayMusic(unlinkedchainedsoul, 1);
		// 	ScrollRelocateMapTo(0,48);
		// 	break;

		// case 8:
		// 	canDo = 0;
		// 	dialog = 0;
		// 	state_counter = 60;
		// 	break;

		case 9:
			canDo = 0;
			dialog = 0;
			state_counter = 60;
			current_dialog = 9;
			break;
		
		case 10:
			canDo = 0;
			dialog = 0;
			state_counter = 60;
			current_dialog = 13;
			// CapeCutsAnim(0);
			break;
		case 11:
			// canDo = 0;
			// dialog = 0;
			// state_counter = 60;
			// event = 0;
			// SHOW_SPRITES;
			// SHOW_WIN;
			// WY_REG = 144; 
			// SpriteManagerAdd(SpriteCapeCuts, 0, 0);
			canDo = 0;
			anim_index = 6;
			dialog = 0;
			state_counter = 3;
				// CapeCutsAnim(0);
			break;
		case 12:
			// canDo = 0;
			// dialog = 0;
			// state_counter = 60;
			// event = 0;
			// SHOW_SPRITES;
			// SHOW_WIN;
			WY_REG = 144; 
			// SpriteManagerAdd(SpriteCapeCuts, 0, 0);
			canDo = 0;
			anim_index = 15;
			dialog = 0;
			state_counter = 1;
			event = 0;
				// CapeCutsAnim(0);
			break;

	



		case 20:
			PlayMusic(unlinkedinside1, 1);
			door_time_btwn_start = door_time_btwn = 35;
			SetOnOffCols(collision_tiles2, on_off);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			IsCutscene = 0;
			state_interrupts = 0;
			break;
		case 21:
			door_time_btwn_start = door_time_btwn = 120;
			SetOnOffCols(collision_tiles2, on_off);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			IsCutscene = 0;
			state_interrupts = 0;
			break;
		case 22:
			door_time_btwn_start = door_time_btwn = 120;
			SetOnOffCols(collision_tiles2, on_off);
			ScrollRelocateMapTo(0,48);
			SetHudWin(1);
			IsCutscene = 0;
			state_interrupts = 0;
			break;
		case 23:
			ScrollRelocateMapTo(0,48);
			door_time_btwn_start = door_time_btwn = 170;
			SetOnOffCols(collision_tiles2, on_off);
			SetOnOffColsEvent(collision_tiles2, 0);
			SetHudWin(1);
			IsCutscene = 0;
			canDo = 0;
			event = 0;
			state_interrupts = 0;
			break;
		case 24:
			ScrollRelocateMapTo(0,48);
			door_time_btwn_start = door_time_btwn = 220;
			SetOnOffCols(collision_tiles2, on_off);
			SetHudWin(1);
			IsCutscene = 0;
			state_interrupts = 0;
			break;
		case 25:
			ScrollRelocateMapTo(0,48);
			// door_time_btwn_start = door_time_btwn = 220;
			// SetOnOffCols(collision_tiles2, on_off);
			canDo = 0;
			AutomaticOnOff(collision_tiles2, canDo);
			onoff_auto_time = 20;
			SetHudWin(1);
			IsCutscene = 0;
			state_interrupts = 0;
			break;
		
		case 28:
		canDo = 0;
		dialog = 0;
		AutomaticOnOff(collision_tiles2, canDo);
		ScrollRelocateMapTo(0,48);
		SetHudWin(1);
		IsCutscene = 0;
		state_interrupts = 0;
		break;
		
		case 29:
		ScrollRelocateMapTo(0,48);
		onoff_auto_time = 20;
		canDo = 0;
		SetHudWin(1);
		IsCutscene = 0;
		state_interrupts = 0;
		AutomaticOnOff(collision_tiles2, canDo);
		break;

		case 30:
		ScrollRelocateMapTo(40,40);
		// onoff_auto_time = 20;
		// canDo = 0;
		SetHudWin(1);
		AnimCounter = 0;
		IsCutscene = 0;
		state_interrupts = 3;
		can_scroll_x = 0;
		canDoInterrupt = 0;
		bossAttackCounter = 10;
		bossAttackState = 0;
		doAnimCount = 3;
		Attacks_Animations(30);
		
		// AutomaticOnOff(collision_tiles2, canDo);
		break;

		default:
			if(current_level != 1 && current_level != 2  && current_level != 8 && current_level != 9 && current_level != 13 && current_level != 19){
				
				ScrollRelocateMapTo(0,48);
				
				SetHudWin(1);
				IsCutscene = 0;
				state_interrupts = 0;
				

			}else{
				SetHudWin(0);
				IsCutscene = 1;
				state_interrupts = 10;
				SHOW_SPRITES;
			}
			canDo = 0;
			dialog = 0;
			
			break;
	}

	

	if(current_level != 0){
		if(current_level == 30){
			SpriteManagerAdd(SpriteBoss1, 144, 68);
			bossFireAttack_spr = SpriteManagerAdd(SpriteBossFireFlash, 0, 138);
		}
		if(current_level == 1 || current_level == 8 || current_level == 13 ){
			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayerCutscenes, start_positions[current_level].start_x, start_positions[current_level].start_y);
			// if(current_level == 13){
			// 	FadeInColor();
			// }
		}else if(current_level == 19){
			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayerCutsTemple, start_positions[current_level].start_x, start_positions[current_level].start_y);
		}else if( current_level < 8 && current_level != 2 && current_level != 19){
			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayerNoCape, start_positions[current_level].start_x, start_positions[current_level].start_y);
		}else if( current_level > 13){
			player_sprite = scroll_target = SpriteManagerAdd(SpritePlayer, start_positions[current_level].start_x, start_positions[current_level].start_y);
		}
		
	}

	if(current_level == 31){
		SpriteManagerAdd(SpriteBossHand1, 32, 56);
		SpriteManagerAdd(SpriteBossHand2, 112, 56);
	}

	// LY_REG  = 0;
	// disable_interrupts();
	// add_LCD(LCD_Interrupt);
	// add_VBL(VBL_Interrupt);
	// enable_interrupts();

	// if(current_level == 0){
	// 	DISPLAY_OFF;
	// 	LOAD_SGB_BORDER(linkedborder);
	// 	DISPLAY_ON;
	// }
	
	// stop_music_on_new_state = 0;
	// event = 0;
	// current_level = 9;
	


	door_open = 0;
	door_button = 1;
	door_time = 6;

	doAnimCount = 3;
	AnimCounter2 = 0;
	



	

	
 
	

	



	// INIT_HUD(window);

	
	// if(current_level != 0){
	// 	if(current_level < 11){
			
	// 	}else{
	// 		INIT_HUD(window2);
	// 	}
	// }else{
	// 	HIDE_WIN;
	// }

	//InitScroll(level->bank, level->map, windtower_tiles, 0);




	CRITICAL {
#ifdef CGB
	if (_cpu == CGB_TYPE) {
		if(current_level > 10){
				TMA_REG = 102u;
			}else if(current_level == 0){
				TMA_REG = 55u;
			}else{

				TMA_REG = 102u;
			}
	}else{
		if(current_level > 10 && current_level < 20){
			TMA_REG = 180u;
		}else if(current_level > 19){
			TMA_REG = 175u;
		}else if(current_level == 0){
			TMA_REG = 154u;
		}else{

			TMA_REG = 180u;
		}
	}
#else
		if(current_level > 10 && current_level < 20){
			TMA_REG = 180u;
		}else if(current_level > 19){
			TMA_REG = 175u;
		}else if(current_level == 0){
			TMA_REG = 154u;
		}else{

			TMA_REG = 180u;
		}
#endif
	}

	// #ifdef CGB
	// 	if (_cpu == CGB_TYPE) {
	// 		if(current_level > 10){
	// 			TMA_REG = 180u;
	// 		}else if(current_level == 0){
	// 			TMA_REG = 154u;
	// 		}else{

	// 			TMA_REG = 90u;
	// 		}		
	// 	} else
	// #endif
	// 	if(current_level > 10){
	// 		TMA_REG = 180u;
	// 	}else if(current_level == 0){
	// 		TMA_REG = 154u;
	// 	}else{

	// 		TMA_REG = 180u;
	// 	}
	// }	



	if(IsCutscene == 1){
		INIT_FONT(font, PRINT_WIN);
	}

	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

	// if(current_level != 0){
		
	// }else{
	// 	HIDE_WIN;
	// }

	


}

void UPDATE()
{
	const struct MapInfoBanked* level = &levels[current_level]; // Se declara mapa del nivel actual

	if (KEY_TICKED(J_SELECT) && !KEY_PRESSED(J_LEFT)){
		current_level++;
		SetState(current_state);
	} else if (KEY_TICKED(J_SELECT) && KEY_PRESSED(J_LEFT)){
		current_level--;
		SetState(current_state);
	}



	if(dialog == 1){
		if(canDo == 0){
			SetDialog();
			canDo = 1;
		}
		if(KEY_TICKED(J_A) && canDo == 1){
			current_dialog++;
			canDo = 0;
		}
	}






	if(current_level != 31){

	if(current_level == 2){
		if(canDoInterrupt == 0){
			canDoInterrupt = 1;
		}else if (canDoInterrupt == 2){
			if(--state_counter == 0 &&  event == 0){
				event = 1;
				CleanWin();
				dialog_pos = 20;
				if(current_dialog < 5){
					current_dialog = 5;
				}
				dialog = 1;
				
				WY_REG = dialog_pos;
				state_interrupts = 1;
				LYC_REG = 0;
				
			}
		}
	}








	if((current_level == 9 || current_level == 10) && event != 2){
		if(--state_counter == 0 && event == 0){
			event = 1;
			CleanWin();
			dialog_pos = 120;
			dialog = 1;
			
			WY_REG = dialog_pos;
			state_interrupts = 1;
			LYC_REG = 0;
			
		}
		// }else if(--state_counter == 0 && canDo == 0 && current_dialog == 15){
		// 	state_counter = 3;
		// 	scroll_x = scroll_x == 2 ? 0 : 2;
		// }
	}






	if(current_level == 10 && event == 2){
		
		if(--state_counter == 0 ){
			// scroll_y = scroll_y == 4 ? 0 : 4;
			
			state_counter = 4;
			if(anim_index != 5 ){
				CapeCutsAnim(anim_index);
				anim_index++;
			}else{
				event = 3;
				state_counter = 30;
			}
			
		}
	}else if(current_level == 10 && event == 3){
		if(--state_counter == 0)
		{

			current_level = 11;
			SetState(current_state);
			
		}
		
	}






	if(current_level == 11){
		if(--state_counter == 0){
			if(anim_index != 14){
				CapeCutsAnim(anim_index);
				anim_index++;
				state_counter = 4;
			}else{
				FadeDMGCustom(0);
				current_level++;
				SetState(current_state);
			}
		}
	}





	if(current_level == 12){
		if(event < 12){
				event++;
				if(event == 10 && dialog == 0){
					event = 20;
					CleanWin();
					dialog_pos = 120;
					if(current_dialog < 16){
						current_dialog = 16;
					}
					dialog = 1;
					
					WY_REG = dialog_pos;
					state_interrupts = 1;
					LYC_REG = 0;
					
				}
			}	
		if(--state_counter == 0){
			SHOW_WIN;
			CapeCutsAnim(anim_index);
			anim_index++;
			state_counter = 4;
			
			if(anim_index == 17){
				SHOW_WIN;
				anim_index = 14;
				
			}
			
		}	
	}

	
	if(current_level == 11){
		if(--state_counter == 0){
			canDo = canDo == 0 ? 1 : 0;
			CapeCutsAnim(canDo);
			--state_counter = 8;
		}
	}



	if(current_level == 25 || current_level == 29){
		if(--onoff_auto_time == 0 && start_screen == 0){
			if(current_level == 29){
				onoff_auto_time = 60;
			}else{
				onoff_auto_time = 90;
			}
			
			canDo = canDo == 0 ? 1 : 0;
			AutomaticOnOff(collision_tiles2, canDo);
			PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
            PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
		}	
	}

	// vsync();
	// scanline_offsets = scanline_offsets_tbl + ((sys_time >> 2) & 0x07u)



	// if(current_level != 17 && current_level != 18 && start_screen == 0 ){
	if(door_open == 1 && door_time_btwn > 0 && start_screen == 0){
		door_time_btwn--;
	}else if(door_open == 1 && start_screen == 0){
		door_time--;
		PlayFx(CHANNEL_1 , 10, 0x18, 0xBF, 0xF1,door_sounds[door_time], 0x87);
		RefreshTimer();
		door_time_btwn = door_time_btwn_start;
	}
	if(door_time == 0 ){
		door_open = 0;
		door_time = 6;
		door_button = 1;
		SetDoorCols(0);
		PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
	}


	if(KEY_TICKED(J_START) ){
		if( IsCutscene == 0 && current_level != 0){
			start_screen = start_screen == 0 ? 1 : 0;
				if( start_screen == 1 ){
					DISPLAY_OFF;
					SetWindowY(0);
					SetPauseMenu( level->map, level->bank );
				}else{
					SetWindowY(128);
					SetPauseMenu( level->map, level->bank );
					if(door_open == 1){
						RefreshTimer();
						SetDoorCols(door_open);
					}
					if(current_level == 20 || current_level == 21 || current_level == 22 ||  current_level == 23 || current_level == 28){
						SetOnOffCols(collision_tiles2, on_off);
					}else if(current_level == 25 || current_level == 29){
						AutomaticOnOff(collision_tiles2, canDo);
					}
					RefreshLife();
					if(player_sprite->y != 0){
						pDelay(40);
					}
			}
		}
	}

		
	if(KEY_TICKED(J_START) && current_level == 0){
		start_fade = 1;
		FadeColorAndMusic();
		current_level++;
		SetState(current_state);
	}



	if(--doAnimCount == 0 && IsCutscene == 0  && current_level != 30 ){

		
		AnimCounter = AnimCounter == 1 ? 0 : 1;
		
		if(start_screen == 0){
			
			if(AnimCounter == 0){
				Spike_anim(&spikesAnim, 112, BANK(spikesAnim));
			}else{
				Spike_anim(&spikesAnim2, 112, BANK(spikesAnim2));
			}


			if(current_level == 25 || current_level == 29){

				if(canDo == 0){
					if(AnimCounter == 0){
						Spike_anim(&spikesAnim, 81, BANK(spikesAnim));
					}else{
						Spike_anim(&spikesAnim2, 81, BANK(spikesAnim2));
					}
				}else{
					if(AnimCounter == 0){
						Spike_anim(&spikesAnim, 85, BANK(spikesAnim));
					}else{
						Spike_anim(&spikesAnim2, 85, BANK(spikesAnim2));
					}
				}


				
			}
			if(current_level > 25 && current_level != 30){
				AnimCounter2++;
				if(change_jump_count == 0){
					Tile_Anim(AnimCounter2, 6, &spinChangerAnim, 47, BANK(spinChangerAnim));	
				}else{
					Tile_Anim(AnimCounter2, 6, &spinChangerAnim2, 47, BANK(spinChangerAnim2));
				}
		
			// 	Tile_Anim(AnimCounter2 + 8, 16, &cloudAnim1, 46, BANK(cloudAnim1));
			// 	// Tile_Anim(AnimCounter2, 8, &cloudAnim2, 44, BANK(cloudAnim2));
			}

			
		}
		doAnimCount = 5;
		
	}

	
		

	// 	} else if(current_level == 18){
	// 		if(--doAnimCount == 0 && current_level > 0){



	// 			AnimCounter++;
	// 			Tile_Anim(AnimCounter , 2, &waterAnim, 47, BANK(waterAnim));
	// 			Tile_Anim(AnimCounter , 8, &waterfallAnim2, 72, BANK(waterfallAnim2));


	// 			doAnimCount = 5;
	// 		}
	// }
	if(current_level == 23 && player_sprite->x > 1142 && canDo == 0 && event == 0){
		canDo = 1;
		SetOnOffColsEvent(collision_tiles2, 1);
	}
	if(event == 1 && IsCutscene == 0){
		// can_scroll_x = 1;
		event++;
		SetOnOffColsEvent(collision_tiles2, 2);
	}


	if( change_jump_count > 0 ){
		if(change_jump_count == 20){
			Set_SpinChange_Tiles(&spinChangerAnim4, BANK(spinChangerAnim4), 8);
		}else if(change_jump_count == 1){
			Set_SpinChange_Tiles(&spinChangerAnim3, BANK(spinChangerAnim3), 8);
		}
		change_jump_count--;
	}

	if( current_level == 30){

	
		
			
	
			if(AnimCounter < 3){
				AnimCounter++;

					if(AnimCounter == 0){
						Spike_anim(&flameBoss2, 108, BANK(flameBoss2));
					}else if(AnimCounter == 1){
						Spike_anim(&flameBoss3, 108, BANK(flameBoss3));
					} else if(AnimCounter == 2){
						Spike_anim(&flameBoss, 108, BANK(flameBoss));
					}
				if(AnimCounter == 3){
					AnimCounter = 0;
				}
			}
		
		
	}
	
	// if(KEY_TICKED(J_A)){
	// 	char name [6] = "Dragon";
	// 	PRINT(0, 0, "hola mundo");
	// }
	}else{
		if(--doAnimCount == 0){
			AnimCounter2++;
			Tile_Anim(AnimCounter2, 8, &waterAnim1, 57, BANK(waterAnim1));	
			Tile_Anim(AnimCounter2, 8, &waterAnim2, 58, BANK(waterAnim2));	
			doAnimCount = 5;
		}
	}

}
