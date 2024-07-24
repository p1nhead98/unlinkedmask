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
extern UINT8 text_delay;
extern UINT8 current_level;
extern UINT8 state_interrupts;
extern UINT8 dialog;
extern UINT8 canDo;
extern UINT8 event;
extern UINT8 state_counter;

extern UINT8 text_voice;




IMPORT_TILES(mugshots);
IMPORT_MAP(capeCutsWin);

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
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        pDelay(10);
		FadeColorAndMusic();
        current_level++;
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
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        pDelay(10);
		FadeColorAndMusic();
        current_level++;
		SetState(current_state);
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
        current_level++;
		current_dialog++;
        SetState(current_state);
        
        break;
    case 13:
        CleanWin();
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
        state_interrupts = 0;
        HIDE_WIN;
        dialog = 0;
        canDo = 0;
        state_counter = 3;
        event = 2;
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
        canDo = 0;
        FadeColorAndMusic();
        current_level++;
        SetState(current_state);
        break;
        
    default:
        break;
    }
} 

 void CleanWin() BANKED{
    text_delay = 0;
    PRINT(0, 0, "                     "); 
    PRINT(0, 1, "                     "); 
    PRINT(0, 2, "                     "); 
 }

void CleanText() BANKED{
    text_delay = 0;
    PRINT(3, 0, "                     "); 
    PRINT(3, 1, "                     "); 
    PRINT(3, 2, "                     "); 
}