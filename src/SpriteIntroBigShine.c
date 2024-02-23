#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 big_shine_anim[] = {3, 0, 1, 2};
UINT8 canPutShine = 0;
void START()
{
    SetSpriteAnim(THIS, big_shine_anim, 13);
    canPutShine = 0;
}

void UPDATE()
{
    if(THIS->anim_frame == 1 && canPutShine == 0){
        
        Sprite* mShine = SpriteManagerAdd(SpriteIntroMiniShine, THIS->x - 4, THIS->y - 4);
        CUSTOM_DATA_BTN* mShinedata = (CUSTOM_DATA_BTN*)mShine->custom_data; 
        mShinedata->state= 0;

        Sprite* mShine2 = SpriteManagerAdd(SpriteIntroMiniShine, THIS->x - 4, THIS->y + 12);
        CUSTOM_DATA_BTN* mShinedata2 = (CUSTOM_DATA_BTN*)mShine2->custom_data; 
        mShinedata2->state= 1;


        Sprite* mShine3 = SpriteManagerAdd(SpriteIntroMiniShine, THIS->x + 12, THIS->y - 4);
        CUSTOM_DATA_BTN* mShinedata3 = (CUSTOM_DATA_BTN*)mShine3->custom_data; 
        mShinedata3->state= 2;


        Sprite* mShine4 =  SpriteManagerAdd(SpriteIntroMiniShine, THIS->x + 12, THIS->y + 12);
        CUSTOM_DATA_BTN* mShinedata4 = (CUSTOM_DATA_BTN*)mShine4->custom_data; 
        mShinedata4->state= 3;   
       
        canPutShine = 1;
    }
    if(THIS->anim_frame == 2){
        SpriteManagerRemove(THIS_IDX);
    }
}

void DESTROY()
{
}