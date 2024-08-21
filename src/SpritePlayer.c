#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "Misc2.h"
#include "WinController.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "Scroll.h"
#include "ZGBMain.h"
#include "Music.h"
#include "TileAnimation.h"

#define InmunityTime 100

const UINT8 anim_idle[] = {2, 0, 1};
const UINT8 anim_walk[] = {4, 2, 1, 3, 1};
const UINT8 anim_jump[] = {2, 4, 5};
const UINT8 anim_fall[] = {2, 6, 7};
const UINT8 anim_spin[] = {6, 8, 9, 10, 11, 12, 13};
const UINT8 anim_death[] = {4, 14, 15, 15, 15};
const UINT8 anim_dab[] = {2, 16, 17};
const UINT8 anim_patinar[] = {2, 18, 18};

const UINT8 anim_back[] = {3, 19, 20, 21};


// DECLARE_MUSIC(unlinkedunchainedsoul);

extern UINT8 load_next;

extern INT16 inmunity;
extern INT8 pal_tick;
extern UINT8 current_pal;
extern UINT8 current_life;
extern UINT8 current_level;
extern UINT8 door_open;
extern UINT8 start_screen;

extern UINT8 deaths_u_count;
extern UINT8 deaths_d_count;

extern UINT8 on_off;
extern UINT8 canDo;
extern UINT8 change_jump_count;
extern INT8 boss_state;

extern UINT8 IsCutscene;

extern UINT8 current_cs;

BOOLEAN canHurt;


INT16 player_accel_y = 0;
INT8 player_state = 0;
INT8 player_last_state = 0;
UINT8 player_collision = 0;
UINT8 player_counter = 0;
UINT8 player_counter2 = 0;
UINT8 player_priority = 0;
UINT8 player_canDo = 0;
// UINT8 player_dj = 0;

UINT8 player_start = 0;
INT16 player_initial_y = 0;
INT16 player_init_framespeed = 0;

UINT8 bossCanHurt = 0;
// void UpdateMapTile(INT16 map_x, INT16 map_y, UINT8 tile_id, UINT8 c) {
//        UPDATE_TILE(map_x, map_y, &tile_id, &c);
// }
void playerHurtSound(){
    // PlayFx(CHANNEL_1, 15, 0x3a, 0xbf, 0xf1, 0x9e, 0xc7);
}

void boss1Collisions(UINT8 bossCanHurt){
    switch (bossCanHurt){
        case 1:
            if((THIS->y + 4) > 128 && (THIS->x > 0 && THIS->x < 112)){
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;

        case 2:
            if((THIS->y + 4) > 128 && (THIS->x > 112)){
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;
 
        case 3:
            if(((THIS->x > 32 && THIS->x < 64) || (THIS->x > 96 && THIS->x < 128 ) || (THIS->x > 160 && THIS->x < 192) )&& (THIS->y + 4) > 128){
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;
        case 4:
            if(((THIS->x > 64 && THIS->x < 96) || (THIS->x > 128 && THIS->x < 160 )) && (THIS->y + 4) > 128){
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;
        case 5:
            if(((THIS->x > 32 && THIS->x < 48) || (THIS->x > 64 && THIS->x < 80 ) || (THIS->x > 96 && THIS->x < 112) || (THIS->x > 128 && THIS->x < 144) || (THIS->x > 160 && THIS->x < 176 )) && (THIS->y + 4) > 128){
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;
        case 6:
            if(((THIS->x >48 && THIS->x < 64) || (THIS->x > 80 && THIS->x < 96 ) || (THIS->x > 112 && THIS->x < 128) || (THIS->x > 144 && THIS->x < 160) || (THIS->x > 176 && THIS->x < 192 )) && (THIS->y + 4) > 128){
                 if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
            }
            break;

        default:
            break;
    }
}

void CheckDeathTiles(){

    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 12u) >> 3);
    

    if(current_level != 32){
        if(current_level == 25){
            if(  ( THIS->x > 1449 && THIS->x < 1488) || ( THIS->x > 1697 && THIS->x < 1736) || ( THIS->x > 1825 && THIS->x < 1864)  ){
                if(canDo == 0 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }else if(( (THIS->x > 1281 && THIS->x < 1336) && THIS->y < 104)){
                if(canDo == 0 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }else if( ( THIS->x > 169 && THIS->x < 224 ) || ( THIS->x > 297 && THIS->x < 336) || ( THIS->x > 705 && THIS->x < 432) || ( THIS->x > 449 && THIS->x < 488) || ( THIS->x > 505 && THIS->x < 544) || ( THIS->x > 1369 && THIS->x < 1408) || ( THIS->x > 1553 && THIS->x < 1592 ) || ( THIS->x > 1761 && THIS->x < 1800) ){
                if(canDo == 1 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }else if((colision == 60 || colision == 61 || colision == 62 || colision == 63)){
                if(canDo == 1 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }else if((colision == 56 || colision == 57 || colision == 58 || colision == 59)){
                if(canDo == 0 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }
        }
        if(current_level == 30 ){
            if((colision == 60 || colision == 61 || colision == 62 || colision == 63)){
                if(canDo == 1 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }else if((colision == 56 || colision == 57 || colision == 58 || colision == 59)){
                if(canDo == 0 && player_state != 11){
                    current_life = 0;
                    ScreenShake(1,1);
                    RefreshLife();
                    SetSpriteAnim(THIS, anim_death, 15);
                    player_state = 11;
                }
            }

            if ((colision == 81 || colision == 82 || colision == 83 || colision == 84) && on_off == 0)
            {
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
                
            }else if ((colision == 85 || colision == 86 || colision == 87 || colision == 88) && on_off == 1)
            {
                if(canHurt && player_state != 11){
                    inmunity = InmunityTime;
                    canHurt = 0;
                    current_life--;
                    ScreenShake(1,1);
                    RefreshLife();
                }
                
            }
        }

        if ((colision == 81 || colision == 82 || colision == 83 || colision == 84) && canDo == 0)
        {
            if(canHurt && player_state != 11){
                inmunity = InmunityTime;
                canHurt = 0;
                current_life--;
                ScreenShake(1,1);
                RefreshLife();
            }
            
        }else if ((colision == 85 || colision == 86 || colision == 87 || colision == 88) && canDo == 1)
        {
            if(canHurt && player_state != 11){
                inmunity = InmunityTime;
                canHurt = 0;
                current_life--;
                ScreenShake(1,1);
                RefreshLife();
            }
            
        }

    }
}

void ChangeJumpCollision(){

    UINT8 colision = GetScrollTile((THIS->x) >> 3, (THIS->y ) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x + 8u) >> 3, (THIS->y ) >> 3);
    UINT8 colision3 = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y ) >> 3);

    UINT8 colision4 = GetScrollTile((THIS->x) >> 3, (THIS->y + 8u) >> 3);
    UINT8 colision5 = GetScrollTile((THIS->x + 8u) >> 3, (THIS->y + 8u ) >> 3);
    UINT8 colision6 = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y + 8u ) >> 3);

    
    if(current_level > 26 && current_level != 32){
        if((colision == 47 || colision2 == 47 || colision3 == 47 || colision4 == 47 || colision5 == 47 || colision6 == 47) && change_jump_count == 0){
            change_jump_count = 20;
     
            if(player_state == 1){
                player_last_state = player_state;
                player_state = 2;
                SetSpriteAnim(THIS, anim_spin, 15);
            }else if(player_state == 2){
                player_last_state = player_state;
                player_state = 1;
                SetSpriteAnim(THIS, anim_jump, 15);
            }else if(player_state == 3){
                player_state = 4;
                SetSpriteAnim(THIS, anim_jump, 15);
            }else if(player_state == 4){
                player_state = 3;
                SetSpriteAnim(THIS, anim_spin, 15);
            }
        } 
    }
}


void CheckCollisionTile()
{

// if(current_level != 18 && current_level != 17){

    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 12u) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x + 1u) >> 3, (THIS->y + 16u) >> 3);
    UINT8 colision3 = GetScrollTile((THIS->x + 10u) >> 3, (THIS->y + 16u) >> 3);

    
    if(current_level != 34){
        if (colision == 112 || colision == 113 || colision == 114 || colision == 115)
        {
            if(canHurt && player_state != 11){
                inmunity = InmunityTime;
                canHurt = 0;
                current_life--;
                ScreenShake(1,1);
                RefreshLife();
                playerHurtSound();
            }
            
            //SpriteManagerRemove(THIS_IDX);
        }
        if( (colision2 == 108 || colision2 == 110) ||  (colision3 == 108 || colision3 == 110)){
            if((player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))  && player_accel_y > 2 ){
                player_state = 3;
                player_accel_y = -83;
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
        if(colision == 116 && current_life > 0){
            current_life = 0;
            player_state = 55;
            ScreenShake(1,1);
            RefreshLife();
            playerHurtSound();
            // SetState(current_state);
            if(deaths_u_count != 99){
                deaths_u_count++;
            }else{
                if(deaths_d_count != 9){
                    deaths_u_count = 0;
                    deaths_d_count++;
                }
            }
        }
    }else{
        if( (colision2 == 112 || colision2 == 113) ||  (colision3 == 112 || colision3 == 113)){
            if((player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))  && player_accel_y > 2 && (boss_state > 24 && boss_state < 43) ){
                player_state = 3;
                player_accel_y = -83;
                PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                // PlayFx(CHANNEL_2, 10, 0xc1, 0xb1, 0x2b, 0x87);
                SetSpriteAnim(THIS, anim_spin, 20);
                SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                if(boss_state == 25){
                    boss_state = 26;
                }
            }
        }
    }


// }

   

}

void PriorityCheck(){
    if(THIS->x < 37 && player_priority == 0){
        player_priority = 1;
    }else if(THIS->x > 37 && THIS->x < 210 && player_priority == 1){
        player_priority = 0;
    }else if(THIS->x > 210 && THIS->x < 292 && player_priority == 0){
        player_priority = 1;
    }else if(THIS->x > 292 && THIS->x < 466 && player_priority == 1){
        player_priority = 0;
    }else if(THIS->x > 467 && THIS->x < 548 && player_priority == 0){
        player_priority = 1;

    }else if(THIS->x > 548 && THIS->x < 724 && player_priority == 1){
        player_priority = 0;
    }else if(THIS->x > 722 && player_priority == 0){
        player_priority = 1;
    }
}

void START()
{
    CUSTOM_DATA_PRIORITY* data = (CUSTOM_DATA_PRIORITY*)THIS->custom_data;
    

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
    // THIS->x -= 8;
    // if(IsFirstLvl){
    //     THIS->y -= 8;
    // }
    player_counter =  0;
    player_counter2 = 4;
    inmunity = 0;
    canHurt = inmunity < 1 ? 1 : 0;
    bossCanHurt = 0;
    // THIS->mt_sprite->props = 57;
   
    // player_dj = 0;

    player_priority = current_level == 31 ? 1 : 0;
    THIS->mirror = current_level == 31 ? NM_PRIOR : NO_MIRROR;
    player_canDo = 0;
}

void UPDATE()
{
    CUSTOM_DATA_PRIORITY* data = (CUSTOM_DATA_PRIORITY*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;


    if(start_screen == 0){
        if(player_start == 0){
            player_start = 1;
            THIS->y = player_initial_y;
            THIS->anim_speed = player_init_framespeed;
        }


        if( IsCutscene == 0 || IsCutscene == 5 || IsCutscene == 2){

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


            if((KEY_PRESSED(J_LEFT) || KEY_PRESSED(J_RIGHT)) && _cpu == CGB_TYPE){
                if(--player_counter2 == 0){
                    player_counter2 = 8;
                    SpriteManagerAdd(SpritePlayerStars, THIS->x, THIS->y);
                }
            }

            if (current_level == 34)
            {
                boss1Collisions(bossCanHurt);
            }else if(current_level == 31){
                PriorityCheck();
            }
            

            if(current_life < 1){ // DEATH
                SetSpriteAnim(THIS, anim_death, 15);
                player_state = 11;
                
                // SetState(current_state);
            }
            if( current_level != 34){
                if( (THIS->x >= scroll_x + 150) && player_state != 9 && player_state != 8){
                    player_state = 9;
                }
            }


            if(current_level == 34){
                if((boss_state > 26 && boss_state < 42 ) && THIS->y > 120){
                    if(canHurt && player_state != 11){
                        inmunity = InmunityTime;
                        canHurt = 0;
                        current_life--;
                        ScreenShake(1,1);
                        RefreshLife();
                        playerHurtSound();
                    }
                } 
            }



            switch( player_state ){
                case 0:
                    if(IsCutscene != 5){
                        if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                            TranslateSprite(THIS, -2 << delta_time, 0);
                            if(current_level == 31){
                                if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_canDo == 0){
                                    player_canDo = 1;
                                    PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
                                }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_canDo == 1){
                                    player_canDo = 0;
                                }
                            }   
                            SetSpriteAnim(THIS, anim_walk, 15);
                            THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                            
                            if(current_level == 31){
                                if((THIS->anim_frame == 1 || THIS->anim_frame == 3) && player_canDo == 0){
                                    player_canDo = 1;
                                    PlayFx(CHANNEL_4, 5, 0x3A, 0x81, 0x00, 0xC0);
                                }else if ((THIS->anim_frame == 0 || THIS->anim_frame == 2 ) && player_canDo == 1){
                                    player_canDo = 0;
                                }
                            }
                            if(current_level == 34 && THIS->x < 192){
                                TranslateSprite(THIS, 2 << delta_time, 0);
                                SetSpriteAnim(THIS, anim_walk, 15);
                                THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                            }else if(current_level < 34){
                                TranslateSprite(THIS, 2 << delta_time, 0);
                                SetSpriteAnim(THIS, anim_walk, 15);
                                THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                            }
                            

                        }else if(!KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                            SetSpriteAnim(THIS, anim_idle, 15);
                        }

                        
                        if(KEY_TICKED(J_A)){
                            
                            player_state = 1;
                            player_last_state = player_state;
                            player_accel_y = -83;
                            JumpRandSound(0);
                            SetSpriteAnim(THIS, anim_jump, 15);
                            
                            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                            // player_dj = 1;
                        }
                        if(KEY_TICKED(J_B)){
                            
                            player_state = 2;
                            player_last_state = player_state;
                            player_accel_y = -83;
                            JumpRandSound(1);
                            SetSpriteAnim(THIS, anim_spin, 20);
                            
                            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                        }
                    }
                break;
                case 1:
                    if(!KEY_PRESSED(J_A) && player_accel_y < 0 && player_last_state == 1){
                        player_accel_y = 0;
                    }else if (!KEY_PRESSED(J_B) && player_accel_y < 0 && player_last_state == 2){
                        player_accel_y = 0;
                    }
        
                    if (player_accel_y > 2)
                    {
                        SetSpriteAnim(THIS, anim_fall, 15);
                    }
                    if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                        TranslateSprite(THIS, -2 << delta_time, 0);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        
                    }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                        if(current_level == 34 && THIS->x < 192){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }else if(current_level < 34){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                    
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }
                    }
                break;
            case 2:
                    if(!KEY_PRESSED(J_B) && player_accel_y < 0  ){
                        player_accel_y = 0;
                    }
                    
                    
                    if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                        TranslateSprite(THIS, -2 << delta_time, 0);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        
                    }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                        if(current_level == 34 && THIS->x < 192){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }else if(current_level < 34){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                    
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }
                    }
                break;
                case 3:
                    // if(!KEY_PRESSED(J_B) && player_accel_y < 0){
                    //     player_accel_y = 0;
                    // }
                    
                    if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                        TranslateSprite(THIS, -2 << delta_time, 0);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        
                    }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                        if(current_level == 34 && THIS->x < 192){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }else if(current_level < 34){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }
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
                        TranslateSprite(THIS, -2 << delta_time, 0);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        
                    }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                        if(current_level == 34 && THIS->x < 192){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }else if(current_level < 34){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }
                    }
                break;
                case 8: //animacion al entrar a un nivel
                    // if(IsFirstLvl){
                    //     player_accel_y = -80;
                    //     THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        
                    //     SetSpriteAnim(THIS, anim_jump, 15);
                    //     player_state = 12;
                    // }else{  
                        TranslateSprite(THIS, 1, 0);
                        SetSpriteAnim(THIS, anim_walk, 15);
                        THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        if(THIS->x == 16){
                            player_state = 0;
                        }
                    // }
        
                break;
                case 9: //animacion al llegar al limite del nivel
                    THIS->x++;
                    THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                    if(THIS->x >= (scroll_x + 172)){
                        if(current_state == StateStage2 && current_level == 4){
                            load_next = 0;
                            current_cs = 7;
                            current_state = StateCutscenes;
                            SetState(current_state);
                        }else{
                            load_next = 1;
                        }
                    }
                break;
                case 10:
                    if(player_accel_y < 85){
                        if(KEY_TICKED(J_A)){
                            player_state = 1;
                            player_accel_y = -83;
                            JumpRandSound(0);
                            SetSpriteAnim(THIS, anim_jump, 15);
                            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                        }
                        if(KEY_TICKED(J_B)){
                            player_state = 2;
                            player_accel_y = -83;
                            JumpRandSound(1);
                            SetSpriteAnim(THIS, anim_spin, 20);
                            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                        }

                    }
                    
                    if (player_accel_y > 2)
                    {
                        
                        SetSpriteAnim(THIS, player_last_state == 2 ? anim_spin : anim_fall, 15);
                    }
                    if(KEY_PRESSED(J_LEFT) && !KEY_PRESSED(J_RIGHT) && THIS->x > scroll_x + 2){
                        TranslateSprite(THIS, -2 << delta_time, 0);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                        
                    }else if(KEY_PRESSED(J_RIGHT) && !KEY_PRESSED(J_LEFT)){
                        if(current_level == 34 && THIS->x < 192){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }else if(current_level < 34){
                            TranslateSprite(THIS, 2 << delta_time, 0);
                            THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        }
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
                        // PlayMusic(unlinkedunchainedsoul, 1);
                    }
                    
                break;
                case 15:
                    if(THIS->x > 114){
                        THIS->x--;
                        SetSpriteAnim(THIS, anim_walk, 15);
                        THIS->mirror = player_priority == 1 ? VM_PRIOR : V_MIRROR;
                    }else if(THIS->x < 114){
                        THIS->mirror = player_priority == 1 ? NM_PRIOR : NO_MIRROR;
                        THIS->x++;
                        SetSpriteAnim(THIS, anim_walk, 15);
                    }else{
                        player_state++;
                        SetSpriteAnim(THIS, anim_back, 15);
                        player_counter = 70;
                    }
                    break;
                case 16:
                    if(--player_counter == 0){
                        current_level++;
                        SetState(current_state);
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
                            if(IsCutscene != 5){
                                player_state = 0;
                            }
                            SetSpriteAnim(THIS, anim_idle, 15);
                        }
                        if(player_state == 12){
                            player_state++;
                            SetSpriteAnim(THIS, anim_patinar, 30);
                        }
                    
                }else if(player_collision && player_accel_y < 0 && IsCutscene != 5){
                    player_accel_y = 0;
                }
                if (player_state == 0 && player_accel_y >= 20 && IsCutscene != 5)
                {
                    player_state = 10;
                }
            }

            if(current_level != 31){
                
                CheckCollisionTile();
                if(current_level == 25 || current_level == 29 || current_level == 30 ){
                    CheckDeathTiles();
                }
                if(current_level > 26 && current_level < 31){
                    ChangeJumpCollision();
                }
            }

            


            SPRITEMANAGER_ITERATE(i, spr) {

                if(spr->type == SpriteBoss1 && player_accel_y > 0) {
                    CUSTOM_DATA_BTN* sprData = (CUSTOM_DATA_BTN*)spr->custom_data;
                    if((sprData->state == 2 || sprData->state == 21 || sprData->state == 48)){
                        if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2)) && (sprData->state == 2 || sprData->state == 21 || sprData->state == 48)) {
                            player_state = 3;
                            player_accel_y = -83;
                            // PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                            sprData->state++;
                            ScreenShake(1,1);
                            SetSpriteAnim(THIS, anim_spin, 20);
                            SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                            PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
                            PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
                        }
                    }else if(CheckCollision(THIS, spr) && THIS->y + 8 > (spr->y) && player_state != 11 &&  (sprData->state == 6 || sprData->state == 7 || sprData->state == 13 || sprData->state == 16 || sprData->state == 19 ||  sprData->state == 20 || sprData->state == 29 || sprData->state == 32 || sprData->state == 35 || sprData->state == 38 || sprData->state == 41 || sprData->state == 46 || sprData->state == 80 || sprData->state == 81) ){
                        if(canHurt && player_state != 11){
                            inmunity = InmunityTime;
                            canHurt = 0;
                            current_life--;
                            ScreenShake(1,1);
                            RefreshLife();
                            playerHurtSound();
                        }
                    }
                }
                if(spr->type == SpriteOrbForest && player_accel_y > 0) {
                    CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                        player_state = 3;
                        player_accel_y = -83;
                        PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                        
                        SetSpriteAnim(THIS, anim_spin, 20);
                        SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                        if(current_level == 4){
                            if(sprData->state == 10){
                                sprData->state = 6;
                            }
                        }
                    }
                }

                if(spr->type == SpriteOrbTemple && player_accel_y > 0) {
                    CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                        player_state = 3;
                        player_accel_y = -83;
                        PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                        
                        SetSpriteAnim(THIS, anim_spin, 20);
                        SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                        if(current_level == 0 || current_level == 1 || current_level == 2){
                            if(sprData->state == 10){
                                sprData->state = 6;
                            }
                        }else if(current_level == 3){
                            if(sprData->state == 10){
                                sprData->state = 7;
                            }
                        }else if(current_level == 4){
                            if(sprData->state == 13){
                                sprData->state = 9;
                            }else if(sprData->state == 10 || sprData->state == 21){
                                sprData->state = 6;
                            }else if(sprData->state == 20){
                                sprData->state = 8;
                            }else if(sprData->state == 22){
                                sprData->state = 15;
                            }else if(sprData->state == 23){
                                sprData->state = 0;
                            }else if(sprData->state == 24){
                                sprData->state = 11;
                            }
                        }
                    }
                }

                if((spr->type == SpriteSpinOrb || spr->type == SpriteSpinOrbEvent) && player_accel_y > 0) {
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                        player_state = 3;
                        player_accel_y = -83;
                        PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                        
                        SetSpriteAnim(THIS, anim_spin, 20);
                        SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                    }
                }
                // if(spr->type == SpriteSpinOrbFall && player_accel_y > 0) {
                //     CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         if(sprData->state == 0){
                //             sprData->state = 1;
                //         }
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }
                if(spr->type == SpriteSpinOrbActivable  && player_accel_y > 0) {
                    CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
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
                // if(spr->type == SpriteSpinOrbEvent  && player_accel_y > 0) {
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }
                // if((spr->type == SpriteSpinOrbStoppable || spr->type == SpriteSpinOrbStoppable2 || spr->type == SpriteSpinOrbStoppable3)  && player_accel_y > 0) {
                //     CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         if(sprData->state == 0 ){
                //             sprData->state = 1;
                //         }else if( sprData->state == 10 ){
                //             sprData->state = 0;
                //             spr->y++;
                //         }else if(sprData->state == 6){
                //             sprData->state = sprData->initial_state;
                //         }
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }
                // if(( spr->type == SpriteSpinOrbStoppable4)  && player_accel_y > 0) {
                //     CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         if(sprData->state == 0 ){
                //             sprData->state = 1;
                //         }else if( sprData->state == 5 || sprData->state == 6 ){
                //             sprData->state = 1;
                            
                //         }else if( sprData->state == 7 ){
                //             sprData->state = 3;
                //             sprData->speed = sprData->initial_speed = 2;
                //         }
                //         // else if(sprData->state == 6){
                //         //     sprData->state = sprData->initial_state;
                //         // }
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }
                // if(( spr->type == SpriteSpinOrbStoppable5)  && player_accel_y > 0) {
                //     CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         if(sprData->state == 0 ){
                //             sprData->state = 1;
                //         }else if( sprData->state == 6  ){
                //             sprData->state = 3;
                            
                //         }else if( sprData->state == 7 ){
                //             sprData->state = 4;
                //             sprData->speed = sprData->initial_speed = 2;
                //         }else if( sprData->state == 8 ){
                //             sprData->state = 5;
                //         }
                //         // else if(sprData->state == 6){
                //         //     sprData->state = sprData->initial_state;
                //         // }
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }
                if((spr->type == SpriteJumpBox || spr->type == SpriteSplitBox || spr->type == SpriteJumpBoxEvent) && player_accel_y > 0)  {
                    CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
                    if(CheckCollision(THIS, spr) && sprData->state == 0 && (player_state == 1 || player_state == 2 || player_state == 4 || (player_state == 10))  ) {
                        if(player_state == 1 || player_state == 4 || (player_state == 10 && player_last_state == 1) && THIS->y < (spr->y - 5)){
                            player_state = 4;
                            player_accel_y = -83;
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
                        playerHurtSound();
                        // SetState(current_state);
                    
                    }
                }

                if(spr->type == SpriteCrusherDown) {
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2)) && player_accel_y > 0 ) {
                        // THIS->y -= 5;
                        player_state = 3;
                        player_accel_y = -83;
                        SetSpriteAnim(THIS, anim_spin, 20);
                        PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    }else if(CheckCollision(THIS, spr) && THIS->y + 8 > (spr->y) && player_state != 11){
                        current_life = 0;
                        ScreenShake(1,1);
                        RefreshLife();
                        playerHurtSound();
                        SetSpriteAnim(THIS, anim_death, 15);
                        player_state = 11;
                    }
                }

                if(spr->type == SpriteCrusherLeft) {
                    if(CheckCollision(THIS, spr) && THIS->y < (spr->y) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2)) && player_accel_y > 0 ) {
                        // THIS->y -= 5;
                        player_state = 3;
                        player_accel_y = -83;
                        SetSpriteAnim(THIS, anim_spin, 20);
                        PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                    }else if(CheckCollision(THIS, spr) && THIS->y + 8 > (spr->y + 12) && player_state != 11){
                        current_life = 0;
                        ScreenShake(1,1);
                        RefreshLife();
                        playerHurtSound();
                        SetSpriteAnim(THIS, anim_death, 15);
                        player_state = 11;
                    }
                }

                if(spr->type == SpriteSkullFlame) {
                   if(CheckCollision(THIS, spr) && player_state != 11){
                      if(canHurt && player_state != 11){
                            inmunity = InmunityTime;
                            canHurt = 0;
                            current_life--;
                            ScreenShake(1,1);
                            RefreshLife();
                        }
                    }
                }

                if(spr->type == SpriteOnOffBtn || spr->type == SpriteKaizoBlock) {
                    CUSTOM_DATA_BOX* sprData = (CUSTOM_DATA_BOX*)spr->custom_data;
                    if(CheckCollision(THIS, spr) && THIS->y >= (spr->y) && (player_state == 1 || player_state == 2 || player_state == 3 || player_state == 4) && player_accel_y < 0) {
                        // THIS->y -= 5;
                        player_accel_y = 5;
                       
                        if(player_state == 1 || player_state == 4){
                            player_state = 4;
                            SetSpriteAnim(THIS, anim_jump, 20);
                        }else{
                            player_state = 3;
                            SetSpriteAnim(THIS, anim_spin, 20);
                        }
                        PlayFx(CHANNEL_1, 20, 0x1C, 0x8D, 0xF1, 0xD6, 0x86);
                        PlayFx(CHANNEL_4, 20, 0x3A, 0x91, 0x40, 0xC0);
                        if(sprData->state == 0){
                            sprData->state = 1;
                        }
                        
                        
                    }
                }
                // if(( spr->type == SpriteSpinOrbRooftop)  && player_accel_y > 0) {
                //     CUSTOM_DATA_ORB* sprData = (CUSTOM_DATA_ORB*)spr->custom_data;
                //     if(CheckCollision(THIS, spr) && THIS->y < (spr->y - 5) && (player_state == 2 || player_state == 3 || (player_state == 10 && player_last_state == 2))) {
                //         player_state = 3;
                //         player_accel_y = -83;
                //         if(sprData->state == 2 ){
                //             sprData->state = 3;
                //         }else if(sprData->state == 5 ){
                //             sprData->state = 6;
                //         }else if(sprData->state == 1 ){
                //             sprData->state = 4;
                //         }
                //         else if(sprData->state == 8 ){
                //             sprData->state = 7;
                //         }else if(sprData->state == 0 ){
                //             sprData->state = 9;
                //         }
                //         else if(sprData->state == 12 ){
                //             sprData->state = 11;
                //         }else if(sprData->state == 14 ){
                //             sprData->state = 13;
                //         }else if(sprData->state == 17 ){
                //             sprData->state = 16;
                //         }
                //         // else if(sprData->state == 6){
                //         //     sprData->state = sprData->initial_state;
                //         // }
                //         PlayFx(CHANNEL_4, 10, 0x02, 0xf1, 0x40, 0xc0);
                //         SetSpriteAnim(THIS, anim_spin, 20);
                //         SpriteManagerAdd(SpritePlayerVfx, THIS->x - 4, THIS->y + 8);
                //     }
                // }

                // if(spr->type == SpriteCrystalAttack){
                //     if(CheckCollision(THIS, spr)) {
                //         if(canHurt && player_state != 11){
                //             inmunity = 30;
                //             canHurt = 0;
                //             current_life--;
                //             ScreenShake(1,1);
                //             RefreshLife();
                //         }
                //     }
                // }


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
        playerHurtSound();
        SetState(current_state);
    }   

}