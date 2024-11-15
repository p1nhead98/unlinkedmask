#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"
#include "Music.h"

// const UINT8 anim_box[] = {2, 0, 1};
// const UINT8 anim_box2[] = {2, 2, 2};

const UINT8 pct_walk_anim[] = {4, 0, 1, 0, 2};
const UINT8 pct_entering[] = {15, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 15, 15};
const UINT8 pct_stand[] = {2, 16, 17};


extern UINT8 start_screen;
extern UINT8 state_interrupts;
extern UINT8 dialog;
extern UINT8 current_level;
extern UINT8 dialog_pos;
extern UINT8 canDoInterrupt;
extern INT16 scroller_y;

UINT8 player_cst_state = 0;
UINT8 player_cst_counter = 0;
UINT8 player_cst_counter2 = 0;
UINT8 player_cst_canDo = 0;


void START()
{
    player_cst_state = current_level == 26 ? 2 : 0;
    SetSpriteAnim(THIS, pct_walk_anim, 15);
    THIS->x -= 8;
    player_cst_counter = 0;
    player_cst_counter2 = 20;
    

}

void UPDATE()
{
    switch (player_cst_state)
    {
        case 0:
            if(THIS->x != 113){
                THIS->x++;
                if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_cst_canDo == 0){
                    player_cst_canDo = 1;
                    PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
                }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_cst_canDo == 1){
                    player_cst_canDo = 0;
                }
                if (player_cst_counter < 4){
                    if(--player_cst_counter2 == 0){
                        FadeMusic(player_cst_counter);
                        player_cst_counter++;
                        player_cst_counter2 = 20;
                        
                    }
                
                }
            }else{
                // THIS->anim_speed = 0;
                // player_cst_state++;
                // player_c_counter2 = 20;
                // SetSpriteAnim(THIS, pcs_stand, 15);
                player_cst_state++;
                SetSpriteAnim(THIS, pct_entering, 68);
                
            }
            break;
        case 1:
            if(THIS->x != 158){
                THIS->x++;
            }
            if(THIS->anim_frame == 14){
                THIS->y = -16;
            }
            if(THIS->x > 157){
                current_level = 0;
                current_state = StateStage3;
                SetState(current_state);
            }
            break;
        case 2:
            if(THIS->x != 72){
                
                if (player_cst_counter < 4){
                    if(--player_cst_counter2 == 0){
                        FadeMusic(player_cst_counter);
                        player_cst_counter++;
                        player_cst_counter2 = 20;
                    }
                
                }
                THIS->x++;
                if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_cst_canDo == 0){
                    player_cst_canDo = 1;
                    PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
                }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_cst_canDo == 1){
                    player_cst_canDo = 0;
                }
            }else{
                player_cst_state++;
                canDoInterrupt = 1;
                player_cst_counter2 = 20;
                SetSpriteAnim(THIS, pct_stand, 15);
            }
            break;
        case 3:
            THIS->y = scroller_y + 97;
            if(scroller_y == 1){
                player_cst_state++;
            }
            break;
        case 4:
            THIS->y--;
            break;
    }
}

void DESTROY()
{
}