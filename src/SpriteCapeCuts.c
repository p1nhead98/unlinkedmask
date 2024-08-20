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

const UINT8 cape_cut_anim[] = {8, 0, 1, 2, 3, 4, 5, 6, 7};

void START()
{
     SetSpriteAnim(THIS, cape_cut_anim, 7);

}

void UPDATE()
{
    switch (THIS->anim_frame)
    {
    case 0:
        THIS->y = 120;
        THIS->x = 8;
        break;
    case 1:
        THIS->y = 50;
        THIS->x = 8;
        break;
    
    default:
        break;
    }
     
}

void DESTROY()
{
}