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
const UINT8 pos_state_0[] = { 40, 48, 56, 64, 72, 80, 88, 96, 104};
const UINT8 pos_state_1[] = { 120, 128, 136, 144, 152, 160, 168, 176, 182};

// posiciones x de segundo ataque 
const UINT8 pos_state_2[] = { 40, 56, 104, 120, 168, 184};
const UINT8 pos_state_3[] = { 72, 88, 136, 152};

// posiciones x de tercer ataque 
const UINT8 pos_state_4[] = { 40, 72, 104, 136, 168};
const UINT8 pos_state_5[] = { 56, 88, 120, 152, 194};

UINT8 fire_pos_counter = 0;

UINT8 bossFireState = 0;
UINT8 bossFireTimer = 110;
UINT8 patternCounter = 0;

extern UINT8 bossAttackState;
extern Sprite* bossFireAttack_spr;
extern UINT8 bossCanHurt;

void flameSound(){
    PlayFx(CHANNEL_4, 10, 0x3f, 0xf3, 0x90, 0x80);
}

void START()
{
    SetSpriteAnim(THIS, boss_fire_anim, 20);
    bossFireTimer = 110;
    bossFireState = 0;
    patternCounter = 0;
    THIS->lim_y = 80;
    fire_pos_counter = 0;
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
                flameSound();
                if(patternCounter > 0){
                    bossCanHurt = 0;
                    Attacks_Animations(7);
                    Attacks_Animations(8); 
                }   
            }
            if(THIS->y == 126){
                Attacks_Animations(1);
                bossCanHurt = 1;
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
                flameSound();
                bossCanHurt = 0;
                Attacks_Animations(2);
                Attacks_Animations(5);
            }
            if(THIS->y == 126){
                Attacks_Animations(4);
                Attacks_Animations(6);
                bossCanHurt = 2;
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
                    bossCanHurt = 0;
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
                flameSound();
                if(patternCounter > 5){
                    bossCanHurt = 0;
                   Attacks_Animations(17);
                   Attacks_Animations(18); 
                }   
            }
            if(THIS->y == 126){
                bossCanHurt = 3;
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
                bossCanHurt = 0;
                flameSound();
                Attacks_Animations(15);
                Attacks_Animations(12);
                Attacks_Animations(13); 
            }
            if(THIS->y == 126){
                bossCanHurt = 4;
                Attacks_Animations(16);
                Attacks_Animations(14);
                flameSound();
                
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
                    bossCanHurt = 0;
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
                flameSound();
                if(patternCounter > 10){
                    bossCanHurt = 0;
                    Attacks_Animations(27);
                    Attacks_Animations(28); 
                }
    
            }
            if(THIS->y == 126){
                Attacks_Animations(21);
                bossCanHurt = 5;
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
                 bossCanHurt = 0;
                 flameSound();
                Attacks_Animations(25);
                Attacks_Animations(22);
                Attacks_Animations(23);
            }
            if(THIS->y == 126){
                bossCanHurt = 6;
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
                     bossCanHurt = 0;
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