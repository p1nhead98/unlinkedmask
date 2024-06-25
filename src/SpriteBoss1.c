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
IMPORT_TILES(bossIdleGround);

const UINT8 boss_flyidle[] = {3, 0, 1, 2};
const UINT8 boss_6frames[] = {6, 0, 1, 2, 0, 1, 2};
INT8 boss_state = 0;
UINT8 boss_counter = 0;
UINT8 cantChangeAnim = 0;
extern Sprite* bossFireAttack_spr;

void START()
{

    SetSpriteAnim(THIS, boss_flyidle, 20);
    boss_state = 0;
    boss_counter = 0;
    cantChangeAnim = 0;
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
                THIS->x = 64;
                Set_Sprite_Tiles(&bossFalling, BANK(bossFalling), 48, THIS->first_tile);
            }
            break;
        case 5:
            if(TranslateSprite(THIS, 0, 3)){
                boss_state++;
                Set_Sprite_Tiles(&bossHitGround, BANK(bossHitGround), 48, THIS->first_tile);
                SetSpriteAnim(THIS, boss_flyidle, 20);
                // Set_Sprite_Tiles(&bossCanHit, BANK(bossCanHit), 48, THIS->first_tile);

            }
            break;
        case 6:
            if(THIS->anim_frame == 2){
                boss_state++;
                Set_Sprite_Tiles(&bossIdleGround, BANK(bossIdleGround), 48, THIS->first_tile);
            }
            break;
    }   
     
}

void DESTROY()
{
}