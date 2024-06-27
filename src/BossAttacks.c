#include "BossAttacks.h"
const UINT8 FLAME_TILE_1  = 108;
const UINT8 FLAME_TILE_2  = 109;
const UINT8 FLAME_TILE_3  = 110;
const UINT8 FLAME_TILE_4  = 111;

const UINT8 LEFT_PILAR_1  = 68;
const UINT8 LEFT_PILAR_2  = 69;
const UINT8 LEFT_PILAR_3  = 3;
const UINT8 LEFT_PILAR_4  = 72;
const UINT8 LEFT_PILAR_5  = 70;
const UINT8 LEFT_PILAR_6  = 71;
const UINT8 LEFT_PILAR_7  = 73;
void Attacks_Animations(UINT8 animIndex) BANKED {
    switch (animIndex)
    {
    case 0:
        
		set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_4);
        break;
    case 1:
   
		set_bkg_tiles(5, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(7, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(9, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(11, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(13, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 17, 1, 1, &FLAME_TILE_2);
        break;
    case 2:
     
		set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_2);
        break;

    case 3:
        set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_4);
        break;
    case 4:
   
		set_bkg_tiles(15, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(17, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(19, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(21, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(23, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 17, 1, 1, &FLAME_TILE_2);
        break;
    case 5:
   
		set_bkg_tiles(5, 17, 1, 1, &LEFT_PILAR_1);
		set_bkg_tiles(6, 17, 1, 1, &LEFT_PILAR_2);
        set_bkg_tiles(7, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(9, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(11, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(13, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 17, 1, 1, &LEFT_PILAR_3);
        break;
    case 6:
   
		set_bkg_tiles(5, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(6, 18, 1, 1, &LEFT_PILAR_4);
        set_bkg_tiles(7, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(9, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(11, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(13, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 18, 1, 1, &LEFT_PILAR_3);
        break;
    case 7:
     
		set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_2);
        break;

    case 8:
   
		set_bkg_tiles(15, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(17, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(19, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(21, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(23, 17, 1, 1, &LEFT_PILAR_5);
		set_bkg_tiles(24, 17, 1, 1, &LEFT_PILAR_6);
        break;
    case 9:
   
		set_bkg_tiles(15, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(17, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(19, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(21, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(23, 18, 1, 1, &LEFT_PILAR_7);
		set_bkg_tiles(24, 18, 1, 1, &LEFT_PILAR_3);
        break;


    case 10:
        set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_4);


        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_4);
        break;
    case 11:
        set_bkg_tiles(5, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(7, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(13, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(15, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 17, 1, 1, &FLAME_TILE_2);


        set_bkg_tiles(21, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(23, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 17, 1, 1, &FLAME_TILE_2);
        break;

    case 12:
        set_bkg_tiles(5, 17, 1, 1, &LEFT_PILAR_1);
		set_bkg_tiles(6, 17, 1, 1, &LEFT_PILAR_2);
        set_bkg_tiles(7, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(13, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(15, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 17, 1, 1, &LEFT_PILAR_3);


        set_bkg_tiles(21, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(23, 17, 1, 1, &LEFT_PILAR_5);
		set_bkg_tiles(24, 17, 1, 1, &LEFT_PILAR_6);
        break;    
    case 13:
        set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_2);


        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_2);
        break; 
    case 14:
        set_bkg_tiles(5, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(6, 18, 1, 1, &LEFT_PILAR_4);
        set_bkg_tiles(7, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(13, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(15, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 18, 1, 1, &LEFT_PILAR_3);


        set_bkg_tiles(21, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(23, 18, 1, 1, &LEFT_PILAR_7);
		set_bkg_tiles(24, 18, 1, 1, &LEFT_PILAR_3);
        break; 




     case 15:
        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_4);
        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_4);
        break;     
    case 16:
        set_bkg_tiles(9, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(11, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(17, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 17, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(19, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 17, 1, 1, &FLAME_TILE_2);
        break; 
    case 17:
        set_bkg_tiles(9, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(11, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(17, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 17, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(19, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 17, 1, 1, &LEFT_PILAR_3);
        break; 
     case 18:
        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_2);
        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_2);
        break;
    case 19:
        set_bkg_tiles(9, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(11, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(17, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 18, 1, 1, &LEFT_PILAR_3);
        set_bkg_tiles(19, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 18, 1, 1, &LEFT_PILAR_3);
        break; 




    case 20:
        set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_4);
      
        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_4);

        break;
    case 21:
        set_bkg_tiles(5, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(9, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 17, 1, 1, &FLAME_TILE_2);
      
        set_bkg_tiles(13, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(17, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(21, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 17, 1, 1, &FLAME_TILE_2);
        break;
    case 22:
        set_bkg_tiles(5, 17, 1, 1, &LEFT_PILAR_1);
		set_bkg_tiles(6, 17, 1, 1, &LEFT_PILAR_2);

        set_bkg_tiles(9, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 17, 1, 1, &LEFT_PILAR_3);
      
        set_bkg_tiles(13, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(17, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(21, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 17, 1, 1, &LEFT_PILAR_3);
        break;
    case 23:
        set_bkg_tiles(5, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(6, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(9, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(10, 18, 1, 1, &FLAME_TILE_2);
      
        set_bkg_tiles(13, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(14, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(17, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(18, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(21, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(22, 18, 1, 1, &FLAME_TILE_2);
        break;
    case 24:
        set_bkg_tiles(5, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(6, 18, 1, 1, &LEFT_PILAR_4);

        set_bkg_tiles(9, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(10, 18, 1, 1, &LEFT_PILAR_3);
      
        set_bkg_tiles(13, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(14, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(17, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(18, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(21, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(22, 18, 1, 1, &LEFT_PILAR_3);
        break;

    case 25:
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_4);
      
        set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_4);

        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_3);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_4);
        break;
    case 26:
        set_bkg_tiles(7, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(11, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 17, 1, 1, &FLAME_TILE_2);
      
        set_bkg_tiles(15, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(19, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 17, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(23, 17, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 17, 1, 1, &FLAME_TILE_2);
        break;

    case 27:
        set_bkg_tiles(7, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(11, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 17, 1, 1, &LEFT_PILAR_3);
      
        set_bkg_tiles(15, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(19, 17, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 17, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(23, 17, 1, 1, &LEFT_PILAR_5);
		set_bkg_tiles(24, 17, 1, 1, &LEFT_PILAR_6);
        break;

    case 28:
        set_bkg_tiles(7, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(8, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(11, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(12, 18, 1, 1, &FLAME_TILE_2);
    
        set_bkg_tiles(15, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(16, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(19, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(20, 18, 1, 1, &FLAME_TILE_2);

        set_bkg_tiles(23, 18, 1, 1, &FLAME_TILE_1);
		set_bkg_tiles(24, 18, 1, 1, &FLAME_TILE_2);
        break;
    case 29:
        set_bkg_tiles(7, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(8, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(11, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(12, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(15, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(16, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(19, 18, 1, 1, &LEFT_PILAR_3);
		set_bkg_tiles(20, 18, 1, 1, &LEFT_PILAR_3);

        set_bkg_tiles(23, 18, 1, 1, &LEFT_PILAR_7);
		set_bkg_tiles(24, 18, 1, 1, &LEFT_PILAR_3);
        break;
    
    default:
        break;
    }
}