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
extern UINT8 door_button;

const UINT8 time_door[] = {4, 0, 1, 2, 3};

void START()
{

    SetSpriteAnim(THIS, time_door, 15);
}

void UPDATE()
{
    if(THIS->anim_frame == 2){
        door_button = 1;
    }
    if(THIS->anim_frame == 3){
        SpriteManagerRemove(THIS_IDX);
    }
 
}

void DESTROY()
{
}