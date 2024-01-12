#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 anim_box[] = {2, 0, 1};
const UINT8 anim_box2[] = {2, 2, 2};
void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->initial_x = THIS->x;
    data->initial_y = THIS->y;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    data->state = 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    CUSTOM_DATA* playerData = (CUSTOM_DATA*)scroll_target->custom_data;
    UINT8 i;
	Sprite* spr;

     switch( data->state ){
        case 0:
            SetSpriteAnim(THIS, anim_box, 20);
        break;
        case 1:
       
                SetSpriteAnim(THIS, anim_box2, 2);
            if(THIS->anim_frame == 1){
                data->state = 0;
                SetSpriteAnim(THIS, anim_box, 20);
             
            }
        break;
     }

}

void DESTROY()
{
}