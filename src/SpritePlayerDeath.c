#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "ZGBMain.h"


const UINT8 player_death_anim[] = {3, 0, 1, 1 };

UINT8 player_d_start = 0;
INT16 player_d_initial_y = 0;
INT16 player_d_init_framespeed = 0;

extern UINT8 start_screen;

void START()
{
    SetSpriteAnim(THIS, player_death_anim, 20);
    player_d_start = 1;
    player_d_initial_y = 0;
    player_d_init_framespeed = 0;
}

void UPDATE()
{
    if(start_screen == 0){

        if(player_d_start == 0){
            player_d_start = 1;
            THIS->y = player_d_initial_y;
            THIS->anim_speed = player_d_init_framespeed;
        }

        if(THIS->anim_frame == 2){
            SpriteManagerRemove(THIS_IDX);
            SetState(current_state);
        }

    }else{
       
        if(THIS->y != 0  && player_d_start == 1){
            player_d_start = 0;
            player_d_initial_y = THIS->y;
            THIS->y = 0;
            player_d_init_framespeed = THIS->anim_speed;
            THIS->anim_speed = 0;
        } 
    }
}

void DESTROY()
{
}