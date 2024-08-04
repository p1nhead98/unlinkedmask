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
#include "WinController.h"

#define InmunityTime 100

const UINT8 nc_anim_idle[] = {2, 0, 1};
const UINT8 nc_anim_walk[] = {4, 2, 1, 3, 1};
const UINT8 nc_anim_jump[] = {2, 4, 5};
const UINT8 nc_anim_fall[] = {2, 6, 7};
const UINT8 nc_anim_death[] = {4, 8, 9, 9, 9};
const UINT8 nc_anim_dab[] = {2, 11, 12};
const UINT8 nc_anim_patinar[] = {2, 10, 10};


DECLARE_MUSIC(unlinkedunchainedsoul);

extern INT16 inmunity;
extern INT8 pal_tick;
extern UINT8 current_pal;
extern UINT8 current_life;
extern UINT8 current_level;
extern UINT8 door_open;
extern UINT8 IsFirstLvl;
extern UINT8 start_screen;

extern UINT8 deaths_u_count;
extern UINT8 deaths_d_count;
BOOLEAN canHurtNc;


INT16 player_nc_accel_y = 0;
INT16 player_nc_can = 0;
INT8 player_nc_state = 0;
UINT8 player_nc_collision = 0;
UINT8 player_nc_last_state = 0;
UINT8 player_nc_counter = 0;
UINT8 player_nc_start = 0;
INT16 player_nc_initial_y = 0;
INT16 player_nc_init_framespeed = 0;

// void UpdateMapTile(INT16 map_x, INT16 map_y, UINT8 tile_id, UINT8 c) {
//        UPDATE_TILE(map_x, map_y, &tile_id, &c);
// }

void CheckCollisionTileNc()
{

// if(current_level != 18 && current_level != 17){

    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 12u) >> 3);
 

    if (colision == 112 || colision == 113 || colision == 114 || colision == 115)
    {
        if(canHurtNc && player_nc_state != 11){
            inmunity = InmunityTime;
            canHurtNc = 0;
            current_life--;
            ScreenShake(1,1);
            RefreshLife();
        }
        
        //SpriteManagerRemove(THIS_IDX);
    }

    if(colision == 116){  // MUERE POR CAIDA
        current_life = 0;

        if(deaths_u_count != 99){
            deaths_u_count++;
        }else{
            if(deaths_d_count != 9){
                deaths_u_count = 0;
                deaths_d_count++;
            }
        }

        player_nc_state = 55;
        ScreenShake(1,1);
        RefreshLife();
        SetState(current_state);
    }
   

}



void START()
{
    player_nc_state = 8;
    player_nc_accel_y = 0;
    player_nc_collision = 0;
    player_nc_start = 1;
    player_nc_initial_y = 0;
    player_nc_init_framespeed = 0;

    THIS->lim_x = 80;
    THIS->lim_y = 40;
    // player_direction = FALSE;
    // player_canDo = TRUE;
    player_nc_last_state = 0;
    player_nc_can = 0;
    THIS->x -= 8;
    if(IsFirstLvl){
        THIS->y -= 8;
    }
    player_nc_counter =  0;
    inmunity = 0;
    canHurtNc = inmunity < 1 ? 1 : 0;

}

void UPDATE()
{

    UINT8 i;
	Sprite* spr;

    if(start_screen == 0){
        if(player_nc_start == 0){
            player_nc_start = 1;
            THIS->y = player_nc_initial_y;
            THIS->anim_speed = player_nc_init_framespeed;
        }
        if (inmunity != 0)
        {
            inmunity -= (1 << delta_time);

            if (inmunity < 1)
            {
                inmunity = 0;
                pal_tick = 0; //This forces the palette to be 0 after after the next if
                current_pal = 1;
                canHurtNc = 1;
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
            SetSpriteAnim(THIS, nc_anim_death, 15);
            player_nc_state = 11;
            
            // SetState(current_state);
        }
        if(current_level != 17 && current_level != 18){
            if( (THIS->x >= scroll_x + 150) && player_nc_state != 9 && player_nc_state != 8){
                player_nc_state = 9;
            }
        }



        switch( player_nc_state ){
            case 0:

                if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                    TranslateSprite(THIS, -2, 0);
                    SetSpriteAnim(THIS, nc_anim_walk, 15);
                    THIS->mirror = V_MIRROR;
                }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                    TranslateSprite(THIS, 2, 0);
                    SetSpriteAnim(THIS, nc_anim_walk, 15);
                    THIS->mirror = NO_MIRROR;
                }else if(!KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                    SetSpriteAnim(THIS, nc_anim_idle, 15);
                }
                if(KEY_TICKED(J_A)){
                    player_nc_state = 1;
                    player_nc_accel_y = -82;
                    JumpRandSound(0);
                    SetSpriteAnim(THIS, nc_anim_jump, 15);
                    player_nc_last_state = 0;
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                }
            break;
            case 1:
                if(!KEY_PRESSED(J_A) && player_nc_accel_y < 0){
                    player_nc_accel_y = 0;
                }
                if (player_nc_accel_y > 2)
                {
                    SetSpriteAnim(THIS, nc_anim_fall, 15);
                }
                if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                    TranslateSprite(THIS, -2, 0);
                    THIS->mirror = V_MIRROR;
                    
                }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                    TranslateSprite(THIS, 2, 0);
                    THIS->mirror = NO_MIRROR;
                }
            break;


            case 4:
                // if(!KEY_PRESSED(J_B) && player_nc_accel_y < 0){
                //     player_nc_accel_y = 0;
                // }
                if (player_nc_accel_y > 2)
                {
                    SetSpriteAnim(THIS, nc_anim_fall, 15);
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
                    player_nc_accel_y = -70;
                    THIS->mirror = NO_MIRROR;
                    
                    SetSpriteAnim(THIS, nc_anim_jump, 15);
                    player_nc_state = 12;
                    PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                }else{  
                    TranslateSprite(THIS, 1, 0);
                    SetSpriteAnim(THIS, nc_anim_walk, 15);
                    THIS->mirror = NO_MIRROR;
                    if(THIS->x == 16){
                        player_nc_state = 0;
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
                if(player_nc_accel_y < 85){
                    if(KEY_TICKED(J_A)){
                        player_nc_state = 1;
                        player_nc_accel_y = -82;
                        JumpRandSound(0);
                        SetSpriteAnim(THIS, nc_anim_jump, 15);
                        SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                    }

                }
                
                if (player_nc_accel_y > 2)
                {
                    
                    SetSpriteAnim(THIS, nc_anim_fall, 15);
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
                if (player_nc_accel_y > 2)
                {
                    
                    SetSpriteAnim(THIS, nc_anim_fall, 15);
                }
            break;
            case 13: //animacion patinar
                TranslateSprite(THIS, 1, 0);
                if(THIS->anim_frame == 1){
                    player_nc_counter++;
                    player_nc_can = player_nc_can ? 0 : 1;
                    if(player_nc_can == 0){
                        SpriteManagerAdd(SpriteIntroFx, THIS->x - 8, THIS->y);
                    }
                }
                if(player_nc_counter == 10){
                    player_nc_counter = 0;
                    SetSpriteAnim(THIS, nc_anim_dab, 15);
                    player_nc_state++;
                    SpriteManagerAdd(SpriteIntroBigShine, THIS->x + 8, THIS->y - 8);
                }
                
            break;
            case 14: //animacion dab
            
                if(THIS->anim_frame == 1){
                    player_nc_counter++;
                }
                if(player_nc_counter == 40){
                    player_nc_counter = 0;
                    player_nc_state = 0;
                    PlayMusic(unlinkedunchainedsoul, 1);
                }
                
            break;
        }

    
        if (player_nc_state != 8 && player_nc_state != 9 && player_nc_state != 11)
        {

            if (player_nc_accel_y < 90)
            {
                player_nc_accel_y += 6;
            }

            player_nc_collision = TranslateSprite(THIS, 0, (player_nc_accel_y >> (4)));
            if (!player_nc_collision && delta_time != 0 && player_nc_accel_y < 40)
            {
                player_nc_accel_y += 6;
                player_nc_collision = TranslateSprite(THIS, 0, (player_nc_accel_y >> 4));
            }
            if (player_nc_collision && !TranslateSprite(THIS, 0, (player_nc_accel_y >> (-4 << delta_time))))
            {
                player_nc_accel_y = 0;
                if (player_nc_state == 1 || player_nc_state == 2 || player_nc_state == 3 || player_nc_state == 4 || player_nc_state == 10)
                {
                    player_nc_state = 0;
                    SetSpriteAnim(THIS, nc_anim_idle, 15);
                }
                if(player_nc_state == 12){
                    player_nc_state++;
                    SetSpriteAnim(THIS, nc_anim_patinar, 30);
                }
            }
            if (player_nc_state == 0 && player_nc_accel_y >= 20)
            {
                player_nc_state = 10;
            }
        }

        CheckCollisionTileNc();



        SPRITEMANAGER_ITERATE(i, spr) {



            if(spr->type == SpriteJumpBox && player_nc_accel_y > 0)  {
                CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
                if(CheckCollision(THIS, spr) && sprData->state == 0 && (player_nc_state == 1 || player_nc_state == 2 || player_nc_state == 4 || (player_nc_state == 10))  ) {
                    if(player_nc_state == 1 || player_nc_state == 4 || (player_nc_state == 10 && player_nc_last_state == 0) && THIS->y < (spr->y - 5)){
                        player_nc_state = 4;
                        player_nc_accel_y = -82;
                        SetSpriteAnim(THIS, nc_anim_jump, 40);   
                    }
                    PlayFx(CHANNEL_4, 10, 0x05, 0xf1, 0x70, 0xc0);
                    SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                    sprData->state = 1;
                }
            }

        }
    }else{
       
        if(THIS->y != 0  && player_nc_start == 1){
            player_nc_start = 0;
            player_nc_initial_y = THIS->y;
            THIS->y = 0;
            player_nc_init_framespeed = THIS->anim_speed;
            THIS->anim_speed = 0;
        } 
    }
}

void DESTROY()
{

    if(player_nc_state != 9 && player_nc_state != 8 && player_nc_state != 11){
        current_life = 0;
        ScreenShake(1,1);
        RefreshLife();
        SetState(current_state);
    }   

}