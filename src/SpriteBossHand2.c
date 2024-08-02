#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

extern UINT8 door_time;
extern UINT8 door_open;

const UINT8 hand2anim[] = {3, 0, 1, 2};
const UINT8 hand2anim2[] = {1, 3};

// posiciones x de fuego ataque 
const UINT8 hand_boss_patter[] = { 16, 48, 80, 112};
const UINT8 hand_boss_patter2[] = { 32, 64, 96, 128};
const UINT8 hand_boss_patter3[] = { 16, 32, 80, 96};
const UINT8 hand_boss_patter4[] = { 48, 64, 112, 128};

UINT8 BossH2Counter = 0;
UINT8 BossH2State = 0;
INT16 BossH2InitY = 0;
UINT8 BossH2Counter2 = 0;

void START()
{
     SetSpriteAnim(THIS, hand2anim, 16);
     BossH2Counter = 50;
     BossH2State = 0;
     BossH2InitY = THIS->y;
     BossH2Counter2 = 0;
}

void UPDATE()
{

     // switch (BossH2State)
     // {
     // case 0:
     //      if(--BossH2Counter == 0){
     //           BossH2Counter = 18;
     //           BossH2State++;
     //           SetSpriteAnim(THIS, hand2anim2, 16);
     //      }
     //      break;
     // case 1:
     //      if( BossH2Counter > 0 ){
     //           BossH2Counter--;
     //           THIS->y--;
     //      }else{
     //           BossH2State++;
     //      }
     //      break;
     // case 2:
     //      if(TranslateSprite(THIS, 0 , 4)){
     //           BossH2State++;
     //           ScreenShake(1,1);
     //           BossH2Counter = 50;


     //           switch (BossH2Counter2)
     //           {
     //           case 0:
     //                for (UINT8 i = 0; i < 4; i++)
     //                {
     //                     SpriteManagerAdd(SpriteBossFire, hand_boss_patter[i], 0);
     //                }
     //                break;
     //           case 1:
     //                for (UINT8 i = 0; i < 4; i++)
     //                {
     //                     SpriteManagerAdd(SpriteBossFire, hand_boss_patter2[i], 0);
     //                }
     //                break;
     //           case 2:
     //                for (UINT8 i = 0; i < 4; i++)
     //                {
     //                     SpriteManagerAdd(SpriteBossFire, hand_boss_patter3[i], 0);
     //                }
     //                break;
     //           case 3:
     //                for (UINT8 i = 0; i < 4; i++)
     //                {
     //                     SpriteManagerAdd(SpriteBossFire, hand_boss_patter4[i], 0);
     //                }
     //                break;
     //           }

     //           if(BossH2Counter2 < 3){
     //                BossH2Counter2++;
     //           }else{
     //                BossH2Counter2 = 0;
     //           }
               
               
     //      }
     //      break;
     // case 3:
     //      if(--BossH2Counter == 0){
     //           BossH2Counter = 50;
     //           BossH2State++;
     //           SetSpriteAnim(THIS, hand2anim, 16);
     //      }
     //      break;
     // case 4:
     //      if(THIS->y > BossH2InitY){
     //           THIS->y--;
     //      }else{
     //           BossH2State = 0;
         
     //      }
     //      break;
     // default:
     //      break;
     // }

     // if(BossH2State == 0 && --BossH2Counter == 0 ){
     //      if(TranslateSprite(THIS, 0, 4)){
     //           BossH2State = 1;
     //           BossH2Counter = 50;
     //      }
     // }
     // if(BossH2State == 1 && --BossH2Counter == 0 ){
     //      if(THIS->y > BossH2InitY){
     //           THIS->y--;
     //      }else{
     //           BossH2State = 0;
     //           BossH2Counter = 50;
     //      }
     // }
     
}

void DESTROY()
{
}