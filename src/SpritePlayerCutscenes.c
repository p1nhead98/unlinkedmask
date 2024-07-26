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
DECLARE_MUSIC(unlinkedchainedsoul);
const UINT8 pcs_walk_anim[] = {4, 1, 2, 0, 3};
const UINT8 pcs_stand[] = {2, 4, 5};
const UINT8 pcs_air[] = {5, 6, 7, 8, 9, 10};
const UINT8 pcs_cape_stand[] = {2, 11, 12};
const UINT8 pcs_cape_walk[] = {4, 12, 13, 12, 14};

extern UINT8 start_screen;
extern UINT8 state_interrupts;
extern UINT8 dialog;
extern UINT8 current_level;
extern UINT8 dialog_pos;

UINT8 player_cs_state = 0;
UINT8 player_c_counter = 0;
UINT8 player_c_counter2 = 0;
UINT8 player_c_counter3 = 0;
UINT8 player_c_canDo = 0;

void START()
{
    player_cs_state = 0;
    SetSpriteAnim(THIS, pcs_walk_anim, 15);
    THIS->x -= 8;
    player_c_counter = 0;
    player_c_counter2 = 20;
    if(current_level == 13){
        SetSpriteAnim(THIS, pcs_air, 12);
        player_cs_state = 2;
        THIS->x = 72;
        THIS->y = 16;
        player_c_counter = 2;
        player_c_counter2 = 1;
        player_c_counter3 = 4;
    }
}

void UPDATE()
{
    switch (player_cs_state)
    {
    case 0:
        if(THIS->x != 72){
            
            if(current_level == 8 && player_c_counter < 4){
                if(--player_c_counter2 == 0){
                    FadeMusic(player_c_counter);
                    player_c_counter++;
                    player_c_counter2 = 20;
                }
               
            }
            THIS->x++;
            if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_c_canDo == 0){
                player_c_canDo = 1;
                PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
            }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_c_canDo == 1){
                player_c_canDo = 0;
            }
        }else{
            player_cs_state++;
            player_c_counter2 = 20;
            SetSpriteAnim(THIS, pcs_stand, 15);
        }
        break;
    case 1:
       
        if(current_level != 8){
            dialog_pos = 20;
            WY_REG = dialog_pos;
            state_interrupts = 1;
            LYC_REG = 0;
            dialog = 1;
        }
        if(current_level == 8){
            if(--player_c_counter2 == 0){
                FadeColor();
                current_level++;
                SetState(current_state);
            }
            
        }
        break;
    case 2:
        if(THIS->y != 96){
            if(--player_c_counter2 == 0){

                player_c_counter2 = 10;
                SpriteManagerAdd(SpritePlayerStars, THIS->x + 2, THIS->y - 8);
            }
            if(--player_c_counter3 == 0){

                player_c_counter3 = 20;
                SpriteManagerAdd(SpritePlayerStars, THIS->x + 8, THIS->y - 8);
            }
            if(--player_c_counter == 0){
                THIS->y++;
                player_c_counter = 2;
              
            }
        }else{
            player_cs_state++;
            player_c_counter = 60;
            SpriteManagerAdd(SpriteExplosionCuts, THIS->x - 8, THIS->y - 8);
            SetSpriteAnim(THIS, pcs_cape_stand, 15);
            PlayMusic(unlinkedchainedsoul, 1);
           
        }
        break;
    case 3:
        if(--player_c_counter == 0){
            player_cs_state++;
            SetSpriteAnim(THIS, pcs_cape_walk, 15);
        }
        break;
    case 4:
        THIS->x++;
        if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_c_canDo == 0){
            player_c_canDo = 1;
            PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
        }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_c_canDo == 1){
            player_c_canDo = 0;
        }
        if(THIS->x == 158){
            current_level++;
            SetState(current_state);
        }
        break;
    }
}

void DESTROY()
{
}