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
const UINT8 anim_death[] = {4, 14, 15, 15, 15};


extern INT16 inmunity;
extern INT8 pal_tick;
extern UINT8 current_pal;
extern UINT8 current_life;
extern UINT8 current_level;
BOOLEAN canHurt;


INT16 player_accel_y;
INT16 player_accel_x;
INT8 player_state;
UINT8 player_collision;



// void UpdateMapTile(INT16 map_x, INT16 map_y, UINT8 tile_id, UINT8 c) {
//        UPDATE_TILE(map_x, map_y, &tile_id, &c);
// }

void CheckCollisionTile()
{



    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 12u) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x + 1u) >> 3, (THIS->y + 16u) >> 3);
    UINT8 colision3 = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y + 16u) >> 3);

 

    if (colision == 112 || colision == 113 || colision == 114 || colision == 115)
    {
        if(canHurt && player_state != 11){
            inmunity = 30;
            canHurt = 0;
            current_life--;
            ScreenShake(1,1);
            RefreshLife();
        }
        
        //SpriteManagerRemove(THIS_IDX);
    }
    if( (colision2 == 108 || colision2 == 110) ||  (colision3 == 108 || colision3 == 110)){
        if((player_state == 2 || player_state == 3)  && player_accel_y > 2 ){
            player_state = 3;
            player_accel_y = -82;
            PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
            // PlayFx(CHANNEL_2, 10, 0xc1, 0xb1, 0x2b, 0x87);
            SetSpriteAnim(THIS, anim_spin, 20);
            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
        }
    }




   

}



void START()
{
    player_state = 0;
    player_accel_y = 0;
    player_collision = 0;
    THIS->lim_x = 80;
    THIS->lim_y = 40;
    // player_direction = FALSE;
    // player_canDo = TRUE;

    player_accel_x = 0;
    // THIS->x -= 17;
    canHurt = inmunity < 1 ? 1 : 0;
}

void UPDATE()
{

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


    if(current_life < 1){ // DEATH
        SetSpriteAnim(THIS, anim_death, 15);
        player_state = 11;
        
        // SetState(current_state);
    }
    if( (THIS->x >= scroll_x + 150) && player_state != 9 && player_state != 8){
        player_state = 9;
    }


    switch( player_state ){
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
                player_state = 1;
                player_accel_y = -82;
                JumpRandSound(0);
                SetSpriteAnim(THIS, anim_jump, 15);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
            }
            if(KEY_TICKED(J_B)){
                player_state = 2;
                player_accel_y = -82;
                JumpRandSound(1);
                SetSpriteAnim(THIS, anim_spin, 20);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
            }
        break;
        case 1:
            if(!KEY_PRESSED(J_A) && player_accel_y < 0){
                player_accel_y = 0;
            }
            if (player_accel_y > 2)
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
            if(!KEY_PRESSED(J_B) && player_accel_y < 0){
                player_accel_y = 0;
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
            // if(!KEY_PRESSED(J_B) && player_accel_y < 0){
            //     player_accel_y = 0;
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
            // if(!KEY_PRESSED(J_B) && player_accel_y < 0){
            //     player_accel_y = 0;
            // }
            if (player_accel_y > 2)
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
            if(THIS->x == 16){
                player_state = 0;
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
        case 10:
            if(player_accel_y < 85){
                if(KEY_TICKED(J_A)){
                    player_state = 1;
                    player_accel_y = -82;
                    JumpRandSound(0);
                    SetSpriteAnim(THIS, anim_jump, 15);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
                if(KEY_TICKED(J_B)){
                    player_state = 2;
                    player_accel_y = -82;
                    JumpRandSound(1);
                    SetSpriteAnim(THIS, anim_spin, 20);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }

            }
            
            if (player_accel_y > 2)
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
        case 11:
            if(THIS->anim_frame == 3){
                SpriteManagerRemove(THIS_IDX);
                SpriteManagerAdd(SpritePlayerDeath, THIS->x - 12, THIS->y - 8);
            }
        break;
    }

   
    if (player_state != 8 && player_state != 9)
    {

        if (player_accel_y < 90)
        {
            player_accel_y += 6;
        }

        player_collision = TranslateSprite(THIS, 0, (player_accel_y >> (4)));
        if (!player_collision && delta_time != 0 && player_accel_y < 40)
        {
            player_accel_y += 6;
            player_collision = TranslateSprite(THIS, 0, (player_accel_y >> 4));
        }
        if (player_collision && !TranslateSprite(THIS, 0, (player_accel_y >> (-4 << delta_time))))
        {
            player_accel_y = 0;
            if (player_state == 1 || player_state == 2 || player_state == 3 || player_state == 4 || player_state == 10)
            {
                player_state = 0;
                SetSpriteAnim(THIS, anim_idle, 15);
            }
        }
        if (player_state == 0 && player_accel_y >= 20)
        {
            player_state = 10;
        }
    }

    CheckCollisionTile();



	SPRITEMANAGER_ITERATE(i, spr) {
		if(spr->type == SpriteSpinOrb && player_accel_y > 0) {
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3)) {
                player_state = 3;
                player_accel_y = -82;
                 PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                 
                SetSpriteAnim(THIS, anim_spin, 20);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
			}
		}
        if(spr->type == SpriteSpinOrbActivable  && player_accel_y > 0) {
            CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3)) {
                player_state = 3;
                player_accel_y = -82;
                if(sprData->state == 0){
                    sprData->state = 1;
                }
                 PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                SetSpriteAnim(THIS, anim_spin, 20);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
			}
		}
        if(spr->type == SpriteJumpBox && player_accel_y > 0)  {
            CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && sprData->state == 0 && (player_state == 1 || player_state == 2 || player_state == 4 )  ) {
                if(player_state == 1 || player_state == 4){
                    player_state = 4;
                    player_accel_y = -82;
                    SetSpriteAnim(THIS, anim_jump, 40);   
                }
                PlayFx(CHANNEL_4, 10, 0x05, 0xf1, 0x70, 0xc0);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                sprData->state = 1;
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
			if(CheckCollision(THIS, spr) && THIS->y < (spr->y) && (player_state == 2 || player_state == 3) ) {
                // THIS->y -= 5;
                player_state = 3;
                player_accel_y = -82;
                SetSpriteAnim(THIS, anim_spin, 20);
			}
		}

        if(spr->type == SpriteOnOffBtn) {
            CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
			if(CheckCollision(THIS, spr) && THIS->y > (spr->y) && (player_state == 1 || player_state == 2 || player_state == 3 || player_state == 4) ) {
                // THIS->y -= 5;
                player_accel_y = 20;
                if(player_state == 1 || player_state == 4){
                    player_state = 4;
                    SetSpriteAnim(THIS, anim_jump, 20);
                }else{
                    player_state = 3;
                    SetSpriteAnim(THIS, anim_jump, 20);
                }
                if(sprData->state == 0){
                    sprData->state = 1;
                }
                
                
			}
		}


	}






}

void DESTROY()
{

    if(player_state != 9 && player_state != 8 && player_state != 11){
        current_life = 0;
        ScreenShake(1,1);
        RefreshLife();
        SetState(current_state);
    }   

}