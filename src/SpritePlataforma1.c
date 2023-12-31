#include "Banks/SetAutoBank.h"
#include "Keys.h"
#include "Misc.h"
#include "SpriteManager.h"
#include <gb/gb.h>
#include "Sound.h"
#include "Palette.h"
#include "Math.h"
#include "ZGBMain.h"

void CheckCollisionTilePlt(CUSTOM_DATA* data)
{
    UINT8 colision = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 4u) >> 3);
    // UINT8 colision2 = GetScrollTile((THIS->x + 3u) >> 3, (THIS->y + 16u) >> 3);
    if(data->state == 1){
        colision = GetScrollTile((THIS->x) >> 3, (THIS->y + 4u) >> 3);
    }else if (data->state == 2){
        colision = GetScrollTile((THIS->x) >> 3, (THIS->y + 10u) >> 3);
    }else if(data->state == 3){
        colision = GetScrollTile((THIS->x + 8u) >> 3, (THIS->y + 4u) >> 3);
    }


    if( colision == 107 && data->state != 1 ){
        data->state = 1;
    }else if( colision == 106 && data->state != 2 ){
        data->state = 2;
    }else if( colision == 105 && data->state != 3 ){
        data->state = 3;
    }else if( colision == 104 && data->state != 4 ){
        data->state = 4;
    }

   

}

void START()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    data->state = 0;
    THIS->y -= 4;
    THIS->x - 8;
}

void UPDATE()
{
    CUSTOM_DATA* data = (CUSTOM_DATA*)THIS->custom_data;
    UINT8 i;
	Sprite* spr;
    CheckCollisionTilePlt(data);

    switch (data->state)
    {
    case 1:
        THIS->x++;
        break;
    case 2:
        THIS->y--;
        break;
    case 3:
        THIS->x--;
        break;
    case 4:
        THIS->y++;
        break;
    default:
        break;
    }
}

void DESTROY()
{
}