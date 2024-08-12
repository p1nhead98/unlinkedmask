#include "Banks/SetAutoBank.h"
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Dialogos.h"
#include "Sound.h"
#include "Music.h"
#include "rand.h"
#include "TileAnimation.h"
#include "Banks/SetAutoBank.h"
#include "Print.h"
#include "Math.h"

#define tDelay 25

UINT8 current_dialog = 0;
UINT8 dialog = 0;
UINT8 can_dialog = 0;

extern UINT8 text_delay;
extern UINT8 current_level;
extern UINT8 state_interrupts;
extern UINT8 canDo;

UINT8 event = 0;
// extern UINT8 state_counter;
extern UINT8 dialog_pos;
extern UINT8 current_cs;
extern UINT8 cs_cando_anim;
extern UINT8 cs_anim_index;


extern UINT8 text_voice;
extern UINT8 player_cs_state;

extern INT8 boss_state;



IMPORT_TILES(mugshots);
IMPORT_MAP(capeCutsWin);

void FadeDMGCs(UINT8 fadeout) BANKED {
	
	UINT8 pals3[] = {0, 1, 2, 3};
    UINT8 pals2[] = {0, 0, 1, 2};
    UINT8 pals1[] = {0, 0, 0, 1};
	BGP_REG = OBP0_REG = OBP1_REG = PAL_DEF(0, pals1[fadeout], pals2[fadeout], pals3[fadeout] );
		
}

void FadeColorAndMusicCs(){
    FadeDMGCs(3);
    pDelay(20);
    NR50_REG = 0x55;
    FadeDMGCs(2);
    pDelay(20);
    NR50_REG = 0x33;
    FadeDMGCs(1);
    pDelay(20);
    NR50_REG = 0x11;
    FadeDMGCs(0);
    pDelay(20);
    NR50_REG = 0x0;
    StopMusic;
}


void SetMushot(){
    UINT8 i = 0;


    const UINT8 mug_tiles_up[] = { 247, 248, 249 };
    const UINT8 mug_tiles_mid[] = { 250, 251, 252 };
    const UINT8 mug_tiles_down[] = { 253, 254, 255 };

    for (i = 0; i != 3; ++i)
    {
        set_win_tiles(0 + i, 0, 1, 1,  &mug_tiles_up[i]);
        set_win_tiles(0 + i, 1, 1, 1,  &mug_tiles_mid[i]);
        set_win_tiles(0 + i, 2, 1, 1,  &mug_tiles_down[i]);
    }
}


void SetDialog() BANKED{
    switch (current_dialog)
    {
    case 0:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 0);
        SetMushot();
        text_delay = tDelay;
        text_voice = 1;
		PRINT(3, 0, "i recieve a "); 
		PRINT(3, 1, "divine message..."); 
        break;
    case 1:
        CleanText();
      
        text_delay = tDelay;
		PRINT(3, 0, "a call from "); 
		PRINT(3, 1, "beings that ");
        PRINT(3, 2, "promised me..."); 
        break;
    case 2:
        CleanText();
      
        text_delay = tDelay;
		PRINT(3, 0, "To give me  "); 
		PRINT(3, 1, "something that   ");
        PRINT(3, 2, "I will never "); 
        break;
    case 3:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "achieve in this"); 
        PRINT(3, 1, "material world."); 
        break;
    case 4:
        CleanText();
        LYC_REG = 0;
        WY_REG = 144;
        HIDE_WIN;
        dialog_pos = 144;
        dialog = 0;
        state_interrupts = 10;
        pDelay(10);
		FadeColorAndMusicCs();
        current_cs++;
		SetState(current_state);
        break;



     case 5:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 27);
        SetMushot();
        text_delay = tDelay;
        text_voice = 2;
		PRINT(3, 0, "viewer..."); 
        break;
    case 6:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "Come in,Viewer..."); 
		PRINT(3, 1, " ");
        break;
    case 7:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "We are waiting"); 
		PRINT(3, 1, "for your arrival.");
        break;
    case 8:
        CleanText();
        LYC_REG = 0;
        WY_REG = 144;
        HIDE_WIN;
        dialog_pos = 144;
        state_interrupts = 10;
        dialog = 0;
        pDelay(10);
		FadeColorAndMusicCs();
        current_level = 0;
        current_state = StateStage1;
		SetState(current_state);


        // CleanText();
        // LYC_REG = 0;
        // WY_REG = 144;
        // HIDE_WIN;
        // dialog_pos = 144;
        // dialog = 0;
        // state_interrupts = 10;
        // pDelay(10);
		// FadeColorAndMusicCs();
        // current_cs++;
		// SetState(current_state);
        break;










    case 9:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 27);
        SetMushot();
        text_delay = tDelay;
		PRINT(3, 0, "..."); 
        break;
    case 10:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "Viewer..."); 
        break;
    case 11:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "Kneel down before");
        PRINT(3, 1, "us."); 
        break;
    case 12:
        CleanText();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        pDelay(10);
		FadeColorAndMusic();
        current_cs++;
		current_dialog++;
        SetState(current_state);
        
        break;





    case 13:
        CleanWin();
        text_voice = 1;
        SetMugTiles(&mugshots, BANK(mugshots), 0);
        SetMushot();
        text_delay = tDelay;
		PRINT(3, 0, "WAIT A SECOND!");
        break;
    case 14:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "WHAT9S HAPPENING");
        PRINT(3, 1, "TO ME!?");
        break;
    case 15:
        CleanWin();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 10;
        HIDE_WIN;
        dialog = 0;
        can_dialog = 0;
        // state_counter = 3;
        cs_cando_anim = 1;
        HIDE_WIN;
        break;
        // pDelay(10);
		// FadeColorAndMusic();
        // current_level++;
		// current_dialog++;
        // SetState(current_state);
    // case 16:
    //     CleanText();
    //     text_delay = tDelay;
	// 	PRINT(3, 0, "WHAT'S HAPPENING");
    //     PRINT(3, 1, "TO ME!?");
    //     break;
        

    case 16:
        CleanWin();
        text_voice = 1;
        SetMugTiles(&mugshots, BANK(mugshots), 27);
        SetMushot();
        text_delay = tDelay;
		PRINT(3, 0, "It's our divine"); 
        PRINT(3, 1, "commission."); 
        break;
    case 17:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "This cape has"); 
        PRINT(3, 1, "been woven by "); 
        PRINT(3, 2, "the faith of "); 
        break;
    case 18:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "the people."); 
        break;
    case 19:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "People who perished"); 
        PRINT(3, 1, "in despair."); 
        break;
    case 20:
        
        CleanWin();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        can_dialog = 0;
        FadeColorAndMusic();
        current_level++;
        SetState(current_state);
        break;
        
    case 21:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 18);
        SetMushot();
        text_delay = tDelay;
        text_voice = 2;
		PRINT(3, 0, "you must be"); 
		PRINT(3, 1, "viewer right?"); 
        break;
    case 22:
        CleanText();
      
        text_delay = tDelay;
		PRINT(3, 0, "many times, i"); 
		PRINT(3, 1, "have thought i");
        PRINT(3, 2, "was a lost soul."); 
        break;
    case 23:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "guarding this"); 
		PRINT(3, 1, "temple that was");
        PRINT(3, 2, "once teeming"); 
        break;

    case 24:
        CleanText();
        text_delay = tDelay;
        PRINT(3, 0, "with life...");
        break;
    case 25:
        CleanText();
        text_delay = tDelay;
        PRINT(3, 0, "...");
        break;
    case 26:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "i see that you"); 
		PRINT(3, 1, "really accepted");
        PRINT(3, 2, "the challenge"); 
        break;
    case 27:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "of the elder"); 
		PRINT(3, 1, "gods...");
        break;

    case 28:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "that cape tells"); 
		PRINT(3, 1, "the whole story."); 
        break;
    case 29:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "however...");  
        break;
    case 30:
        
        CleanWin();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        can_dialog = 0;
        player_cs_state = 8;
        // FadeColorAndMusic();
        // current_level++;
        // SetState(current_state);
        break;
    case 31:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 18);
        SetMushot();
        text_delay = tDelay;
        text_voice = 2;
		PRINT(3, 0, "we were so naive,"); 
		PRINT(3, 1, "don't you think?"); 
        break;

    case 32:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "you don't really"); 
		PRINT(3, 1, "know what lies"); 
        PRINT(3, 2, "ahead."); 
        break;
    case 33:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "there was a time"); 
		PRINT(3, 1, "i had a body,"); 
        break;
    case 34:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "a body that i"); 
		PRINT(3, 1, "offered to take"); 
        PRINT(3, 2, "care of this"); 
        break;
    case 35:
        CleanText();
        text_delay = tDelay;
        PRINT(3, 0, "place.");
       
        break;
    case 36:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "a place where i"); 
		PRINT(3, 1, "truly believed"); 
        PRINT(3, 2, "i was special."); 
        break;
    case 37:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "miserable or not,"); 
		PRINT(3, 1, "that depends on"); 
        PRINT(3, 2, "your perspective."); 
        break;
    case 38:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "like ants"); 
		PRINT(3, 1, "searching for "); 
        PRINT(3, 2, "their food or"); 
        break;
    case 39:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "not healed...");  
        PRINT(3, 1, "scars that have"); 
        break;
    case 40:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "sleepless nights."); 
        break;
    case 41:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "what's your"); 
		PRINT(3, 1, "motivation in ");
		PRINT(3, 2, "life?");  
        break;
    case 42:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "you know it, "); 
		PRINT(3, 1, "don't you?");  
        break;
    case 43:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "what i've found"); 
		PRINT(3, 1, "out is that it"); 
        PRINT(3, 2, "will never be too"); 
        break;
    case 44:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "late to start"); 
		PRINT(3, 1, "over.");  
        break;
    case 45:
        CleanWin();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        can_dialog = 0;
        FadeColorAndMusic();
        current_level++;
        SetState(current_state);
        break;
    case 46:
        CleanWin();
        SetMugTiles(&mugshots, BANK(mugshots), 18);
        SetMushot();
        text_delay = tDelay;
        text_voice = 2;
		PRINT(3, 0, "you..."); 
        break;

    case 47:
        CleanText();
        text_delay = tDelay;
		PRINT(3, 0, "do you believe "); 
		PRINT(3, 1, "me.");
        PRINT(3, 1, "don't you?");
         
        break;

    case 48:
        CleanWin();    
        LYC_REG = 0;
        WY_REG = 144;
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        can_dialog = 0;
        boss_state = 60;
        break;


        
    default:
        break;
    }
} 

 void CleanWin() BANKED{
    text_delay = 0;
    if(print_target == 0){
        PRINT(0, 18, "                     "); 
        PRINT(0, 19, "                     "); 
        PRINT(0, 20, "                     "); 
    }else{
        PRINT(0, 0, "                     "); 
        PRINT(0, 1, "                     "); 
        PRINT(0, 2, "                     "); 
    }
 }

void CleanText() BANKED{
    text_delay = 0;
    if(print_target == 0){
        PRINT(3, 18, "                     "); 
        PRINT(3, 19, "                     "); 
        PRINT(3, 20, "                     "); 
    }else{
        PRINT(3, 0, "                     "); 
        PRINT(3, 1, "                     "); 
        PRINT(3, 2, "                     "); 
    }

}