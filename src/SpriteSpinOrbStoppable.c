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

void CheckCollisionTilePlt3(CUSTOM_DATA_ORB* data)
{
    
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    UINT8 colision2 = GetScrollTile(( THIS->x + 4u ) >> 3, (THIS->y) >> 3);
    if(data->state == 2){
        colision = GetScrollTile((THIS->x + 12u) >> 3, (THIS->y + 4u) >> 3);
        
    }else if (data->state == 3){
        colision = data->initial_speed == 3 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 2u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 3u) >> 3);
    }else if(data->state == 4){
        colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    }else if(data->state == 5){
        colision = data->initial_speed == 3 ? GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 13u) >> 3) : GetScrollTile((THIS->x + 9u) >> 3, (THIS->y + 12u) >> 3);
    }

    if(colision == 92 ){
        data->state = 7;
    }else if( colision == 101 && data->state != 2 ){
        data->initial_state = 2;
        data->state = 6;
        data->initial_speed = 0;
        data->speed = 1;
    }else if( colision == 102 && data->state != 5 ){
        data->initial_state = 5;
        data->state = 6;
        data->initial_speed = 0;
        data->speed = 1;
    }else if( colision == 103 && data->state != 4 ){
        data->initial_state = 4;
        data->state = 6;
        data->initial_speed = 0;
        data->speed = 1;
    }else if( colision == 104 && data->state != 3 ){
        data->initial_state = 3;
        data->state = 6;
        data->initial_speed = 0;
        data->speed = 1;
    }else if(colision == 97 && data->state != 2 ){
        data->initial_state = 2;
        data->state = 6;
        data->initial_speed = 1;
    }else if( colision == 98 && data->state != 5){
        data->initial_state = 5;
        data->state = 6;
        data->initial_speed = 1;
    }else if( colision == 99 && data->state != 4){
        data->initial_state = 4;
        data->state = 6;
        data->initial_speed = 1;
    }else if( colision == 100 && data->state != 3){
        data->initial_state = 3;
        data->state = 6;
        data->initial_speed = 1;
    }if(colision == 93 && data->state != 2 ){
        data->initial_state = 2;
        data->state = 6;
        data->initial_speed = 3;
    }else if( colision == 94 && data->state != 5){
        data->initial_state = 5;
        data->state = 6;
        data->initial_speed = 3;
    }else if( colision == 95 && data->state != 4){
        data->initial_state = 4;
        data->state = 6;
        data->initial_speed = 3;
    }else if( colision == 96 && data->state != 3){
        data->initial_state = 3;
        data->state = 6;
        data->initial_speed = 3;
    }else if(data->state == 2 && colision2 == 93 ){
        data->initial_state = 8;
        data->state = 6;
        data->initial_speed = 3;
    }else if(data->state == 8 && colision2 == 101 ){
        data->initial_state = 2;
        data->state = 6;
        data->initial_speed = 0;
        data->speed = 1;
    }
        
    
   

}

void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    data->initial_state = data->state = 0;
    if(current_level == 10 || current_level == 11){
        data->initial_speed = 1;
    }else{
        data->initial_speed = 0;
    }
    data->speed = data->initial_speed;
    THIS->y -= 4;
    THIS->x -= 3;
    THIS->lim_x = 80;
    THIS->lim_y = 80;
    UINT8 colision = GetScrollTile((THIS->x + 16u) >> 3, (THIS->y + 6u) >> 3);
    if (colision == 106){
        THIS->x += 7;
    }
}

void UPDATE()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;

    if(data->state != 0){
        CheckCollisionTilePlt3(data);
    }

    switch (data->state)
    {
    case 1:
        UINT8 colision = GetScrollTile((THIS->x) >> 3, (THIS->y + 6u) >> 3);
        UINT8 colision2 = GetScrollTile((THIS->x + 7u) >> 3, (THIS->y + 6u) >> 3);
        if(colision == 97){
            data->state = 2;
            data->initial_speed = 1;
        }else if (colision == 101){
            data->state = 2;
        }else if(colision == 105){
            if(current_level == 14){
                data->state = 4;
                data->initial_speed = 1;
            }
        }else if(colision2 == 106){
           
            data->state = 5;
            data->initial_speed = 3;
            
        }else if(colision2 == 93){
           
            data->state = 2;
            data->initial_speed = 3;
            
        }
        break;
    case 2:
        if(--data->speed == 0 && data->initial_speed == 0){
            THIS->x++;
            data->speed = 2;
        }else{
            THIS->x += data->initial_speed;
        }
            
        break;
    case 3:
     
        if(--data->speed == 0 && data->initial_speed == 0){
            THIS->y--;
            data->speed = 2;
        }else{
            
            THIS->y -= data->initial_speed;
        }
        break;
    case 4:
        if(--data->speed == 0 && data->initial_speed == 0){
            THIS->x--;
            data->speed = 2;
        }else{
            THIS->x -= data->initial_speed;
        }
    
        break;
    case 5:
        if(--data->speed == 0 && data->initial_speed == 0){
            THIS->y++;
            data->speed = 2;
        }else{
            THIS->y += data->initial_speed;
        }
      
        break;
    case 8:
        if(--data->speed == 0 && data->initial_speed == 0){
            THIS->x++;
            data->speed = 2;
        }else{
            THIS->x += data->initial_speed;
        }
    break;
    default:
        break;
    }
}

void DESTROY()
{
}