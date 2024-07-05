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


//ANIMATION TILES
IMPORT_TILES(bossFalling);
IMPORT_TILES(bossFlyUp);
IMPORT_TILES(bossCanHit);
IMPORT_TILES(bossCanHit2);
IMPORT_TILES(bossHitGround);
IMPORT_TILES(bossCharge);
IMPORT_TILES(bossIdleGround);
IMPORT_TILES(bossFlySide);

const UINT8 boss_flyidle[] = {3, 0, 1, 2};
const UINT8 boss_6frames[] = {6, 0, 1, 2, 0, 1, 2};
const UINT8 boss_4frames[] = {4, 0, 1, 2, 2};
const UINT8 boss_6frames2[] = {6, 0, 1, 0, 1, 0 ,1};


const UINT8 boss_poss_1[] = { 64, 112};

INT8 boss_state = 0;
UINT8 boss_counter = 0;
UINT8 boss_counter2 = 0;
UINT8 boss_counter3 = 0;
UINT8 cantChangeAnim = 0;
extern Sprite* bossFireAttack_spr;
extern Sprite* player_sprite;
Sprite* bossSkullFlame_spr1 = 1;
Sprite* bossSkullFlame_spr2 = 1;

Sprite* warning_spr = 1;
Sprite* warning_spr2 = 1;

UINT16 boss_y_1 = 0;
UINT16 boss_y_2 = 0;

void START()
{
    CUSTOM_DATA_BTN* data = (CUSTOM_DATA_BTN*)THIS->custom_data;
    SetSpriteAnim(THIS, boss_flyidle, 20);
    data->state = 0;
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
            }
            break;
        case 1:
            if(TranslateSprite(THIS, 0, 2)){
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
                }
            }else{
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = NO_MIRROR;
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
                }  
            }else{
                if(warning_spr == 0 && warning_spr2 == 0){
                    data->state++;
                    THIS->mirror = V_MIRROR;
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
            }
            if(boss_counter2 == 4){
                data->state++;
                boss_counter = 30;
            }
            break;
        case 18:
            if(--boss_counter == 0){
                data->state++;
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
                
                bossSkullFlame_spr1 = SpriteManagerAdd(SpriteSkullFlame, THIS->x - 18, THIS->y);
                CUSTOM_DATA* dataFlame1 = (CUSTOM_DATA*)bossSkullFlame_spr1->custom_data;
                dataFlame1->state = 0;
                bossSkullFlame_spr2 = SpriteManagerAdd(SpriteSkullFlame, THIS->x + 16, THIS->y);
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
                if(boss_counter2 == 7){
                    data->state++;
                    boss_state = 25;
                    Attacks_Animations(31);
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
              
                // THIS->mirror = H_MIRROR;
            }
            break;

        case 46:
           
                if(TranslateSprite(THIS, 0, 4)){
                    data->state++;
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
                
                data->state++;
                SetSpriteAnim(THIS, boss_6frames, 20);
                Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);
                
            }
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