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
        case 1:
            if(THIS->x < 264){
                data->state = 10;
                THIS->x += 36;
                THIS->y -= 24;
            }else if(THIS->x > 656 && THIS->x < 808){
                data->state = 21;
                THIS->y += 4;
            }else if(THIS->x > 1048){
                data->state = 24;
                THIS->x += 4;
                THIS->y += 16;
            }
        break;
        case 2:
            if(THIS->x < 368){
                data->state = 21;
                THIS->y -= 4;

            }else if(THIS->x > 460 && THIS->x < 896){
                data->state = 25;
                THIS->x -= 4;
                THIS->y += 16;
                THIS->lim_x = 200;
                THIS->lim_y = 160;
            }else if(THIS->x > 1160){
                data->state = 10;
                THIS->x -= 4;
                THIS->y += 8;
            }
            break;
        case 3:
            data->state = 21;
            THIS->y -= 4;
            THIS->lim_x = 200;
            THIS->lim_y = 160;
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
                THIS->x += 1 << delta_time;
            }
        break;
        case 1:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x -= 1  << delta_time;
            }
        break;
        case 2:
           if(--data->speed == 0){
                data->speed = 2;
                THIS->y += 1 << delta_time;
            }
        break;
        case 3:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->y -= 1  << delta_time;
            }
        break;
        

        case 4:
            THIS->y += 1 << delta_time;
        break;

        case 5:
            THIS->y -= 1  << delta_time;
        break;
        
        case 6:
            THIS->x += 1 << delta_time;
        break;
        
        case 7:
            THIS->x -= 1 << delta_time;
        break;


        case 8:
            THIS->y -= 3  << delta_time;
        break;
        case 9:
            THIS->y += 3 << delta_time;
        break;
        case 11:
            THIS->x += 3 << delta_time;
        break;
        case 12:
            THIS->x -= 3 << delta_time;
        break;


        case 14:
            THIS->x -= 2 << delta_time;
        break;
        case 15:
            THIS->x += 2 << delta_time;
        break;
        case 16:
            THIS->y -= 2 << delta_time;
        break;
        case 17:
            THIS->y += 2 << delta_time;
            
            break;
        
        case 26:
            THIS->y -= 5 << delta_time;
            break;
        case 27:
            THIS->y += 5 << delta_time;
            break;
        case 28:
            THIS->x += 5 << delta_time;
            break;
        case 29:
            THIS->x -= 5;
            break;
        case 32:
            if(--data->speed == 0){
                data->speed = 2;
                THIS->x+=3  << delta_time;
            }
        break;
        case 40:
            THIS->x += 4 << delta_time;
        break;
        case 41:
            THIS->y += 4 << delta_time;
        break;
        case 42:
            THIS->y -= 4 << delta_time;
        break;
        case 44:
            THIS->y -= 4 << delta_time;
        break;
        case 45:
            THIS->y += 1 << delta_time;
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
    }else if(current_level == 1){
        if(THIS->x > 656 && THIS->x < 808){
            if(data->state == 15 && THIS->x > 788){
                data->state = 99;
            }
            
        }else if(THIS->x > 1048){
            if(data->state == 16 && THIS->y < 142){
                data->state = 6;
                // THIS->y-=1;
            }else if(data->state == 6 && THIS->x > 1171){
                data->state = 9;
            }
        }
    }else if(current_level == 2){
        if(THIS->x < 368){
            if(data->state == 15 && THIS->x > 280){
                data->state = 23;
            }else if(data->state == 6 && THIS->x > 344){
                data->state = 99;
            }
        
        }else if(THIS->x > 460 && THIS->x < 896){
            if(data->state == 17 && THIS->y > 163){
                data->state = 15;
            }else if(data->state == 15 && THIS->x > 859){
                data->state = 30;
            }
            
        }else if(THIS->x > 1160){
            if(data->state == 9 && THIS->y > 114 && THIS->x < 1216){
                data->state = 28;
                THIS->y -= 1;
            }else if(data->state == 28 && THIS->x > 1240 && THIS->y < 129){
                data->state = 10;
                THIS->x += 1;
            }else if(data->state == 9 && THIS->y > 130 && THIS->x < 1272){
                data->state = 28;
                THIS->y += 1;
            }else if(data->state == 28 && THIS->x > 1288 && THIS->y < 144){
                data->state = 10;
                THIS->x += 3;
            }else if(data->state == 9 && THIS->y > 146){
                data->state = 28;
                THIS->y += 1;
            }else if(data->state == 28 && THIS->x > 1336){
                data->state = 99;
            }
        }
    }else if(current_level == 3){
        if(data->state == 15 && THIS->x > 435){
            data->state = 16;
        }else if(data->state == 16 && THIS->y < 78){
            data->state = 40;
            //THIS->y-=2;
        }else if(data->state == 40 && THIS->x > 600 && THIS->y < 136){
            data->state = 41;
        }if(data->state == 41 && THIS->y > 184){
            data->state = 40;
        }else if(data->state == 40 && THIS->x > 768){
            data->state = 42;
        }else if(data->state == 42 && THIS->y < 128){
            data->state = 43;
        }else if(data->state == 44 && THIS->y < 48){
            data->state = 0;
        }else if(data->state == 0 && THIS->x > 1147){
            data->state = 4;
        }else if(data->state == 4 && THIS->y > 100){
            data->state = 25;
        }else if(data->state == 17 && THIS->y > 137){
            THIS->y+=1;
            data->state = 6;
        }else if(data->state == 6 && THIS->x > 1251){
            data->state = 45;
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