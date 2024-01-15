#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "ZGBMain.h"


const UINT8 player_vfx_anim[] = {3, 0, 1, 2};




void START()
{
    SetSpriteAnim(THIS, player_vfx_anim, 30); 
}

void UPDATE()
{  
    if(THIS->anim_frame == 2){
        SpriteManagerRemove(THIS_IDX);
    }


}

void DESTROY()
{
}