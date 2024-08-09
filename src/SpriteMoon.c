#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Palette.h"
#include "Math.h"
#include "Scroll.h"
#include "ZGBMain.h"



void START()
{

THIS->mirror =  NM_PRIOR;
}

void UPDATE()
{
    THIS-> x = scroll_x + 96;
     
}

void DESTROY()
{
}