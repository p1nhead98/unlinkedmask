#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern UINT8 door_time;
extern UINT8 door_open;
extern INT16 scroller_y;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    data->state = 0;
    if(THIS->x > 100){
        THIS->mirror = V_MIRROR;
    }
}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    switch (data->state)
    {
        case 0:
            THIS->y = scroller_y + 80;
            if(scroller_y == 1){
                data->state++;
            }
            break;
        case 1:
            THIS->y--;
            break;

    }
}

void DESTROY()
{
}