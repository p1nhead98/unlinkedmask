#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "ZGBMain.h"


const UINT8 player_death_anim[] = {3, 0, 1, 1 };




void START()
{
    SetSpriteAnim(THIS, player_death_anim, 20);
}

void UPDATE()
{

    if(THIS->anim_frame == 2){
        SpriteManagerRemove(THIS_IDX);
        SetState(current_state);
    }

}

void DESTROY()
{
}