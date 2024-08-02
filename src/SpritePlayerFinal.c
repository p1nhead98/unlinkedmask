#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 pl_final_anim[] = {3, 0, 1, 2};

void START()
{
    SetSpriteAnim(THIS, pl_final_anim, 15);
 
}

void UPDATE()
{

}

void DESTROY()
{
}