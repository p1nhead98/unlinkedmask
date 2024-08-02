#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "ZGBMain.h"
#include "Misc.h"


const UINT8 player_death_anim[] = {3, 0, 1, 1 };

UINT8 player_d_start = 0;
INT16 player_d_initial_y = 0;
INT16 player_d_init_framespeed = 0;

extern UINT8 start_screen;
extern UINT8 deaths_u_count;
extern UINT8 deaths_d_count;
UINT8 pdeath_counter = 0;
UINT8 pdeath_counter2 = 0;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;   

    data->state = 0;
    SetSpriteAnim(THIS, player_death_anim, 20);
    player_d_start = 1;
    player_d_initial_y = 0;
    player_d_init_framespeed = 0;
    pdeath_counter = 0;
    pdeath_counter2 = 0;
}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;   
    if(start_screen == 0){

        if(player_d_start == 0){
            player_d_start = 1;
            THIS->y = player_d_initial_y;
            THIS->anim_speed = player_d_init_framespeed;
        }

        if(THIS->anim_frame == 2){
            SpriteManagerRemove(THIS_IDX);
            // SetState(current_state);
            data->state = 1;
            if(deaths_u_count != 99){
                deaths_u_count++;
            }else{
                if(deaths_d_count != 9){
                    deaths_u_count = 0;
                    deaths_d_count++;
                }
            }
        }
        if(pdeath_counter == 0){
            pdeath_counter = 1;
            pdeath_counter2 = 60;
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