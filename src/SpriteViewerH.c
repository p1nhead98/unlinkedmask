#include "Banks/SetAutoBank.h"
#include "SpriteManager.h"
#include "Scroll.h"



const UINT8 vw_hair_cs[] = {3, 0, 1, 2};

void START()
{
    SetSpriteAnim(THIS, vw_hair_cs, 13);
    // scroll_offset_y -= 20;
    // MoveScroll(0, 38);
}

void UPDATE()
{
//    TranslateSprite(THIS, 0, 1);
    
}

void DESTROY()
{
}