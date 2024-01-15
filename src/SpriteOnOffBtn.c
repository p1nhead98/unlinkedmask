#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 on_anim[] = {2, 0, 0};
const UINT8 off_anim[] = {2, 1, 1};

extern UINT8 on_off;
extern UINT8 collision_tiles2[];

void START()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    if(on_off == 0){
        SetSpriteAnim(THIS, on_anim, 20);
    }else{
        SetSpriteAnim(THIS, off_anim, 20);
    }
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA_BOX* data = (CUSTOM_DATA_BOX*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;
    switch(data->state){
        case 1:
            if(on_off == 0){
                on_off = 1;
                SetSpriteAnim(THIS, off_anim, 15);
                THIS->y -= 5;
                data->state++;
                SetOnOffCols(collision_tiles2, on_off);
            }else{
                on_off = 0;
                SetSpriteAnim(THIS, on_anim, 15);
                THIS->y -= 5;
                data->state++;
                SetOnOffCols(collision_tiles2, on_off);
            }
        break;
        case 2:
            if(THIS->anim_frame == 1){
                THIS->y += 5;
                data->state = 0;
            }
        break;
    }

}

void DESTROY()
{
}