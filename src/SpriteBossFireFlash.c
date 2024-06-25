#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"
#include "BossAttacks.h"


const UINT8 boss_fire_anim[] = {2, 0, 1};

// posiciones x de primer ataque 
const UINT8 pos_state_0[] = { 0, 8, 16, 24, 32, 40, 48, 56, 64};
const UINT8 pos_state_1[] = { 80, 88, 96, 104, 112, 120, 128, 136, 142};

// posiciones x de segundo ataque 
const UINT8 pos_state_2[] = { 0, 16, 64, 80, 128, 144};
const UINT8 pos_state_3[] = { 32, 48, 96, 112};

// posiciones x de tercer ataque 
const UINT8 pos_state_4[] = { 0, 32, 64, 96, 128};
const UINT8 pos_state_5[] = { 16, 48, 80, 112, 144};

UINT8 fire_pos_counter = 0;

UINT8 bossFireState = 0;
UINT8 bossFireTimer = 110;
UINT8 patternCounter = 0;

extern UINT8 bossAttackState;
extern Sprite* bossFireAttack_spr;
void START()
{
    SetSpriteAnim(THIS, boss_fire_anim, 20);
    bossFireTimer = 110;
    patternCounter = 0;
    THIS->lim_y = 80;
}

void UPDATE()
{
    switch(bossFireState){
        case 0:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
            }
            THIS->x = pos_state_0[fire_pos_counter];
            if(++fire_pos_counter == 9){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_0[fire_pos_counter];
            break;
        case 1:
            if(THIS->y > 124){
                THIS->y--;
            }else{
                bossFireState++;
                patternCounter++;
                THIS->y = 138;
                THIS->x = pos_state_1[0];
            }
            if(THIS->y == 134){
                Attacks_Animations(0);
                if(patternCounter > 0){
                   Attacks_Animations(7);
                   Attacks_Animations(8); 
                }   
            }
            if(THIS->y == 126){
                Attacks_Animations(1);
                if(patternCounter > 0){
                    Attacks_Animations(9);
                }
            }
            THIS->x = pos_state_0[fire_pos_counter];
            if(++fire_pos_counter == 9){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_0[fire_pos_counter];
            break;
        case 2:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
            }
            THIS->x = pos_state_1[fire_pos_counter];
            if(++fire_pos_counter == 9){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_1[fire_pos_counter];
            break;
        case 3:
            if(THIS->y > 124){
                THIS->y--;
            }else{
                if(patternCounter < 4){
                    bossFireState = 0;
                    patternCounter++;
                    THIS->y = 138;
                    THIS->x = pos_state_0[0];
                }else{
                    bossFireState++;
                    bossAttackState = 1;
                    THIS->y = 188;
                    bossFireTimer = 50;
                }
            }
            if(THIS->y == 134){
                Attacks_Animations(3);
                Attacks_Animations(2);
                Attacks_Animations(5);
            }
            if(THIS->y == 126){
                Attacks_Animations(4);
                Attacks_Animations(6);
            }
            THIS->x = pos_state_1[fire_pos_counter];
            if(++fire_pos_counter == 9){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_1[fire_pos_counter];
            break;
        case 4:
            if(--bossFireTimer == 0){
                bossFireTimer = 16;
                bossFireState++;
            }
            
            break;
        case 5:
            if(bossFireTimer > 0){
                bossFireTimer--;
                if(bossFireTimer == 12){
                    Attacks_Animations(8);
                    Attacks_Animations(7);
                }else if(bossFireTimer == 4){
                    Attacks_Animations(9);
                }
            }else{
                bossFireState++;
                bossFireTimer = 110;
                THIS->x = 0;
                THIS->y = 138;
            }
            break;
        case 6:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
            }
            THIS->x = pos_state_2[fire_pos_counter];
            if(++fire_pos_counter == 6){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_2[fire_pos_counter];
            break;
        case 7:
            if(THIS->y > 124){
                THIS->y--;
            }else{
                bossFireState++;
                fire_pos_counter = 0;
                patternCounter++;
                THIS->y = 138;
                THIS->x = pos_state_3[0];
            }
            if(THIS->y == 134){
                Attacks_Animations(10);
                if(patternCounter > 5){
                   Attacks_Animations(17);
                   Attacks_Animations(18); 
                }   
            }
            if(THIS->y == 126){
                Attacks_Animations(11);
                if(patternCounter > 5){
                    Attacks_Animations(19);
                }
            }
            THIS->x = pos_state_2[fire_pos_counter];
            if(++fire_pos_counter == 9){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_2[fire_pos_counter];
            break;
        case 8:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_3[fire_pos_counter];
            if(++fire_pos_counter == 4){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_3[fire_pos_counter];
            break;
        case 9:
            if(THIS->y > 124){
                THIS->y--;
            }else{
               if(patternCounter < 9){
                    bossFireState = 6;
                    patternCounter++;
                    THIS->y = 138;
                    THIS->x = pos_state_2[0];
                }else{
                    bossFireState++;
                    THIS->y = 188;
                    bossFireTimer = 50;
                }
            }
            if(THIS->y == 134){
                Attacks_Animations(15);
                Attacks_Animations(12);
                Attacks_Animations(13); 
            }
            if(THIS->y == 126){
                Attacks_Animations(16);
                Attacks_Animations(14);
                
            }
            THIS->x = pos_state_3[fire_pos_counter];
            if(++fire_pos_counter == 4){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_3[fire_pos_counter];
            break;

        case 10:
            if(--bossFireTimer == 0){
                bossFireTimer = 16;
                bossFireState++;
            }
            
            break;

        case 11:
            if(bossFireTimer > 0){
                bossFireTimer--;
                if(bossFireTimer == 12){
                    Attacks_Animations(18);
                    Attacks_Animations(17);
                }else if(bossFireTimer == 4){
                    Attacks_Animations(19);
                }
            }else{
                bossFireState++;
                bossFireTimer = 110;
                fire_pos_counter = 0;
                THIS->x = 0;
                THIS->y = 138;
            }
            break;

        case 12:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
            }
            THIS->x = pos_state_4[fire_pos_counter];
            if(++fire_pos_counter == 5){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_4[fire_pos_counter];
            break;
        
        case 13:
            if(THIS->y > 124){
                THIS->y--;
            }else{
                bossFireState++;
                patternCounter++;
                THIS->y = 138;
                THIS->x = pos_state_5[0];
            }
            if(THIS->y == 134){
                Attacks_Animations(20);
                if(patternCounter > 10){
                    Attacks_Animations(27);
                    Attacks_Animations(28); 
                }
    
            }
            if(THIS->y == 126){
                Attacks_Animations(21);
                if(patternCounter > 10){
                    Attacks_Animations(29);
                }
                
                
            }
            THIS->x = pos_state_4[fire_pos_counter];
            if(++fire_pos_counter == 4){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_4[fire_pos_counter];
            break;

        case 14:
            if(--bossFireTimer == 0){
                bossFireTimer = 50;
                bossFireState++;
            }
            THIS->x = pos_state_5[fire_pos_counter];
            if(++fire_pos_counter == 5){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_5[fire_pos_counter];
            break;
        case 15:
            if(THIS->y > 124){
                THIS->y--;
            }else{
                if(patternCounter < 14){
                    bossFireState = 12;
                    patternCounter++;
                    THIS->y = 138;
                    THIS->x = pos_state_4[0];
                }else{
                    bossFireState++;
                    bossAttackState = 1;
                    THIS->y = 188;
                    bossFireTimer = 50;
                }
            }
            if(THIS->y == 134){
                Attacks_Animations(25);
                Attacks_Animations(22);
                Attacks_Animations(23);
            }
            if(THIS->y == 126){
                Attacks_Animations(26);
                Attacks_Animations(24);
            }
            THIS->x = pos_state_5[fire_pos_counter];
            if(++fire_pos_counter == 5){
                fire_pos_counter = 0;
            }
            THIS->x = pos_state_5[fire_pos_counter];
            break;

        case 16:
            if(--bossFireTimer == 0){
                bossFireTimer = 16;
                bossFireState++;
            }
            
            break;
        case 17:
            if(bossFireTimer > 0){
                bossFireTimer--;
                if(bossFireTimer == 12){
                    Attacks_Animations(27);
                    Attacks_Animations(28);
                }else if(bossFireTimer == 4){
                    Attacks_Animations(29);
                }
            }else{
                SpriteManagerRemove(THIS_IDX);
                bossFireAttack_spr = 0;
            }
            break;
    }
}

void DESTROY()
{
}