#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 windenem_anim[] = {4, 1,0,1,2};

void START()
{

    SetSpriteAnim(THIS, windenem_anim, 20);

}

void UPDATE()
{
   THIS->x-=1;

}

void DESTROY()
{
}