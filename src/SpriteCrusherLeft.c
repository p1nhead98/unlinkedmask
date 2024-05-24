#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 crusher_l_blink[] = {2, 0, 1};
const UINT8 crusher_l_idle[] = {1, 0};
extern UINT8 current_level;
void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    data->state = 0;
    data->counter = 50;
    data->accel_y = 0;
    THIS->lim_x = 200;
    THIS->lim_y = 80;
    THIS->x += 7;
    if(THIS->x < 488 && current_level == 27){
        data->initial_x = THIS->x = 504;
    }else if (THIS->x > 520 && current_level == 27){
        THIS->mirror = V_MIRROR;
    }else if(THIS->x < 104 && current_level == 28){
        THIS->mirror = V_MIRROR;
    }else if(THIS->x > 105 && THIS->x < 960 && current_level == 28){
        data->initial_x = THIS->x = 272;
    }
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
    
            if(current_level == 26){
                if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 95))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_l_blink, 20);
                }
            }else if (current_level == 27){
                if(THIS->x < 513){
                    if(  ((THIS->y + 5) > scroll_target->y) && (THIS->x > scroll_target->x)  ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else if (THIS->x > 936 && THIS->x < 1048){
                    if( (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 95)) ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else{
                    if(  ((THIS->y + 5) > scroll_target->y) && (THIS->x + 15 < scroll_target->x) ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }
            }else if( current_level == 28 ){
                if(THIS->x < 145){
                    if(  (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 38)) && ((THIS->y - 24 ) < scroll_target->y ) ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else if(THIS->x > 960){
                    if( ((scroll_target->x > 864) && (scroll_target->x <  (THIS->x + 3)))  ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }else{
                    if( ((scroll_target->x > 128) && (scroll_target->x <  (THIS->x + 3))) && ((THIS->y - 40 ) < scroll_target->y ) ){
                        data->state = 1;
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }
               
            }
            
        
            
        break;
        case 1:
        if(current_level == 27 && THIS->x > 520 && THIS->x < 656){
            if(TranslateSprite(THIS, 4, 0)){
                data->state = 2;
                data->counter = 50;
            }
        }else if(THIS->x < 145 && current_level == 28){
            if(TranslateSprite(THIS, 4, 0)){
                data->state = 2;
                data->counter = 50;
            }
        }else{
            if(TranslateSprite(THIS, -4, 0)){
                data->state = 2;
                data->counter = 50;
            }
        }
            
        break;
        case 2:
            if(--data->counter == 0){
                data->state = 3;
            }
        break;
        case 3:
            if(current_level == 27 && THIS->x > 520 && THIS->x < 656){
                if(THIS->x > data->initial_x){
                    TranslateSprite(THIS, -1, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }else if(THIS->x < 145 && current_level == 28){
                if(THIS->x > data->initial_x){
                    TranslateSprite(THIS, -1, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }else{
                if(THIS->x < data->initial_x){
                    TranslateSprite(THIS, 1, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            }
        break;
    }
}

void DESTROY()
{
}