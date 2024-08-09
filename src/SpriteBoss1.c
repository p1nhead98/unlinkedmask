#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"
#include "TileAnimation.h"
#include "BossAttacks.h"
#include "Dialogos.h"
#include "Misc.h"
#include "WinController.h"

//ANIMATION TILES
IMPORT_TILES(bossFalling);
IMPORT_TILES(bossFlyUp);
IMPORT_TILES(bossCanHit);
IMPORT_TILES(bossCanHit2);
IMPORT_TILES(bossHitGround);
IMPORT_TILES(bossCharge);
IMPORT_TILES(bossIdleGround);
IMPORT_TILES(bossFlySide);
IMPORT_TILES(bossFlyIdle);
IMPORT_TILES(bossFrontIdle);

DECLARE_MUSIC(unlinkedboss);

const UINT8 boss_flyidle[] = {3, 0, 1, 2};
const UINT8 boss_6frames[] = {6, 0, 1, 2, 0, 1, 2};
const UINT8 boss_4frames[] = {4, 0, 1, 2, 2};
const UINT8 boss_6frames2[] = {6, 0, 1, 0, 1, 0 ,1};


const UINT8 boss_poss_1[] = { 64, 112};

const UINT8 warn2_sounds[] = { 0x9e, 0xf1, 0x4e, 0x26 };

INT8 boss_state = 0;
UINT8 boss_counter = 0;
UINT8 boss_counter2 = 0;
UINT8 boss_counter3 = 0;
UINT8 cantChangeAnim = 0;

extern Sprite* bossFireAttack_spr;
extern Sprite* player_sprite;
extern UINT8 current_level;
UINT8 AnimCounter2 = 0;
extern UINT8 dialog;
extern UINT8 player_cs_state;
extern UINT8 player_state;

extern UINT8 state_interrupts;
extern UINT8 dialog_pos;
extern UINT8 IsCutscene;

Sprite* bossSkullFlame_spr1 = 1;
Sprite* bossSkullFlame_spr2 = 1;

Sprite* warning_spr = 1;
Sprite* warning_spr2 = 1;

UINT16 boss_y_1 = 0;
UINT16 boss_y_2 = 0;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    SetSpriteAnim(THIS, boss_flyidle, 15);
    
    boss_counter = 0;
    boss_counter2 = 0;
    boss_counter3 = 0;
    cantChangeAnim = 0;
    warning_spr = 1;
    warning_spr2 = 1;
    THIS->lim_y = 140;
    THIS->lim_x = 140;
    boss_y_1 = 0;
    boss_y_2 = 0;
    if(current_level == 32){
        Set_Sprite_Tiles(&bossIdleGround, BANK(bossIdleGround), 48, THIS->first_tile);
        data->state = 54;
    }else if(current_level == 34){
        if(IsCutscene == 1){
            data->state = 58;
            boss_counter = 50;
        }else{
            data->state = 60;
            boss_counter = 50;
        }
        
    }

}

void UPDATE()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    // if(KEY_TICKED(J_LEFT)){
    //     Set_Sprite_Tiles(&tiles2, BANK(tiles2), 6, THIS->first_tile);
    //     THIS->x-=2;
    // }

    switch(data->state){
        
        case 0:
            if(bossFireAttack_spr == 0){
                data->state++;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
            break;
        case 1:
            if(TranslateSprite(THIS, 0, 3)){
                data->state++;
                SetSpriteAnim(THIS, boss_6frames, 20);
                Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);

            }
            break;  
        case 2:
            if(boss_counter != 50){
                boss_counter = 50;
            }
            break;
        case 3:
            if(--boss_counter == 0){
                data->state++;
                Set_Sprite_Tiles(&bossFlyUp, BANK(bossFlyUp), 48, THIS->first_tile);
                 PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);

            }
            break;
        case 4:
            THIS->y-=3;
            if(THIS->y < 2){
                data->state++;
                THIS->x = 112;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
                boss_counter = 20;
            }
            break;
        case 5:
            if(--boss_counter == 0){
                data->state++;
                boss_counter = 60;
                warning_spr = SpriteManagerAdd(SpriteWarning, 112, 24);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 112, 14);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 2;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
                    
        break;
        case 6:
            if(warning_spr == 0 && warning_spr2 == 0){
                if(TranslateSprite(THIS, 0, 3)){
                    
                    data->state++;
                    Set_Sprite_Tiles(&bossHitGround, BANK(bossHitGround), 48, THIS->first_tile);
                    SetSpriteAnim(THIS, boss_4frames, 20);
                    if(THIS->x < player_sprite->x){
                        THIS->mirror = V_MIRROR;
                    }else{
                        THIS->mirror = NO_MIRROR;
                    }
                    ScreenShake(1,1);
                    PlayFx(CHANNEL_4, 25, 0x3a, 0xf3, 0x62, 0x80);
                    bossSkullFlame_spr1 = SpriteManagerAdd(SpriteSkullFlame, THIS->x - 18, THIS->y - 4);
                    CUSTOM_DATA* dataFlame1 = (CUSTOM_DATA*)bossSkullFlame_spr1->custom_data;
                    dataFlame1->state = 0;
                    bossSkullFlame_spr2 = SpriteManagerAdd(SpriteSkullFlame, THIS->x + 16, THIS->y - 4);
                    CUSTOM_DATA* dataFlame2 = (CUSTOM_DATA*)bossSkullFlame_spr2->custom_data;
                    dataFlame2->state = 1;
                    // Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);
                }
            }
            break;
        case 7:
            if(THIS->anim_frame == 3){
                
                data->state++;
                SetSpriteAnim(THIS, boss_flyidle, 20);
                Set_Sprite_Tiles(&bossIdleGround, BANK(bossIdleGround), 48, THIS->first_tile);
                
            }
            break;
        case 8:
            if(THIS->x < player_sprite->x){
                    THIS->mirror = V_MIRROR;
                }else{
                    THIS->mirror = NO_MIRROR;
                }
                
            if(bossSkullFlame_spr1 == 0 && bossSkullFlame_spr2 == 0){
                data->state++;
                Set_Sprite_Tiles(&bossCharge, BANK(bossCharge), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_6frames2, 20);
                
            }
            break;
        case 9:
            if(THIS->anim_frame == 5){
                data->state++;
                Set_Sprite_Tiles(&bossFlySide, BANK(bossFlySide), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_flyidle, 20);
                 PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
            break;
        case 10:
            if(THIS->mirror == V_MIRROR){
                THIS->x+=3;
                if(THIS->x > 210){
                    data->state++;
                    boss_counter = 60;
                }
            }else{
                THIS->x-=3;
                if(THIS->x < 15){
                    data->state++;
                    boss_counter = 60;
                }
            }
            break;
        case 11:
            if(THIS->x < 15){
                if(--boss_counter == 0){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = SpriteManagerAdd(SpriteWarning, 24, 136);
                    CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                    warningData->state = 1;
                    warning_spr2 = SpriteManagerAdd(SpriteWarning, 11, 136);
                    CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                    warningData2->state = 1;
                }
            }else{
                if(--boss_counter == 0){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = SpriteManagerAdd(SpriteWarning, 216, 136);
                    CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                    warningData->state = 0;
                    warning_spr2 = SpriteManagerAdd(SpriteWarning, 228, 136);
                    CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                    warningData2->state = 0;
                }
            }
            break;
        case 12:
            if(THIS->x < 15){
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = V_MIRROR;
                     PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                }
            }else{
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = NO_MIRROR;
                     PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                }
            }
            
            break;
        case 13:
            if(THIS->mirror == V_MIRROR){
                THIS->x+=3;
                if(THIS->x > 210){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = warning_spr2 = 1;
                }
            }else{
                THIS->x-=3;
                if(THIS->x < 15){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = warning_spr2 = 1;
                }
            }
            
            break;
        case 14:

            if(THIS->mirror == V_MIRROR){
                if(--boss_counter == 0){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = SpriteManagerAdd(SpriteWarning, 216, 136);
                    CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                    warningData->state = 0;
                    warning_spr2 = SpriteManagerAdd(SpriteWarning, 228, 136);
                    CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                    warningData2->state = 0;
                }
            }else{
                if(--boss_counter == 0){
                    data->state++;
                    boss_counter = 60;
                    warning_spr = SpriteManagerAdd(SpriteWarning, 24, 136);
                    CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                    warningData->state = 1;
                    warning_spr2 = SpriteManagerAdd(SpriteWarning, 11, 136);
                    CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                    warningData2->state = 1;
                }
            }
     
            break;
        case 15:
            if(THIS->mirror == V_MIRROR){
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = NO_MIRROR;
                     PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                }  
            }else{
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = V_MIRROR;
                     PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                    
                }    
            }
            
            break;
        case 16:
            if(THIS->mirror == NO_MIRROR){
                THIS->x-=3;
                if(THIS->x < 15){
                    data->state++;
                    boss_counter = 30;
                    THIS->x = 112;
                    THIS->y = 0;
                    Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
                    boss_counter = 60;
            
                }
            }else{
                THIS->x+=3;
                if(THIS->x > 210){
                    data->state++;
                    boss_counter = 30;
                    THIS->x = 112;
                    THIS->y = 0;
                    Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
                    boss_counter = 60;
              
                }
            }
            
            break;
  
        case 17:
            THIS->x = player_sprite->x;
            if(--boss_counter == 0){
                boss_counter = 50;
                boss_counter2++;
                SpriteManagerAdd(SpriteWarning2, player_sprite->x - 4, player_sprite->y);
                PlayFx(CHANNEL_1, 10, 0x2c, 0xbf, 0xf1, warn2_sounds[boss_counter2], 0x87);
            }
            if(boss_counter2 == 4){
                data->state++;
                boss_counter = 30;
            }
            break;
        case 18:
            if(--boss_counter == 0){
                data->state++;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
            break;
        case 19:
            if(TranslateSprite(THIS, 0, 4)){
                data->state++;
                Set_Sprite_Tiles(&bossHitGround, BANK(bossHitGround), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_4frames, 20);
                if(THIS->x < player_sprite->x){
                    THIS->mirror = V_MIRROR;
                }else{
                    THIS->mirror = NO_MIRROR;
                }
                ScreenShake(1,1);
                PlayFx(CHANNEL_4, 25, 0x3a, 0xf3, 0x62, 0x80);
                bossSkullFlame_spr1 = SpriteManagerAdd(SpriteSkullFlame, THIS->x - 18, THIS->y - 4);
                CUSTOM_DATA* dataFlame1 = (CUSTOM_DATA*)bossSkullFlame_spr1->custom_data;
                dataFlame1->state = 0;
                bossSkullFlame_spr2 = SpriteManagerAdd(SpriteSkullFlame, THIS->x + 16, THIS->y - 4);
                CUSTOM_DATA* dataFlame2 = (CUSTOM_DATA*)bossSkullFlame_spr2->custom_data;
                dataFlame2->state = 1;
            }
            break;
        case 20:
            if(THIS->anim_frame == 3){
                
                data->state++;
                SetSpriteAnim(THIS, boss_6frames, 20);
                Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);
                
            }
            break;
        case 21:
            if(boss_counter != 50){
                boss_counter = 50;
            }
            break;
        case 22:
            if(--boss_counter == 0){
                data->state++;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                Set_Sprite_Tiles(&bossFlyUp, BANK(bossFlyUp), 48, THIS->first_tile);

            }
            break;
        case 23:
            THIS->y-=4;
            if(THIS->y < 2){
                data->state++;
                boss_counter = 10;
                boss_counter2 = 0;
                // Attacks_Animations(31);
            }
            break;
        case 24:
            if(--boss_counter == 0){
                boss_counter = 4;
                if(boss_counter2 % 2 == 0){
                    Attacks_Animations(31);
                }else{
                    Attacks_Animations(30);
                }
                boss_counter2++;
                AnimCounter2 = 1;
                if(boss_counter2 == 7){
                    data->state++;
                    boss_state = 25;
                    Attacks_Animations(31);
                    PlayFx(CHANNEL_1, 15, 0x1b, 0x3f, 0xf1, 0x9e, 0x87);
                    boss_counter = 10;
                }
            }
            break;
        case 25:
            if(boss_state == 26){
                data->state++;
            }
            break;
        case 26:
            if(boss_counter > 0){
                if(boss_counter == 5){
                    Attacks_Animations(32);
                    PlayFx(CHANNEL_4, 10, 0x3f, 0xf3, 0x90, 0x80);
                }
                boss_counter--;
            }else{
                Attacks_Animations(33);
                data->state++;
                boss_counter = 50;
                warning_spr = 1;
                warning_spr2 = 1;
            }
            break;
        case 27:
            if(--boss_counter == 0){
                data->state++;
                warning_spr = SpriteManagerAdd(SpriteWarning, 160, 24);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 160, 14);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 2;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
                THIS->mirror = V_MIRROR;
            }
            break;
        case 28:
            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                THIS->x = 160;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                // THIS->mirror = H_MIRROR;
            }
            break;
        case 29:
            THIS->y += 4;
            if(THIS->y > 192){
                boss_y_1 = THIS->y;
                data->state++;
                boss_counter = 50;
                
            }
            break;
        case 30:
            if(--boss_counter == 0){
                data->state++;
                warning_spr = SpriteManagerAdd(SpriteWarning, 112, 184);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 3;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 112, 194);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 3;
                Set_Sprite_Tiles(&bossFlyUp, BANK(bossFlyUp), 48, THIS->first_tile);
                
            }
            break;
        case 31:
            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                THIS->x = 112;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                // THIS->mirror = H_MIRROR;
            }
            break;
        case 32:
            THIS->y -= 4;
            if(THIS->y < 5){
                data->state++;
                boss_counter = 50;
                boss_y_2 = THIS->y;
            }
            break;
         case 33:
            if(--boss_counter == 0){
                data->state++;
                warning_spr = SpriteManagerAdd(SpriteWarning, 64, 24);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 64, 14);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 2;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
            }
            break;
        case 34:
            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                THIS->x = 64;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                // THIS->mirror = H_MIRROR;
            }
            break;
        case 35:
            THIS->y += 4;
            if(THIS->y > 192){
                data->state++;
                boss_counter = 50;
                warning_spr = 1;
                warning_spr2 = 1;
            }
            break;
        
        case 36:
            if(--boss_counter == 0){
                data->state++;
                warning_spr = SpriteManagerAdd(SpriteWarning, 64, 184);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 3;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 64, 194);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 3;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);

                warning_spr = SpriteManagerAdd(SpriteWarning, 112, 24);
                CUSTOM_DATA* warningData3 = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData3->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 112, 14);
                CUSTOM_DATA* warningData4 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData4->state = 2;
           
            }
            break;

        case 37:
            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                THIS->x = 64;
                warning_spr = SpriteManagerAdd(SpriteBoss1, 112, boss_y_2);
                CUSTOM_DATA_BTN* bossData2 = (CUSTOM_DATA_BTN*)warning_spr->custom_data;
                bossData2->state = 80;
                THIS->mirror = H_MIRROR;
                 PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
            break;
        case 38:
            THIS->mirror = H_MIRROR;
            THIS->y -= 4;

            if(THIS->y < 5){
                data->state++;
                boss_counter = 50;
            }
        
            

            
            
            break;

        case 39:
            if(--boss_counter == 0){
                data->state++;

                warning_spr = SpriteManagerAdd(SpriteWarning, 64, 24);
                CUSTOM_DATA* warningData3 = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData3->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 64, 14);
                CUSTOM_DATA* warningData4 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData4->state = 2;

                warning_spr = SpriteManagerAdd(SpriteWarning, 112, 184);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 3;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 112, 194);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 3;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);

                warning_spr = SpriteManagerAdd(SpriteWarning, 160, 24);
                CUSTOM_DATA* warningData5 = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData5->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 160, 14);
                CUSTOM_DATA* warningData6 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData6->state = 2;
           
            }
            break;

        case 40:

            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                THIS->x = 64;
                warning_spr = SpriteManagerAdd(SpriteBoss1, 112, 184);
                CUSTOM_DATA_BTN* bossData2 = (CUSTOM_DATA_BTN*)warning_spr->custom_data;
                bossData2->state = 81;
                warning_spr2 = SpriteManagerAdd(SpriteBoss1, 160, THIS->y);
                CUSTOM_DATA_BTN* bossData3 = (CUSTOM_DATA_BTN*)warning_spr2->custom_data;
                bossData3->state = 80;
                THIS->mirror = NO_MIRROR;
                PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
            }
            
            break;
        case 41:
    
            THIS->y += 4;
            if(THIS->y > 192){
                data->state++;
                boss_counter = 10;
                boss_counter2 = 0;
                boss_counter3 = 10;
            }
            break;
        case 43:
            if(boss_counter3 > 0){
                if(boss_counter3 == 5){
                    Attacks_Animations(34);
                }
                boss_counter3--;
            }else{
                Attacks_Animations(35);
                data->state++;
            }
        break;
        case 42:
          
            
            if(--boss_counter == 0){
                boss_counter = 4;
                if(boss_counter2 % 2 == 0){
                    Attacks_Animations(31);
                }else{
                    Attacks_Animations(30);
                }
                boss_counter2++;
                if(boss_counter2 == 7){
                    data->state++;
                    boss_state = data->state;
                
                    Attacks_Animations(30);
                    boss_counter = 50;
                }
            }
            break;
        case 44:
            if(--boss_counter == 0){
                data->state++;
                boss_counter = 60;
                warning_spr = SpriteManagerAdd(SpriteWarning, 112, 24);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 2;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 112, 14);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 2;
                THIS->x = 112;
                THIS->y = 0;
            }
            break;
            
        case 45:
            if(warning_spr == 0 && warning_spr2 == 0){
                data->state++;
                boss_counter = 30;
              PlayFx(CHANNEL_1, 15, 0x1D, 0x94, 0xf3, 0xd6, 0x86);
                // THIS->mirror = H_MIRROR;
            }
            break;

        case 46:
           
                if(TranslateSprite(THIS, 0, 4)){
                    data->state++;
                    ScreenShake(1,1);
                    PlayFx(CHANNEL_4, 25, 0x3a, 0xf3, 0x62, 0x80);
                    Set_Sprite_Tiles(&bossHitGround, BANK(bossHitGround), 48, THIS->first_tile);
                    SetSpriteAnim(THIS, boss_4frames, 20);
                    if(THIS->x < player_sprite->x){
                        THIS->mirror = V_MIRROR;
                    }else{
                        THIS->mirror = NO_MIRROR;
                    }
                }
            
            break;
        case 47:
            if(THIS->anim_frame == 3){
                
                data->state = 48;
                SetSpriteAnim(THIS, boss_6frames, 20);
                Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);
                
            }
            break;
        case 48:
            if(boss_counter != 50){
                boss_counter = 50;
            }
            break;
        case 49:
            if(--boss_counter == 0){
                Set_Sprite_Tiles(&bossFlySide, BANK(bossFlySide), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_flyidle, 20);
                data->state++;
                THIS->mirror = NO_MIRROR;
             
            }
            break;
        case 50:
            THIS->x-=3;
            if(THIS->x < 15){
                data->state++;
                boss_counter = 60;
            }
        break;
        case 51:
            if(--boss_counter == 0){
                THIS->y -= 50;
                Set_Sprite_Tiles(&bossFlyIdle, BANK(bossFlyIdle), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_flyidle, 20);
                data->state++;
                THIS->mirror = V_MIRROR;
                 
            }
            break;
        case 52:
            if(THIS->x < 111){
                THIS->x+=2;
            }else{
                data->state++;
                Set_Sprite_Tiles(&bossFrontIdle, BANK(bossFrontIdle), 48, THIS->first_tile);
                boss_counter = 50;
            }
            
            break;
        case 53:
            if(--boss_counter == 0){
                data->state = 61;
                IsCutscene = 5;
                boss_counter2 = 0;
                boss_counter = 5;
            }
            break;

        case 54: // CINEMATICA
            if(player_cs_state == 8){
                data->state++;
                boss_counter = 40;
            }
            break;
        case 55:
            if(--boss_counter == 0){
                data->state++;
                PlayFx(CHANNEL_4, 15, 0x3f, 0xf1, 0x24, 0xc0);
                PlayFx(CHANNEL_1, 15, 0x53, 0x82, 0x52, 0x88, 0x84);
                Set_Sprite_Tiles(&bossFlyIdle, BANK(bossFlyIdle), 48, THIS->first_tile);
            }
            break;
        case 56:
            if(THIS->y < 80){
                data->state++;
                boss_counter = 40;
                Set_Sprite_Tiles(&bossFrontIdle, BANK(bossFrontIdle), 48, THIS->first_tile);
               
            }else{
                THIS->y--;
            }
            break;

        case 57:
            if(--boss_counter == 0){
                current_level++;
		        SetState(current_state);
           
            }
            break;

        case 58:
            if(--boss_counter == 0){
                data->state++;
				CleanWin();
				dialog_pos = 120;
				dialog = 1;
				WY_REG = dialog_pos;
				state_interrupts = 1;
				LYC_REG = 0;
                boss_counter = 50;
            }
            break;
        case 59:
            if(boss_state == 60){
                data->state++;
            } 
            break;
        case 60:
            if(--boss_counter == 0){
                if(IsCutscene == 1){
                    IsCutscene = 0;
                    SetHudWin(1);
                }
                data->state = 0;
                PlayMusic(unlinkedboss, 1);
                bossFireAttack_spr = SpriteManagerAdd(SpriteBossFireFlash, 0, 138);
                // data->state++;
				// CleanWin();
				// dialog_pos = 120;
				// dialog = 1;
				// WY_REG = dialog_pos;
				// state_interrupts = 1;
				// LYC_REG = 0;
            }
            break;







        case 61:
            if(boss_counter2 < 4){
                if(--boss_counter == 0){
                    FadeMusic(boss_counter2);
                    boss_counter2++;
                    boss_counter = 20;
                }
            }else{
                data->state++;
                player_state = 15;
                NR52_REG = 0x80; //Enables sound, you should always setup this first
                NR51_REG = 0xFF; //Enables all channels (left and right)
                NR50_REG = 0x77; //Max volume
            }
            break;
        case 62:
            break;

        case 80:
            THIS->y += 4;
        break;
    
        case 81:
            THIS->mirror = H_MIRROR;
            THIS->y -= 4;
        break;
            
        //  case 16:
        //     if(--boss_counter == 0){
        //         boss_state++;
        //         boss_counter = 60;
        //         warning_spr = SpriteManagerAdd(SpriteWarning, 216, 136);
        //         CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
        //         warningData->state = 0;
        //         warning_spr2 = SpriteManagerAdd(SpriteWarning, 228, 136);
        //         CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
        //         warningData2->state = 0;
        //     }
        //     break;
        // case 17:
        //     if(warning_spr == 0 && warning_spr2 == 0){
        //         boss_state++;
        //         THIS->mirror = NO_MIRROR;
        //     }
        //     break;
        // case 18:
        //     THIS->x-=3;
        //     if(THIS->x < 15){
        //         boss_state++;
        //         boss_counter = 60;
        //         warning_spr = warning_spr2 = 1;
        //     }
        //     break;
    }   
     
}

void DESTROY()
{
}