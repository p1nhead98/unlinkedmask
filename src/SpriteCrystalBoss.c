#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

const UINT8 crystal_boss_idle[] = {3, 0, 1, 2};
const UINT8 crystal_boss_walk[] = {3, 0, 1, 2};
const UINT8 crystal_boss_jump[] = {2, 3, 4};
const UINT8 crystal_boss_fall[] = {2, 5, 6};
const UINT8 crystal_boss_land[] = {4, 7, 7, 7, 7};
UINT8 cryst_boss_state = 0;
UINT8 cryst_boss_counter = 0;

INT16 cryst_boss_accel_y = 0;
UINT8 cryst_boss_x_initial_pos = 0;
UINT8 cryst_boss_fx = 0;
UINT8 player_last_x;
extern Sprite* player_sprite;

void START()
{
    SetSpriteAnim(THIS, crystal_boss_idle, 20);
    cryst_boss_state = 0;
    cryst_boss_counter = 0;
}

void UPDATE()
{
  switch (cryst_boss_state)
  {
    case 0:
        if(player_sprite->x > THIS->x){
            THIS->mirror = V_MIRROR;
        }else{
            THIS->mirror = NO_MIRROR;
        }
        if(THIS->anim_frame == 2){
            cryst_boss_counter++;
            if(cryst_boss_counter > 5){
                cryst_boss_counter = 0;
                cryst_boss_state = 1; 
                SetSpriteAnim(THIS, crystal_boss_walk, 15);
            }
        }
        
    break;
    case 1:
        if(THIS->mirror == NO_MIRROR){
            TranslateSprite(THIS, THIS->x > 17 ? -1 : 0, 0);
        }else{
            TranslateSprite(THIS, THIS->x < 136 ? 1 : 0, 0);
        }
        if(THIS->anim_frame == 2){
            cryst_boss_counter++;
            if(cryst_boss_counter > 2){
                cryst_boss_counter = 0;
                cryst_boss_state++;
                player_last_x = player_sprite->x;
                SetSpriteAnim(THIS, crystal_boss_jump, 20);
            }
        }
        
    break;
    case 2:

        if (cryst_boss_accel_y > -60)
        {
            cryst_boss_accel_y -= 2;
        }
        if(!U_LESS_THAN(DISTANCE(player_last_x, THIS->x + 9), 10)){
            if(THIS->x < player_last_x){
                THIS->x+=3;
            }else{
                THIS->x-=3;
            }
        }
        
        
     
        //THIS->y -=  (cryst_boss_accel_y >> 4) ;
        if(THIS->y > 58 ){
            TranslateSprite(THIS, 0, (cryst_boss_accel_y >> (4 << delta_time)));
        }
        
        if( U_LESS_THAN(DISTANCE(player_last_x, THIS->x + 9), 10) && THIS->y < 59  ){
            cryst_boss_state++;
            SetSpriteAnim(THIS, crystal_boss_fall, 20);
            SPRITE_SET_DMG_PALETTE(THIS, 1);
        }
        
    break;
    case 3:
        if(THIS->anim_frame == 1){
            cryst_boss_counter++;
            if(cryst_boss_counter > 2){
                SPRITE_SET_DMG_PALETTE(THIS, 0);
            }else if(cryst_boss_counter > 3){
                SPRITE_SET_DMG_PALETTE(THIS, 1);
            }else if(cryst_boss_counter > 5){
                SPRITE_SET_DMG_PALETTE(THIS, 0);
            }
            if(cryst_boss_counter > 10){
                cryst_boss_counter = 0;
                cryst_boss_state++;
            }
        }
        break;
    case 4:
        if(TranslateSprite(THIS, 0, 8)){
            cryst_boss_state++;
            ScreenShake(1,1);
            
            Sprite* crystal1 = SpriteManagerAdd(SpriteCrystalAttack, THIS->x, THIS->y + 9);
            CUSTOM_DATA_BTN* crystal1Data = (CUSTOM_DATA_BTN*)crystal1->custom_data;
            crystal1Data->state = 2;
            Sprite* crystal2 = SpriteManagerAdd(SpriteCrystalAttack, THIS->x, THIS->y + 9);
            CUSTOM_DATA_BTN* crystal2Data = (CUSTOM_DATA_BTN*)crystal2->custom_data;
            crystal2Data->state = 1;

            SetSpriteAnim(THIS, crystal_boss_land, 10);
            SPRITE_SET_DMG_PALETTE(THIS, 1);

        }
        
        break;
    case 5:
        if(THIS->anim_frame > 0){
            SPRITE_SET_DMG_PALETTE(THIS, 0);    
        }
    
        if(THIS->anim_frame == 3){
            SetSpriteAnim(THIS, crystal_boss_idle, 20);
            cryst_boss_state = 0;
            cryst_boss_counter = 0;
        }
        break;

  }
   

}

void DESTROY()
{
}