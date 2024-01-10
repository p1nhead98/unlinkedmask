#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "Scroll.h"
#include "ZGBMain.h"


const UINT8 anim_idle[] = {2, 0, 1};
const UINT8 anim_walk[] = {4, 2, 1, 3, 1};
const UINT8 anim_jump[] = {2, 4, 5};
const UINT8 anim_fall[] = {2, 6, 7};
const UINT8 anim_spin[] = {6, 8, 9, 10, 11, 12, 13};


extern INT16 inmunity;
extern INT8 pal_tick;
extern UINT8 current_pal;
extern UINT8 current_life;
extern UINT8 current_level;
BOOLEAN canHurt;

// void UpdateMapTile(INT16 map_x, INT16 map_y, UINT8 tile_id, UINT8 c) {
//        UPDATE_TILE(map_x, map_y, &tile_id, &c);
// }

void CheckCollisionTile(CUSTOM_DATA* data)
{
    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 12u) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 16u) >> 3);

    const UINT8 HEART_TILE4 = 132;

    if (colision == 113 || colision == 115)
    {
        if(canHurt){
            inmunity = 30;
            canHurt = 0;
            current_life--;
            ScreenShake(1,1);
            RefreshLife();
        }
        
        //SpriteManagerRemove(THIS_IDX);
    }
    if( colision2 == 108 || colision2 == 110 ){
        if((data->state == 2 || data->state == 3)){
            data->state = 3;
            data->accel_y = -80;
            SetSpriteAnim(THIS, anim_spin, 40);
        }
    }

    // if( colision2 == 104 || colision2 == 106 ){
    //     if((data->state == 1 || data->state == 4 )){
    //         data->state = 4;
    //         data->accel_y = -80;
    //         SetSpriteAnim(THIS, anim_jump, 40);
    //         UPDATE_TILE(13,15, HEART_TILE4 , 0);
    //         UPDATE_TILE(14,15, HEART_TILE4 , 0);
            
          
           
    //         // SpriteManagerAdd(SpriteTest, THIS->x - 3, THIS->y + 16);
    //     }
    // }
   

}



void START()
{

    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->state = 8;
    data->accel_y = 0;
    data->collision = 0;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    // data->direction = FALSE;
    // data->canDo = TRUE;
    data->counter = 2;
    data->accel_x = 0;
    THIS->x = -16;
    canHurt = inmunity < 1 ? 1 : 0;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    if (inmunity != 0)
    {
        inmunity -= (1 << delta_time);

        if (inmunity < 1)
        {
            inmunity = 0;
            pal_tick = 0; //This forces the palette to be 0 after after the next if
            current_pal = 1;
            canHurt = 1;
        }

        pal_tick -= 1 << delta_time;
        if (U_LESS_THAN(pal_tick, 0))
        {
            pal_tick += 3;
            current_pal++;
            SPRITE_SET_DMG_PALETTE(THIS, current_pal % 2);
        }
    }


    if(current_life < 1){
        SpriteManagerRemove(THIS_IDX);
        SetState(current_state);
    }
    if( (THIS->x >= scroll_x + 150) && data->state != 9 && data->state != 8){
        data->state = 9;
    }


    switch( data->state ){
        case 0:

            if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                TranslateSprite(THIS, -2, 0);
                SetSpriteAnim(THIS, anim_walk, 15);
                THIS->mirror = V_MIRROR;
            }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                TranslateSprite(THIS, 2, 0);
                SetSpriteAnim(THIS, anim_walk, 15);
                THIS->mirror = NO_MIRROR;
            }else if(!KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                SetSpriteAnim(THIS, anim_idle, 15);
            }
            if(KEY_TICKED(J_A)){
                data->state = 1;
                data->accel_y = -80;
                JumpRandSound(0);
                SetSpriteAnim(THIS, anim_jump, 15);
            }
            if(KEY_TICKED(J_B)){
                data->state = 2;
                data->accel_y = -80;
                JumpRandSound(1);
                SetSpriteAnim(THIS, anim_spin, 40);
            }
        break;
        case 1:
            if(!KEY_PRESSED(J_A) && data->accel_y < 0){
                data->accel_y = 0;
            }
            if (data->accel_y > 2)
            {
                SetSpriteAnim(THIS, anim_fall, 15);
            }
            if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                TranslateSprite(THIS, -2, 0);
                THIS->mirror = V_MIRROR;
                  
            }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                TranslateSprite(THIS, 2, 0);
                THIS->mirror = NO_MIRROR;
            }
        break;
       case 2:
            if(!KEY_PRESSED(J_B) && data->accel_y < 0){
                data->accel_y = 0;
            }
            
            if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                TranslateSprite(THIS, -2, 0);
                // THIS->mirror = V_MIRROR;
                  
            }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                TranslateSprite(THIS, 2, 0);
                // THIS->mirror = NO_MIRROR;
            }
        break;
        case 3:
            // if(!KEY_PRESSED(J_B) && data->accel_y < 0){
            //     data->accel_y = 0;
            // }
            
            if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                TranslateSprite(THIS, -2, 0);
                // THIS->mirror = V_MIRROR;
                  
            }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                TranslateSprite(THIS, 2, 0);
                // THIS->mirror = NO_MIRROR;
            }
        break;
        case 4:
            // if(!KEY_PRESSED(J_B) && data->accel_y < 0){
            //     data->accel_y = 0;
            // }
            if (data->accel_y > 2)
            {
                SetSpriteAnim(THIS, anim_fall, 15);
            }
            if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                TranslateSprite(THIS, -2, 0);
                THIS->mirror = V_MIRROR;
                  
            }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                TranslateSprite(THIS, 2, 0);
                THIS->mirror = NO_MIRROR;
            }
        break;
        case 8:
            TranslateSprite(THIS, 1, 0);
            SetSpriteAnim(THIS, anim_walk, 15);
            THIS->mirror = NO_MIRROR;
            if(THIS->x == 11){
                data->state = 0;
            }
        break;
        case 9:
            THIS->x++;
            THIS->mirror = NO_MIRROR;
            if(THIS->x >= (scroll_x + 172)){
                current_level++;
                SetState(current_state);
            }
        break;
    }

   
    if (data->state != 8 && data->state != 9)
    {

        if (data->accel_y < 75)
        {
            data->accel_y += 6;
        }

        data->collision = TranslateSprite(THIS, 0, (data->accel_y >> (4)));
        if (!data->collision && delta_time != 0 && data->accel_y < 40)
        {
            data->accel_y += 6;
            data->collision = TranslateSprite(THIS, 0, (data->accel_y >> 4));
        }
        if (data->collision && !TranslateSprite(THIS, 0, (data->accel_y >> (-4 << delta_time))))
        {
            data->accel_y = 0;
            if (data->state == 1 || data->state == 2 || data->state == 3 || data->state == 4)
            {
                data->state = 0;
                SetSpriteAnim(THIS, anim_idle, 15);
            }
        }
        if (data->state == 0 && data->accel_y >= 20)
        {
            data->state = 1;
        }
    }

    CheckCollisionTile(data);



	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteSpinOrb) {
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (data->state == 2 || data->state == 3)) {
                data->state = 3;
                data->accel_y = -80;
                SetSpriteAnim(THIS, anim_spin, 40);
			}
		}
        if(spr->type == SpriteJumpBox) {
            CUSTOM_DATA* sprData = (CUSTOM_DATA*)spr->custom_data;
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && sprData->state == 0 && (data->state == 1 || data->state == 4 )  ) {
                data->state = 4;
                data->accel_y = -80;
                SetSpriteAnim(THIS, anim_jump, 40);
			}
		}

        if(spr->type == SpriteDoorTile1 || spr->type == SpriteDoorTile2 || spr->type == SpriteDoorTile3) {
			if(CheckCollision(THIS, spr) ) {
                current_life = 0;
                ScreenShake(1,1);
                RefreshLife();
                SetState(current_state);
			}
		}

        if(spr->type == SpriteCrusherDown) {
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y) && (data->state == 2 || data->state == 3) ) {
                // THIS->y -= 5;
                data->state = 3;
                data->accel_y = -80;
                SetSpriteAnim(THIS, anim_spin, 40);
			}
		}


	}






}

void DESTROY()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    if(data->state != 9 && data->state != 8){
        current_life = 0;
        ScreenShake(1,1);
        RefreshLife();
        SetState(current_state);
    }   

}