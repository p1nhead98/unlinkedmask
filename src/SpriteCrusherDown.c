#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


const UINT8 crusher_blink[] = {2, 0, 1};
const UINT8 crusher_idle[] = {1, 0};
extern UINT8 current_level;

void crusherDownSound(){
    PlayFx(CHANNEL_1, 15, 0x34, 0xbf, 0xf1, 0xee, 0x82);
    PlayFx(CHANNEL_4, 15, 0x3b, 0xf1, 0x30, 0x80);
}

void crusherDownCSound(){
    PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
}
void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    data->state = 0;
    data->counter = 50;
    data->accel_y = 0;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    THIS->x += 7;
    data->state = 0;

    if(current_state == StateStage4){
        if(current_level == 0){
            if(THIS->x > 704 && THIS->x < 808){
                THIS->x += 8;
            }
        }else if(current_level == 2){
            if(THIS->x > 1176){
                THIS->mirror = H_MIRROR;
            }else if(THIS->x > 704 && THIS->x < 768){
                THIS->y -= 8;
            }
        }
    }



    if(current_level == 29){
        if(THIS->x > 768 && THIS->x < 840){
            THIS->y -= 24;
        }else if(THIS->x > 1080 && THIS->x < 1136){
            THIS->y -= 8;
            THIS->x += 8;
        }else if(THIS->x > 1136 && THIS->x < 1192){
            THIS->x += 8;
            THIS->lim_y = 150;
            THIS->y -= 16;
        }else if(THIS->x > 1192){
            THIS->y+=32;
        }
    }else if(current_level == 27){
        if(THIS->x > 128 && THIS->x < 200){
            THIS->mirror = H_MIRROR;
        }
    }
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
        if(current_level == 2 ){
            if(THIS->x < 392){
                if( (scroll_target->x > 308 && scroll_target->x < 352 ) ){
                    data->state = 1;
                    crusherDownSound();
                    SetSpriteAnim(THIS, crusher_blink, 20);
                
                }
            }else if(THIS->x > 608 && THIS->x < 688){
                if( (scroll_target->x > 624 && scroll_target->x < 650 ) ){
                    data->state = 1;
                    crusherDownSound();
                    SetSpriteAnim(THIS, crusher_blink, 20);
                
                }
            }else if(THIS->x > 688 && THIS->x < 832){
                if( ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 35))  ){
                    data->state = 1;
                    crusherDownSound();
                    SetSpriteAnim(THIS, crusher_blink, 20);
                
                }
            }else if(THIS->x > 1176){
                if(scroll_target->x > 1184 && scroll_target->x < (THIS->x + 24)){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                    crusherDownSound();
                }
            }else{
                if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 55))  ){
                    data->state = 1;
                    SetSpriteAnim(THIS, crusher_blink, 20);
                    crusherDownSound();
                }
            }

        }else{
            if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 55))  ){
                data->state = 1;
                SetSpriteAnim(THIS, crusher_blink, 20);
                crusherDownSound();
            }
        
        }
       


        // if(current_level == 27 && THIS->x > 128 && THIS->x < 200){
        //         if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 40))  ){
        //             data->state = 1;
        //             crusherDownSound();
        //             SetSpriteAnim(THIS, crusher_blink, 20);
        //         }
        // }else if(current_level == 27 && THIS->x > 288 && THIS->x < 320){
        //     if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 80))  ){
        //         data->state = 1;
        //         crusherDownSound();
        //         SetSpriteAnim(THIS, crusher_blink, 20);
        //     }
        // }else if(current_level == 29){
        //     if(THIS->x < 384){
        //         if(  ((THIS->y + 5) < scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 34))  ){
        //             data->state = 1;
        //             crusherDownSound();
        //             SetSpriteAnim(THIS, crusher_blink, 20);
        //         }
        //     }else if(THIS->x > 1192){
        //        if(  ((THIS->y + 5) > scroll_target->y) && (U_LESS_THAN(DISTANCE(scroll_target->x, THIS->x + 16), 35))  ){
        //             data->state = 1;
        //             crusherDownSound();
        //             SetSpriteAnim(THIS, crusher_blink, 20);
        //         } 
        //     }

        // }else{
      
            
        break;
        case 1:
        // if(current_level == 29){
        //     if(THIS->x > 1192){
        //         if(TranslateSprite(THIS, 0, -4 << delta_time)){
        //             PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
        //             data->state = 2;
        //             data->counter = 50;
        //         }
        //     }else{
        //         if(TranslateSprite(THIS, 0, 4 << delta_time)){
        //             PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
        //             data->state = 2;
        //             data->counter = 50;
        //         } 
        //     }
        // }else if(current_level == 27 && THIS->x > 128 && THIS->x < 200){
          
        //     if(TranslateSprite(THIS, 0, -4 << delta_time)){
        //         PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
        //         data->state = 2;
        //         data->counter = 50;
        //     }




        if(current_level == 2){
            if(THIS->x > 1176){
                if(TranslateSprite(THIS, 0, -4 << delta_time)){
                    PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
                    data->state = 2;
                    data->counter = 50;
                }
            }else{
                if(TranslateSprite(THIS, 0, 4 << delta_time)){
                    PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
                    data->state = 2;
                    data->counter = 50;
                }  
            }
        }else{ 
            if(TranslateSprite(THIS, 0, 4 << delta_time)){
                PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
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
            if(THIS->y > data->initial_y){
                TranslateSprite(THIS, 0, -1);
            }else{
                data->state = 0;
                SetSpriteAnim(THIS, crusher_idle, 20);
            }
        break;
    }
}

void DESTROY()
{
}