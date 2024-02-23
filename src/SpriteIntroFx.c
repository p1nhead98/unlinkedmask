#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 intro_fx_anim[] = {2, 0, 1};

void START()
{
    SetSpriteAnim(THIS, intro_fx_anim, 13);
 
}

void UPDATE()
{
    if(THIS->anim_frame == 1){
        SpriteManagerRemove(THIS_IDX);
    }
}

void DESTROY()
{
}