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
#include "Music.h"

const UINT8 anim_idle[] = {2, 0, 1};
const UINT8 anim_walk[] = {4, 2, 1, 3, 1};
const UINT8 anim_jump[] = {2, 4, 5};
const UINT8 anim_fall[] = {2, 6, 7};
const UINT8 anim_spin[] = {6, 8, 9, 10, 11, 12, 13};
const UINT8 anim_death[] = {4, 14, 15, 15, 15};
const UINT8 anim_dab[] = {2, 16, 17};
const UINT8 anim_patinar[] = {2, 18, 18};


DECLARE_MUSIC(unlinkedunchainedsoul);

extern INT16 inmunity;
extern INT8 pal_tick;
extern UINT8 current_pal;
extern UINT8 current_life;
extern UINT8 current_level;
extern UINT8 door_open;
extern UINT8 IsFirstLvl;
extern UINT8 start_screen;
BOOLEAN canHurt;


INT16 player_accel_y = 0;
INT16 player_accel_x = 0;
INT8 player_state = 0;
UINT8 player_collision = 0;
UINT8 player_last_state = 0;
UINT8 player_counter = 0;
// UINT8 player_dj = 0;

UINT8 player_start = 0;
INT16 player_initial_y = 0;
INT16 player_init_framespeed = 0;


// void UpdateMapTile(INT16 map_x, INT16 map_y, UINT8 tile_id, UINT8 c) {
//        UPDATE_TILE(map_x, map_y, &tile_id, &c);
// }

void CheckCollisionTile()
{

if(current_level != 18 && current_level != 17){

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
        if((player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1))  && player_accel_y > 2 ){
            player_state = 3;
            player_accel_y = -82;
            PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
            // PlayFx(CHANNEL_2, 10, 0xc1, 0xb1, 0x2b, 0x87);
            SetSpriteAnim(THIS, anim_spin, 20);
            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
        }
    }
    if( (colision > 63 && colision < 76) && current_level > 10 && current_life != 0 && door_open == 0){
        current_life = 0;
        ScreenShake(1,1);
        RefreshLife();
        SetSpriteAnim(THIS, anim_death, 15);
        player_state = 11;
    }
    if(colision == 116){
        current_life = 0;
        player_state = 55;
        ScreenShake(1,1);
        RefreshLife();
        SetState(current_state);
    }


}

   

}



void START()
{
    player_state = 8;
    player_accel_y = 0;
    player_collision = 0;
    THIS->lim_x = 80;
    THIS->lim_y = 40;

    player_start = 1;
    player_initial_y = 0;
    player_init_framespeed = 0;

    // player_direction = FALSE;
    // player_canDo = TRUE;
    player_last_state = 0;
    player_accel_x = 0;
    THIS->x -= 8;
    if(IsFirstLvl){
        THIS->y -= 8;
    }
    player_counter =  0;
    inmunity = 0;
    canHurt = inmunity < 1 ? 1 : 0;
    // player_dj = 0;

}

void UPDATE()
{

    UINT8 i;
	Sprite* spr;


    if(start_screen == 0){
        if(player_start == 0){
            player_start = 1;
            THIS->y = player_initial_y;
            THIS->anim_speed = player_init_framespeed;
        }

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
        if(current_level != 17 && current_level != 18){
            if( (THIS->x >= scroll_x + 150) && player_state != 9 && player_state != 8){
                player_state = 9;
            }
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
                    player_last_state = 0;
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                    // player_dj = 1;
                }
                if(KEY_TICKED(J_B)){
                    player_state = 2;
                    player_accel_y = -82;
                    JumpRandSound(1);
                    SetSpriteAnim(THIS, anim_spin, 20);
                    player_last_state = 1;
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            break;
            case 1:
                if(!KEY_PRESSED(J_A) && player_accel_y < 0){
                    player_accel_y = 0;
                }
                // if(KEY_TICKED(J_A) &&  player_dj < 2){
                     
                //     player_accel_y = -82;
                //     JumpRandSound(0);
                //     SetSpriteAnim(THIS, anim_jump, 15);
                //     player_last_state = 0;
                //     SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     player_dj = 2;
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
            case 8: //animacion al entrar a un nivel
                if(IsFirstLvl){
                    player_accel_y = -80;
                    THIS->mirror = NO_MIRROR;
                    
                    SetSpriteAnim(THIS, anim_jump, 15);
                    player_state = 12;
                }else{  
                    TranslateSprite(THIS, 1, 0);
                    SetSpriteAnim(THIS, anim_walk, 15);
                    THIS->mirror = NO_MIRROR;
                    if(THIS->x == 16){
                        player_state = 0;
                    }
                }
    
            break;
            case 9: //animacion al llegar al limite del nivel
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
                    
                    SetSpriteAnim(THIS, player_last_state == 1 ? anim_spin : anim_fall, 15);
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
            case 12: //salto intro escena
                TranslateSprite(THIS, 2, 0);
                if (player_accel_y > 2)
                {
                    SetSpriteAnim(THIS, anim_fall, 15);
                }
            break;
            case 13: //animacion patinar
                TranslateSprite(THIS, 1, 0);
                if(THIS->anim_frame == 1){
                    player_counter++;
                }
                if(player_counter == 10){
                    player_counter = 0;
                    SetSpriteAnim(THIS, anim_dab, 15);
                    player_state++;
                    SpriteManagerAdd(SpriteIntroBigShine, THIS->x + 8, THIS->y - 8);
                }
                
            break;
            case 14: //animacion dab
            
                if(THIS->anim_frame == 1){
                    player_counter++;
                }
                if(player_counter == 30){
                    player_counter = 0;
                    player_state = 0;
                    PlayMusic(unlinkedunchainedsoul, 1);
                }
                
            break;
        }

    
        if (player_state != 8 && player_state != 9 && player_state != 11)
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
                if(player_state == 12){
                    player_state++;
                    SetSpriteAnim(THIS, anim_patinar, 30);
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
                if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1))) {
                    player_state = 3;
                    player_accel_y = -83;
                    PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    
                    SetSpriteAnim(THIS, anim_spin, 20);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            }
            if(spr->type == SpriteSpinOrbFall && player_accel_y > 0) {
                CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1))) {
                    player_state = 3;
                    player_accel_y = -83;
                    PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    if(sprData->state == 0){
                        sprData->state = 1;
                    }
                    SetSpriteAnim(THIS, anim_spin, 20);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            }
            if(spr->type == SpriteSpinOrbActivable  && player_accel_y > 0) {
                CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1))) {
                    player_state = 3;
                    player_accel_y = -83;
                    if(sprData->state == 0){
                        sprData->state = 1;
                    }
                    PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    SetSpriteAnim(THIS, anim_spin, 20);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            }
            if((spr->type == SpriteSpinOrbStoppable || spr->type == SpriteSpinOrbStoppable2 || spr->type == SpriteSpinOrbStoppable3)  && player_accel_y > 0) {
                CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1))) {
                    player_state = 3;
                    player_accel_y = -83;
                    if(sprData->state == 0){
                        sprData->state = 1;
                    }else if(sprData->state == 6){
                        sprData->state = sprData->initial_state;
                    }
                    PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    SetSpriteAnim(THIS, anim_spin, 20);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            }
            if(spr->type == SpriteJumpBox && player_accel_y > 0)  {
                CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
                if(CheckCollision(THIS, spr) && sprData->state == 0 && (player_state == 1 || player_state == 2 || player_state == 4 || (player_state == 10))  ) {
                    if(player_state == 1 || player_state == 4 || (player_state == 10 && player_last_state == 0) && THIS->y < (spr->y - 5)){
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
                if(CheckCollision(THIS, spr) && THIS->y < (spr->y) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 1)) ) {
                    // THIS->y -= 5;
                    player_state = 3;
                    player_accel_y = -82;
                    SetSpriteAnim(THIS, anim_spin, 20);
                }
            }

            if(spr->type == SpriteOnOffBtn) {
                CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
                if(CheckCollision(THIS, spr) && THIS->y >= (spr->y) && (player_state == 1 || player_state == 2 || player_state == 3 || player_state == 4) && player_accel_y < 0) {
                    // THIS->y -= 5;
                    player_accel_y = 20;
                    if(player_state == 1 || player_state == 4){
                        player_state = 4;
                        SetSpriteAnim(THIS, anim_jump, 20);
                    }else{
                        player_state = 3;
                        SetSpriteAnim(THIS, anim_spin, 20);
                    }
                    if(sprData->state == 0){
                        sprData->state = 1;
                    }
                    
                    
                }
            }

            if(spr->type == SpriteCrystalAttack){
                if(CheckCollision(THIS, spr)) {
                    if(canHurt && player_state != 11){
                        inmunity = 30;
                        canHurt = 0;
                        current_life--;
                        ScreenShake(1,1);
                        RefreshLife();
                    }
                }
            }


        }

    }else{
       
        if(THIS->y != 0  && player_start == 1){
            player_start = 0;
            player_initial_y = THIS->y;
            THIS->y = 0;
            player_init_framespeed = THIS->anim_speed;
            THIS->anim_speed = 0;
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