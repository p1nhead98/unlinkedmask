#include <gb/gb.h>
#include <string.h>
#include "ZGBMain.h"
#include "SpriteManager.h"
#include <BankManager.h>
#include "Misc.h"
#include "Scroll.h"

IMPORT_MAP(capeCuts2);
IMPORT_TILES(capeCuts2Tiles);
IMPORT_MAP(capeCuts3);
IMPORT_TILES(capeCuts3Tiles);
IMPORT_MAP(capeCuts4);
IMPORT_TILES(capeCuts4Tiles);
IMPORT_MAP(capeCuts5);
IMPORT_TILES(capeCuts5Tiles);
IMPORT_MAP(capeCuts6);
IMPORT_TILES(capeCuts6Tiles);

IMPORT_MAP(capeCuts7);
IMPORT_TILES(capeCuts7Tiles);
IMPORT_MAP(capeCuts8);
IMPORT_TILES(capeCuts8Tiles);
IMPORT_MAP(capeCuts9);
IMPORT_TILES(capeCuts9Tiles);
IMPORT_MAP(capeCuts10);
IMPORT_TILES(capeCuts10Tiles);
IMPORT_MAP(capeCuts11);
IMPORT_TILES(capeCuts11Tiles);
IMPORT_MAP(capeCuts12);
IMPORT_TILES(capeCuts12Tiles);
IMPORT_MAP(capeCuts13);
IMPORT_TILES(capeCuts13Tiles);
IMPORT_MAP(capeCuts14);
IMPORT_TILES(capeCuts14Tiles);
IMPORT_MAP(capeCuts15);
IMPORT_TILES(capeCuts15Tiles);

IMPORT_MAP(capeCuts16);
IMPORT_TILES(capeCuts16Tiles);
IMPORT_MAP(capeCuts17);
IMPORT_TILES(capeCuts17Tiles);
IMPORT_MAP(capeCuts18);
IMPORT_TILES(capeCuts18Tiles);



void SetBkg(struct TilesInfo *tile, UINT8 bank,UINT8 bank2, struct MapInfo *map, UINT8 tiles_amount) __nonbanked{
  LYC_REG = 0;
  CRITICAL{
    PUSH_BANK(bank);
      set_bkg_data(0, tiles_amount, tile->data);
    POP_BANK;
    PUSH_BANK(bank2);
      set_bkg_tiles(0, 0, 20, 18, map->data);
    POP_BANK;
  }

  
}

void CapeCutsAnim(UINT8 current_frame) BANKED{

  switch (current_frame)
  {
  case 0:
    SetBkg(&capeCuts2Tiles, BANK(capeCuts2Tiles), BANK(capeCuts2), &capeCuts2, 198);
    break;
  case 1:
    SetBkg(&capeCuts3Tiles, BANK(capeCuts3Tiles), BANK(capeCuts3), &capeCuts3, 198);
    break;
  case 2:
    SetBkg(&capeCuts4Tiles, BANK(capeCuts4Tiles), BANK(capeCuts4), &capeCuts4, 198);
    break;
  case 3:
    SetBkg(&capeCuts5Tiles, BANK(capeCuts5Tiles), BANK(capeCuts5), &capeCuts5, 198);
    break;
  case 4:
    SetBkg(&capeCuts6Tiles, BANK(capeCuts6Tiles), BANK(capeCuts6), &capeCuts6, 198);
    break;

  case 5:
    SetBkg(&capeCuts7Tiles, BANK(capeCuts7Tiles), BANK(capeCuts7), &capeCuts7, 199);
    break;
  case 6:
    SetBkg(&capeCuts8Tiles, BANK(capeCuts8Tiles), BANK(capeCuts8), &capeCuts8, 199);
    break;
  case 7:
    SetBkg(&capeCuts9Tiles, BANK(capeCuts9Tiles), BANK(capeCuts9), &capeCuts9, 199);
    break;
  case 8:
    SetBkg(&capeCuts10Tiles, BANK(capeCuts10Tiles), BANK(capeCuts10), &capeCuts10, 199);
    break;
  case 9:
    SetBkg(&capeCuts11Tiles, BANK(capeCuts11Tiles), BANK(capeCuts11), &capeCuts11, 199);
    break;
  case 10:
    SetBkg(&capeCuts12Tiles, BANK(capeCuts12Tiles), BANK(capeCuts12), &capeCuts12, 199);
    break;
  case 11:
    SetBkg(&capeCuts13Tiles, BANK(capeCuts13Tiles), BANK(capeCuts13), &capeCuts13, 199);
    break;
  case 12:
    SetBkg(&capeCuts14Tiles, BANK(capeCuts14Tiles), BANK(capeCuts14), &capeCuts14, 199);
    break;
  case 13:
    SetBkg(&capeCuts15Tiles, BANK(capeCuts15Tiles), BANK(capeCuts15), &capeCuts15, 199);
    break;

  case 14:
    SetBkg(&capeCuts16Tiles, BANK(capeCuts16Tiles), BANK(capeCuts16), &capeCuts16, 178);
    break;

  case 15:
    SetBkg(&capeCuts17Tiles, BANK(capeCuts17Tiles), BANK(capeCuts17), &capeCuts17, 178);
    break;

  case 16:
    SetBkg(&capeCuts18Tiles, BANK(capeCuts18Tiles), BANK(capeCuts18), &capeCuts18, 178);
    break;



  default:
    break;
  }
  
}