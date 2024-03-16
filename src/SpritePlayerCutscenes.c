#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

// const UINT8 anim_box[] = {2, 0, 1};
// const UINT8 anim_box2[] = {2, 2, 2};
const UINT8 pcs_walk_anim[] = {4, 1, 2, 0, 3};
const UINT8 pcs_stand[] = {2, 4, 5};
UINT8 player_cs_state = 0;
extern UINT8 start_screen;

void START()
{
    player_cs_state = 1;
    SetSpriteAnim(THIS, pcs_stand, 15);
    THIS->x -= 8;
}

void UPDATE()
{
    switch (player_cs_state)
    {
    case 0:
        if(THIS->x != 72){
            THIS->x++;
        }else{
            player_cs_state++;
            SetSpriteAnim(THIS, pcs_stand, 15);
        }
        break;
    

    }
}

void DESTROY()
{
}