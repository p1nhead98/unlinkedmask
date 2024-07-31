#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 elec_boss_idle[] = {3, 0, 1, 2};
const UINT8 elec_boss_dash[] = {4, 3, 4, 3, 4};
const UINT8 elec_boss_teleport[] = {3, 7, 8, 8};
const UINT8 elec_boss_teleport2[] = {5, 8, 8, 7, 7, 7};
const UINT8 elec_boss_stop[] = {4, 5, 6, 5, 6};
const UINT8 elec_boss_stop2[] = {2, 5, 6};
UINT8 elec_boss_state = 0;
UINT8 elec_boss_counter = 0;

UINT8 elec_boss_dash_speed = 0;
UINT8 elec_boss_x_initial_pos = 0;
UINT8 elec_boss_fx = 0;

void START()
{

    elec_boss_state = 0;
    elec_boss_dash_speed = 2;
    elec_boss_x_initial_pos = THIS->x;
    elec_boss_fx = 0;
    elec_boss_counter = 0;
    SetSpriteAnim(THIS, elec_boss_idle, 20);

}

void UPDATE()
{
  
    switch (elec_boss_state)
    {
    case 0:
        if(THIS->anim_frame == 2){
            elec_boss_counter++;
        }
        if(elec_boss_counter == 40){
            elec_boss_state = 1;
            SetSpriteAnim(THIS, elec_boss_dash, 20);
        }
        break;
    case 1:
        THIS->x += elec_boss_dash_speed;
        if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && elec_boss_fx == 0){
            elec_boss_fx = 1;
            SpriteManagerAdd(SpriteElectBossFx, THIS->x + 28, THIS->y+ 16);
        }
        if(THIS->anim_frame == 0 || THIS->anim_frame == 2){
            elec_boss_fx = 0;
        }
        if(elec_boss_dash_speed < 6){
            if(THIS->x > 128){
                elec_boss_state++;
                SetSpriteAnim(THIS, elec_boss_teleport, 12);
            }
        }else{
            if(THIS->x > 80){
                elec_boss_state = 4;
                elec_boss_dash_speed = 1;
                SetSpriteAnim(THIS, elec_boss_stop, 20);
                elec_boss_fx = 0;
            }

        }

        break;
    case 2:
        if(THIS->anim_frame == 2){
            elec_boss_state++;
            THIS->x = elec_boss_x_initial_pos;
            SetSpriteAnim(THIS, elec_boss_teleport2, 20);
        }
        break;
    case 3:
        if(THIS->anim_frame == 4){
            elec_boss_state = 1;
            SetSpriteAnim(THIS, elec_boss_dash, 20);
            elec_boss_dash_speed++;
        }
        break;
    case 4:
        THIS->x += elec_boss_dash_speed;
        if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && elec_boss_fx == 0){
            elec_boss_fx = 1;
            // SpriteManagerAdd(SpriteElectBossFx, THIS->x, THIS->y+ 16);
        }
        if(THIS->anim_frame == 0 || THIS->anim_frame == 2){
            elec_boss_fx = 0;
        }
        if(THIS->x > 128){
            elec_boss_state++;
            elec_boss_counter = 0;
            SetSpriteAnim(THIS, elec_boss_stop2, 20);
            // SetSpriteAnim(THIS, elec_boss_teleport, 9);
        }
        break;
    case 5:
        if(THIS->anim_frame == 1){
            elec_boss_counter++;
        }
        if(elec_boss_counter == 40){
            elec_boss_state = 0;
            elec_boss_dash_speed = 2;
            elec_boss_counter = 0;
            THIS->x = elec_boss_x_initial_pos;
            SetSpriteAnim(THIS, elec_boss_idle, 20);
        }
      
        break;
    }

}

void DESTROY()
{
}