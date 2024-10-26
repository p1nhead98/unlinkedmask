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


void START()
{
    CUSTOM_DATA_ORB* data = (CUSTOM_DATA_ORB*)THIS->custom_data;

    data->initial_frame_speed = 0;
    data->initial_y = THIS->y;
    data->start = 1;

    data->state = 0;
    data->initial_speed = 2;
    data->speed = data->initial_speed;
    switch(current_level){
        case 0:
            if(THIS->x < 216){
                data->state = 10;
                THIS->y -= 8;
                THIS->x += 4;
            }else if(THIS->x > 216 && THIS->x < 320){
                data->state = 10;
                THIS->y += 8;
                THIS->x += 4;
            }else if(THIS->x > 480 && THIS->x < 616){
                data->state = 21;
                THIS->y += 12;
                //THIS->x += 4;
            }else if(THIS->x > 864 && THIS->x < 928){
                data->state = 22;
                THIS->y += 40;
                THIS->x += 4;
            }else if(THIS->x > 1224){
                data->state = 23;
                THIS->y -= 4;
                THIS->x += 56;
                THIS->lim_x = 200;
                THIS->lim_y = 160;
            }
           
        break;

    }
    

    // if(current_level == 3){
    //     if(THIS->x < 200){
    //         THIS->y -= 4;
    //     }else if(THIS->x > 520 && THIS->x < 592){
    //         THIS->y -= 4;
    //         THIS->x += 16;
    //     }else if(THIS->x > 593 && THIS->x < 640){
    //         data->state = 3;
    //         THIS->x += 4;
    //     }else if(THIS->x > 832 && THIS->x < 880){
    //         data->state = 3;
    //         THIS->x -= 12;
    //     }else if(THIS->x > 881){
    //         data->state = 3;
    //         THIS->x += 4;
    //     }
    // }else{
    //     data->state = 10;
    //     THIS->x = 76;
    //     THIS->y = 148;
    //     THIS->lim_x = 100;
    //     THIS->lim_y = 160;

    // }
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

     switch(data->state){
        case 0:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x++;
            }
        break;
        case 1:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x--;
            }
        break;
        case 2:
           if(--data->speed == 0){
                data->speed = 2;
                THIS->y++;
            }
        break;
        case 3:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->y--;
            }
        break;
        

        case 4:
            THIS->y++;
        break;

        case 5:
            THIS->y--;
        break;
        
        case 6:
            THIS->x++;
        break;
        
        case 7:
            THIS->x--;
        break;


        case 8:
            THIS->y -= 3;
        break;
        case 9:
            THIS->y += 3;
        break;
        case 11:
            THIS->x += 3;
        break;
        case 12:
            THIS->x -= 3;
        break;


        case 14:
            THIS->x -= 2;
        break;
        case 15:
            THIS->x += 2;
        break;
        case 16:
            THIS->y -= 2;
        break;
        case 17:
            THIS->y += 2;
            
            break;
        
        case 26:
            THIS->y -= 5;
            break;
        case 27:
            THIS->y += 5;
            break;
        case 28:
            THIS->x += 5;
            break;
        case 29:
            THIS->x -= 5;
            break;
        case 32:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x+=3;
            }
        break;
     }

    if(current_level == 0){
        if(THIS->x > 216 && THIS->x < 340){
            if(data->state == 9 && THIS->y > 129 && THIS->x < 270){
                data->state = 15;
            }else if(data->state == 15 && THIS->x > 274 && THIS->y < 150){
                data->state = 10;
            }else if(data->state == 9 && THIS-> y > 153){
                data->state = 15;
            }else if(data->state == 15 && THIS->x > 322){
                data->state = 99;
            }
        }else if(THIS->x > 480 && THIS->x < 616){
            if(data->state == 15 && THIS->x > 538 && THIS->y > 126){
                data->state = 16;
            }else if(data->state == 16 && THIS->x < 545 && THIS->y < 126){
                data->state = 15;
            }else if(data->state == 15 && THIS->x > 593){
                data->state = 99;
            }
            //THIS->x += 4;
        }else if(THIS->x > 864 && THIS->x < 928){
            if(data->state == 8 && THIS->y < 96){
                data->state = 99;
            }
        }else if(THIS->x > 1288){
            if(data->state == 6 && THIS->x > 1448){
                data->state = 99;
            }
        }
    }
    //  if(current_level == 3){
    //     if(THIS->x < 200){
    //         if(THIS->x < 68 && data->state == 1){
    //             data->state = 0;
    //         }else if (THIS->x > 140 && data->state == 0){
    //             data->state = 1;
    //         }
    //     }else if(THIS->x > 520 && THIS->x < 592){
    //         if(THIS->x < 532 && data->state == 1){
    //             data->state = 0;
    //         }else if (THIS->x > 580 && data->state == 0){
    //             data->state = 1;
    //         }
    //     }else if(THIS->x > 593 && THIS->x < 640){
    //         if(THIS->y < 100 && data->state == 3){
    //             data->state = 2;
    //         }else if (THIS->y > 156  && data->state == 2){
    //             data->state = 3;
    //         }
    //     }else if(THIS->x > 832){
    //         if(THIS->y < 76 && data->state == 3){
    //             data->state = 2;
    //         }else if (THIS->y > 164  && data->state == 2){
    //             data->state = 3;
    //         }
    //     }
    //  }else{
    //     if(THIS->x > 668 && THIS->y < 163 && data->state == 6){
    //         data->state = 4;
    //     }else if(THIS->y > 164 && data->state == 4){
    //         data->state = 6;
    //     }else if(THIS->x > 755 && THIS->y > 164 && data->state == 6){
    //         data->state = 5;
    //     }
    //  }






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