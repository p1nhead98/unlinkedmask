#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 elec_boss_fx_anim[] = {3, 0, 1, 1};

void START()
{
    SetSpriteAnim(THIS, elec_boss_fx_anim, 20);

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