#include "Banks/SetAutoBank.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Palette.h"
#include "ZGBMain.h"

const UINT8 bp_anim[] = {2, 0, 1};

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->state = 0;
    data->accel_y = -10;
    SetSpriteAnim(THIS, bp_anim, 20);
}

void UPDATE()
{ 
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;

   
             if(THIS->anim_frame == 1){
                SpriteManagerRemove(THIS_IDX);
            }


        if (data->accel_y < 20)
        {
            data->accel_y += 1;
        }

       
    //    THIS->y = THIS->y + data->accel_y >> (-4 << delta_time);
       THIS->y = THIS->y + (data->accel_y >> 4);
       if( data->state == 0){
        THIS->x++;
       }else{
        THIS->x--;
       }
    
}

void DESTROY()
{
}










