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

void crusherLeftSound(){
    PlayFx(CHANNEL_1, 15, 0x34, 0xbf, 0xf1, 0xee, 0x82);
    PlayFx(CHANNEL_4, 15, 0x3b, 0xf1, 0x30, 0x80);
}

void crusherLeftCSound(){
    PlayFx(CHANNEL_4, 60, 0x3F, 0xF5, 0xA8, 0x80);
}

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    
    data->state = 0;
    data->counter = 50;
    data->accel_y = 0;
    THIS->lim_x = 400;
    THIS->lim_y = 80;
    THIS->x += 7;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    if(THIS->x > 864 && current_level == 1 && current_state == StateStage4){
        data->initial_y = THIS->y = 80;
        data->initial_x = THIS->x = 976;
    }else if(THIS->x < 152 && current_level == 2 && current_state == StateStage4 ){
    
        
         data->initial_y = THIS->y -= 8;
         data->initial_x = THIS->x += 72;
    }else if(current_level == 3){
    
        data->initial_x = THIS->x = 1056;
        data->initial_y = THIS->y = 136;
        THIS->lim_x = 400;
        THIS->lim_y = 80;
    }
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
   

    switch(data->state){
        case 0:
            if( current_level == 1 && current_state == StateStage4 ){
                if(THIS->x > 864){
                    if( ((scroll_target->x > 864) && (scroll_target->x <  (THIS->x + 3)))  ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                    }
                }
               
            }else if(current_level == 2 && current_state == StateStage4){
                 if( scroll_target->x > 56 &&  scroll_target->y > 112 && (scroll_target->x <  (THIS->x))  ){
                        data->state = 1;
                        crusherLeftSound();
                        SetSpriteAnim(THIS, crusher_l_blink, 20);
                }
            }else if(current_level == 3){
               
                if( ((scroll_target->x > 872 && scroll_target->x < 1024) && (scroll_target->x <  (THIS->x))) && scroll_target->y > 105  ){
                    data->state = 1;
                    crusherLeftSound();
                    SetSpriteAnim(THIS, crusher_l_blink, 20);
                }
                
                
            }
            
        
            
        break;
        case 1:
        // if(current_level == 28 && THIS->x > 520 && THIS->x < 656){
        //     if(TranslateSprite(THIS, 4 << delta_time, 0)){
        //         crusherLeftCSound();
        //         data->state = 2;
        //         data->counter = 50;
        //     }
        // }else if(THIS->x < 145 && current_level == 29){
        //     if(TranslateSprite(THIS, 4 << delta_time, 0)){
        //         crusherLeftCSound();
        //         data->state = 2;
        //         data->counter = 50;
        //     }
        // }else if (THIS->x < 703 && current_level == 30) {
        //     if(TranslateSprite(THIS, 4 << delta_time, 0)){
        //         crusherLeftCSound();
        //         data->state = 2;
        //         data->counter = 50;
        //     }
        // }else if (THIS->x > 703 && current_level == 30) {
        //     if(TranslateSprite(THIS, -4 << delta_time, 0)){
        //         crusherLeftCSound();
        //         data->state = 2;
        //         data->counter = 10;
        //     }
        // }else{
            if(TranslateSprite(THIS, -4 << delta_time , 0)){
                crusherLeftCSound();
                data->state = 2;
                data->counter = 50;
            // }
        }
            
        break;
        case 2:
            if(--data->counter == 0){
                data->state = 3;
            }
        break;
        case 3:
            // if(current_level == 28 && THIS->x > 520 && THIS->x < 656){
            //     if(THIS->x > data->initial_x){
            //         TranslateSprite(THIS, -1 << delta_time, 0);
            //     }else{
            //         data->state = 0;
            //         SetSpriteAnim(THIS, crusher_l_idle, 20);
            //     }
            // }else if(THIS->x < 145 && current_level == 29){
            //     if(THIS->x > data->initial_x){
            //         TranslateSprite(THIS, -1 << delta_time, 0);
            //     }else{
            //         data->state = 0;
            //         SetSpriteAnim(THIS, crusher_l_idle, 20);
            //     }
            // }else if(current_level == 30){
            //     if(THIS->x < 704){
            //         if(THIS->x > data->initial_x){
            //             TranslateSprite(THIS, -1 << delta_time, 0);
            //         }else{
            //             data->state = 0;
            //             SetSpriteAnim(THIS, crusher_l_idle, 20);
            //         }
            //     }else if(THIS->x > 704){
            //         if(THIS->x < data->initial_x){
            //             TranslateSprite(THIS, 1 << delta_time, 0);
            //         }else{
            //             data->state = 0;
            //             SetSpriteAnim(THIS, crusher_l_idle, 20);
            //         }
            //     }
            // }else{
                if(THIS->x < data->initial_x){
                    TranslateSprite(THIS, 1 << delta_time, 0);
                }else{
                    data->state = 0;
                    SetSpriteAnim(THIS, crusher_l_idle, 20);
                }
            // }
        break;
    }
}

void DESTROY()
{
}