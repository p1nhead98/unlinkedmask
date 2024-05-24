#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"


extern UINT8 current_level;
extern UINT8 start_screen;

void CheckCollisionOrb(CUSTOM_DATA_ORB* data)
{
    
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    UINT8 colision2 = GetScrollTile((THIS->x ) >> 3, (THIS->y + 6u) >> 3);
    // if(data->state == 2){
    //     colision = GetScrollTile((THIS->x + 12) >> 3, (THIS->y + 4u) >> 3);
    // }else if (data->state == 3){
    //     colision = data->initial_speed == 3 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 2u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 3u) >> 3);
    // }else if(data->state == 4){
    //     colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    // }else
    if(data->state == 3){
        colision =  GetScrollTile((THIS->x + 12u) >> 3, (THIS->y + 4u) >> 3) ;
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x ) >> 3, (THIS->y + 6u) >> 3);
    }else if(data->state == 5){
        colision = GetScrollTile((THIS->x + 4u) >> 3, (THIS->y + 4u) >> 3) ;
    }

    if(colision2 == 104 && data->initial_state != 6){
        data->initial_state = data->state = 6;
    }

    if(colision == 103 && data->initial_state != 7){
        data->initial_state = data->state = 7;
    }

    if(colision == 102 && data->initial_state != 8){
        data->initial_state = data->state = 8;
    }

    if(colision == 101 && data->initial_state != 9){
        data->initial_state = 9; 
       data->state = 9;
    }
    // if(colision == 116 ){
    //     SpriteManagerRemove(THIS_IDX);
    // }

    // if(colision == 92 && data->state != 7 ){
    //     data->state = 7;
    // }else if( colision == 101 && data->state != 2 ){
    //     data->initial_state = 2;
    //     data->state = 6;
    //     data->initial_speed = 2;
    // }else if( colision == 102 && data->state != 5 ){
    //     data->initial_state = 5;
    //     data->state = 6;
    //     data->initial_speed = 2;
    // }else if( colision == 103 && data->state != 4 ){
    //     data->initial_state = 4;
    //     data->state = 6;
    //     data->initial_speed = 2;
    // }else if( colision == 104 && data->state != 3 ){
    //     data->initial_state = 3;
    //     data->state = 6;
    //     data->initial_speed = 2;
    // }else if(colision == 97 && data->state != 2 ){
    //     data->initial_state = 2;
    //     data->state = 6;
    //     data->initial_speed = 1;
    // }else if( colision == 98 && data->state != 5){
    //     data->initial_state = 5;
    //     data->state = 6;
    //     data->initial_speed = 1;
    // }else if( colision == 99 && data->state != 4){
    //     data->initial_state = 4;
    //     data->state = 6;
    //     data->initial_speed = 1;
    // }else if( colision == 100 && data->state != 3){
    //     data->initial_state = 3;
    //     data->state = 6;
    //     data->initial_speed = 1;
    // }if(colision == 93 && data->state != 2 ){
    //     data->initial_state = 2;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }else if( colision == 94 && data->state != 5){
    //     data->initial_state = 5;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }else if( colision == 95 && data->state != 4){
    //     data->initial_state = 4;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }else if( colision == 96 && data->state != 3){
    //     data->initial_state = 3;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }

    // if(colision2 == 93 && (data->state == 2 || data->state == 9)){
    //     data->initial_state = 8;
    //     data->state = 6;
    //     data->initial_speed = 3;
    // }else if(colision2 == 101 && (data->state == 2 || data->state == 8)){
    //     data->initial_state = 9;
    //     data->state = 6;
    //     data->initial_speed = 2;
    //     data->speed = 1;
    // }
        
    
   

}

void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;

    data->initial_state = data->state = 0;
    if(current_level == 10 || current_level == 11){
        data->initial_speed = 1;
    }else{
        data->initial_speed = 2;
    }
    data->speed = data->initial_speed;
    THIS->y += 8;
    THIS->x -= 4;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 8u) >> 3);
    if (colision == 106){
        THIS->x += 8;
        // THIS->y += 8;
        data->state = 2;
    }

    switch(current_level){
        case 26:
            if(THIS->x > 496 && THIS->x < 616){
                data->state = 1;
                THIS->y += 4;
                THIS->x += 12;
            }else  if(THIS->x > 872 && THIS->x < 928){
                data->state = 8;
                THIS->y += 32;
                THIS->x;
            }else if(THIS->x > 1320 ){
                THIS->y -= 12;
                THIS->x -= 12;
            }
        break;
        case 27:
            if(THIS->x < 128){
                THIS->x += 40;
                THIS->y -= 32;
                data->state = 2;
            }
            if(THIS->x > 688 && THIS->x < 912){
                data->state = 1;
                THIS->x += 8;
                THIS->y -= 4;
            }
            if(THIS->x > 1016){
                data->state = 12;
                THIS->x -= 8;
                THIS->y += 44;
        
            }
        break;
        case 28:
            if(THIS->x > 216 && THIS->x < 344){
                THIS->y-=20;
            }else if(THIS->x > 448 && THIS->x < 896){
                THIS->x-=8;
                THIS->y-=10;
                data->state = 17;
            }else if(THIS->x > 897 ){
                data->state = 17;
            }
        break;
        case 29:
            THIS->y-=4;
            data->state = 1;
        break;
    }
  

}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    if(start_screen == 0){

        if(data->start == 0){
            data->start = 1;
            THIS->y = data->initial_y;
            THIS->anim_speed = data->initial_frame_speed;
        }

        if(data->state != 0){
            CheckCollisionOrb(data);
        }
        switch(data->state){
            case 3:
            THIS->y += 3;
            break;
            case 4:
            THIS->x += 2;
            break;
            case 6:
            THIS->y += 3;
            break;
            case 7:
            THIS->y -= 2;
            break;
            case 9:
            THIS->x++;
            break;
            case 11:
            THIS->y-=2;
            break;
            case 13:
            THIS->y-=3;
            break;
            case 15:
            THIS->x+=3;
            break;
            case 16:
            THIS->y+=4;
            break;
            case 18:
            THIS->y--;
            break; 
            case 19:
            THIS->x += 4;
            break;
            case 20:
            THIS->y += 2;
            break;
            case 21:
            THIS->x+=5;
            break;
            case 22:
            THIS->y+=5;
            break;
        

            
        }


    if(current_level == 26){
        if(current_level == 26 && THIS->x > 224 && THIS->x < 344){
            if(data->state == 3 && THIS->y == 117){
                data->state = 4;
            }else if(data->state == 4 && THIS->x == 276){
                data->state = 5;
            }else if(data->state == 6 && THIS->y == 141){
                data->state = 4;
            }else if(data->state == 4 && THIS->x == 324){
                data->state = 10;
            }
        }

        if(current_level == 26 && THIS->x > 496 && THIS->x < 624){
            if(data->state == 4 && THIS->x == 540){
                data->state = 7;
            }else if(data->state == 7 && THIS->y == 124){
                data->state = 4;
            }else if(data->state == 4 && THIS->x == 596){
                data->state = 10;
            }
        }

        if(THIS->x > 872 && THIS->x < 928 && current_level == 26){
            if(data->state == 7 && THIS->y == 92){
                data->state = 10;
            }
        }
        if(THIS->x > 1320 && current_level == 26){
            if(data->state == 9 && THIS->x == 1454){
                data->state = 10;
            }
        }
    }else if(current_level == 27){
        if(THIS->x > 696 && THIS->x < 888 ){
            if(data->state == 4 && THIS->x == 780){
                data->state = 0;
            }else if(data->state == 9 && THIS->x == 852){
                data->state = 12;
            }else if(data->state == 11 && THIS->y == 128){
                data->state = 10;
            }
        }else if(THIS->x > 1016){
            if(data->state == 11 && THIS->y == 136){
                data->state = 14;
            }else if(data->state == 13 && THIS->y < 79){
                data->state = 15;
            }else if(data->state == 15 && THIS->x > 1186){
                data->state = 6;
            }else if(data->state == 6 && THIS->y > 152){
                data->state = 10;
            }
        }
        
    }else if(current_level == 28){
        if(THIS->x > 216 && THIS->x < 336){
            if(data->state == 9 && THIS->x == 316){
                data->state = 2;
            }
        }else if(THIS->x > 448 && THIS->x < 896){
            if(data->state == 16 && THIS->y > 163){
                data->state = 9;
            }else if(data->state == 9 && THIS->x > 859){
                data->state = 18;
            }
        }else{
            if(data->state == 16 && THIS->y > 114 && THIS->x < 1250){
                data->state = 19;
            }else if(data->state == 19 && THIS->x > 1250 && THIS->y < 130){
                data->state = 17;
            }else if (data->state == 16 && THIS->y > 130 && THIS->x < 1298){
                data->state = 19;
            }else if(data->state == 19 && THIS->x > 1298 && THIS->y < 146){
                data->state = 17;
            }else if (data->state == 16 && THIS->y > 146){
                data->state = 19;
            }else if (data->state == 19 && THIS->x > 1346){
                data->state = 10;
            }
        }
    }else if (current_level == 29 ){
        if( data->state == 4 && THIS->x > 434 && THIS->y > 90 && THIS->x < 480){
            data->state = 7;
        }else if (data->state == 7 && THIS->y < 78 && THIS->x < 560){
            data->state = 21;
        }else if (data->state == 19 && THIS->x > 602 && THIS->y < 78){
            data->state = 16;
        }
    }
        // switch (data->state)
        // {
        // case 1:
        //     data->state = 2;
        //     data->initial_speed = 3;
        //     break;
        // case 2:
        //     THIS->y += 3;
        //     break;
        // case 3:
          
        //         THIS->x++;
                
            
                
        //     break;
        // case 4:
          
        //     if(--data->speed == 0 && data->initial_speed != 3){
        //         THIS->y--;
        //         data->speed = data->initial_speed;
        //     }
           
                
        //     break;
        //  case 5:
          
        //     THIS->x--;    
        //     break;

        // default:
        //     break;
        // }
    
    }else{
        if(THIS->y != 0  && data->start == 1){
            data->start = 0;
            data->initial_y = THIS->y;
            THIS->y = 0;
            data->initial_frame_speed = THIS->anim_speed;
            THIS->anim_speed =0;
        } 
    }
}

void DESTROY()
{
}