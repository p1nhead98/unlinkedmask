#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    data->state = 0;
    THIS->mirror = NM_PRIOR;
}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    if(data->state == 0){
        THIS->x+=4;
        if(THIS->x > 138){
            THIS->y+=17;
            THIS->x = 40;
            data->state++;
        }
    }else if(data->state == 1){
        THIS->x+=4;
        if(THIS->x > 104){
            SpriteManagerRemove(THIS_IDX);
        }
    }
    
}

void DESTROY()
{
}