#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 cuts_fx_explosion[] = {7, 0, 1, 2, 3, 4, 5, 6};

void START()
{
    SetSpriteAnim(THIS, cuts_fx_explosion, 13);
 
}

void UPDATE()
{
    if(THIS->anim_frame == 6){
        SpriteManagerRemove(THIS_IDX);
    }
}

void DESTROY()
{
}