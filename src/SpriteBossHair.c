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

const UINT8 hairboss[] = {3, 0, 1, 2};

void START()
{
     SetSpriteAnim(THIS, hairboss, 16);

}

void UPDATE()
{

     
}

void DESTROY()
{
}