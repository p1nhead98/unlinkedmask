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

INT8 boss_state = 0;
UINT8 boss_counter = 0;
UINT8 cantChangeAnim = 0;
extern Sprite* bossFireAttack_spr;
Sprite* bossSkullFlame_spr1 = 1;
Sprite* bossSkullFlame_spr2 = 1;

Sprite* warning_spr = 1;
Sprite* warning_spr2 = 1;
void START()
{

    SetSpriteAnim(THIS, boss_flyidle, 20);
    boss_state = 0;
    boss_counter = 0;
    cantChangeAnim = 0;
    warning_spr = 1;
    warning_spr2 = 1;
    THIS->lim_y = 140;
    THIS->lim_x = 140;
}

void UPDATE()
{
    // if(KEY_TICKED(J_LEFT)){
    //     Set_Sprite_Tiles(&tiles2, BANK(tiles2), 6, THIS->first_tile);
    //     THIS->x-=2;
    // }

    switch(boss_state){
        
        case 0:
            if(bossFireAttack_spr == 0){
                boss_state++;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
            }
            break;
        case 1:
            if(TranslateSprite(THIS, 0, 2)){
                boss_state++;
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
                boss_state++;
                Set_Sprite_Tiles(&bossFlyUp, BANK(bossFlyUp), 48, THIS->first_tile);

            }
            break;
        case 4:
            THIS->y-=3;
            if(THIS->y < 2){
                boss_state++;
                THIS->x = 112;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
            }
            break;
        case 5:
            if(TranslateSprite(THIS, 0, 3)){
                boss_state++;
                Set_Sprite_Tiles(&bossHitGround, BANK(bossHitGround), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_4frames, 20);
                THIS->mirror = V_MIRROR;
                bossSkullFlame_spr1 = SpriteManagerAdd(SpriteSkullFlame, THIS->x - 18, THIS->y);
                CUSTOM_DATA* dataFlame1 = (CUSTOM_DATA*)bossSkullFlame_spr1->custom_data;
                dataFlame1->state = 0;
                bossSkullFlame_spr2 = SpriteManagerAdd(SpriteSkullFlame, THIS->x + 16, THIS->y);
                CUSTOM_DATA* dataFlame2 = (CUSTOM_DATA*)bossSkullFlame_spr2->custom_data;
                dataFlame2->state = 1;
                // Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);

            }
            break;
        case 6:
            if(THIS->anim_frame == 3){
                boss_state++;
                SetSpriteAnim(THIS, boss_flyidle, 20);
                Set_Sprite_Tiles(&bossIdleGround, BANK(bossIdleGround), 48, THIS->first_tile);
                
            }
            break;
        case 7:
            if(bossSkullFlame_spr1 == 0 && bossSkullFlame_spr2 == 0){
                boss_state++;
                Set_Sprite_Tiles(&bossCharge, BANK(bossCharge), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_6frames2, 20);
                
            }
            break;
        case 8:
            if(THIS->anim_frame == 5){
                boss_state++;
                Set_Sprite_Tiles(&bossFlySide, BANK(bossFlySide), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_flyidle, 20);
            }
            break;
        case 9:
            THIS->x+=3;
            if(THIS->x > 210){
                boss_state++;
                boss_counter = 60;
            }
            break;
        case 10:
            if(--boss_counter == 0){
                boss_state++;
                boss_counter = 60;
                warning_spr = SpriteManagerAdd(SpriteWarning, 216, 136);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 0;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 228, 136);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 0;
            }
            break;
        case 11:
            if(warning_spr == 0 && warning_spr2 == 0){
                boss_state++;
                THIS->mirror = NO_MIRROR;
            }
            break;
        case 12:
            THIS->x-=3;
            if(THIS->x < 15){
                boss_state++;
                boss_counter = 60;
                warning_spr = warning_spr2 = 1;
            }
            break;
        case 13:
            if(--boss_counter == 0){
                boss_state++;
                boss_counter = 60;
                warning_spr = SpriteManagerAdd(SpriteWarning, 24, 136);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 1;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 11, 136);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 1;
            }
            break;
        case 14:  
            if(warning_spr == 0 && warning_spr2 == 0){
                boss_state++;
                THIS->mirror = V_MIRROR;
            }    
            break;
        case 15:
            THIS->x+=3;
            if(THIS->x > 200){
                boss_state++;
                boss_counter = 60;
            }
            break;
         case 16:
            if(--boss_counter == 0){
                boss_state++;
                boss_counter = 60;
                warning_spr = SpriteManagerAdd(SpriteWarning, 216, 136);
                CUSTOM_DATA* warningData = (CUSTOM_DATA*)warning_spr->custom_data;
                warningData->state = 0;
                warning_spr2 = SpriteManagerAdd(SpriteWarning, 228, 136);
                CUSTOM_DATA* warningData2 = (CUSTOM_DATA*)warning_spr2->custom_data;
                warningData2->state = 0;
            }
            break;
        case 17:
            if(warning_spr == 0 && warning_spr2 == 0){
                boss_state++;
                THIS->mirror = NO_MIRROR;
            }
            break;
        case 18:
            THIS->x-=3;
            if(THIS->x < 15){
                boss_state++;
                boss_counter = 60;
                warning_spr = warning_spr2 = 1;
            }
            break;
    }   
     
}

void DESTROY()
{
}