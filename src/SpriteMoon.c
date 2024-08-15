#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Palette.h"
#include "Math.h"
#include "Scroll.h"
#include "ZGBMain.h"

const UINT8 moon_anim[] = {1, 0};
const UINT8 moon_anim_1[] = {1, 1};
const UINT8 moon_anim_2[] = {1, 2};

extern INT8 map_width;
extern UINT8 current_level;

void HideMoon(){
    if(current_state == StateStage2){
        if(current_level == 0){
            if((THIS->x > 232 && THIS->x < 328) || (THIS->x > 392 && THIS->x < 552) || (THIS->x > 824)){
                THIS->y = 32;
            }else{
                THIS->y = 64;
            }
        }else if(current_level == 1){
            if((THIS->x < 24) || (THIS->x > 160 && THIS->x < 280) || (THIS->x > 466 && THIS->x < 536) || (THIS->x > 592 && THIS->x < 720) || (THIS->x > 752 && THIS->x < 824) ){
                THIS->y = 32;
            }else{
                THIS->y = 64;
            }
        }else if(current_level == 2){
            if((THIS->x > 144 && THIS->x < 248) || (THIS->x > 576 && THIS->x < 712) || (THIS->x > 848 && THIS->x < 872)  ){
                THIS->y = 32;
            }else{
                THIS->y = 64;
            }
        }else if(current_level == 3){
            if((THIS->x > 64 && THIS->x < 168) || (THIS->x > 224 && THIS->x < 280) || (THIS->x > 320 && THIS->x < 376) || (THIS->x > 400 && THIS->x < 616) || (THIS->x > 736 && THIS->x < 904)){
                THIS->y = 32;
            }else{
                THIS->y = 64;
            }
        }else if(current_level == 4){
            if((THIS->x > 112 && THIS->x < 248) || (THIS->x > 320 && THIS->x < 384) || (THIS->x > 400 && THIS->x < 440) || (THIS->x > 456 && THIS->x < 520) || (THIS->x > 560 && THIS->x < 616) || (THIS->x > 624 && THIS->x < 672) || (THIS->x > 688 && THIS->x < 776) || (THIS->x > 800 && THIS->x < 856) ){
                THIS->y = 32;
            }else{
                THIS->y = 64;
            }
        }
    }
}
void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    THIS->mirror =  NM_PRIOR;
    data->state = 0;
 

}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    switch (data->state)
    {
        case 0:
            SetSpriteAnim(THIS, moon_anim, 0);
            if(current_state == StateStage1){
                THIS-> x = scroll_x + 96;
            }else{
                if(scroll_target->x > 80){
                    if(scroll_target->x < (scroll_x + 88)){
                        THIS-> x = scroll_x + (152 - (((scroll_target->x - 80) / map_width) * 2) );
                    }
                }else{
                    THIS-> x = scroll_x + 152;
                }
            }
            break;
        
        case 1:
            SetSpriteAnim(THIS, moon_anim_1, 0);
            // THIS->mirror =  VM_PRIOR;
            if(current_state == StateStage1){
                THIS-> x = scroll_x + 96;
            }else{
                if(scroll_target->x > 80){
                    if(scroll_target->x < (scroll_x + 88)){
                        THIS-> x = scroll_x + (160 - (((scroll_target->x - 80) / map_width) * 2) );
                    }
                }else{
                     THIS-> x = scroll_x + 160;
                }
            }
            break;
        case 2:
            SetSpriteAnim(THIS, moon_anim_2, 0);
            THIS-> x = scroll_x + 92;
            break;
    }
    HideMoon();
}

void DESTROY()
{
}