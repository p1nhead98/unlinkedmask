#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateGame)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, playerCape)\
_SPRITE_DMG(SpriteSpinOrb, plataforma1)\
_SPRITE_DMG(SpriteJumpBox, plataforma2)\
_SPRITE_DMG(SpriteCrusherDown, crusherDown)\
_SPRITE_DMG(SpriteDoorTile1, doorTile1)\
_SPRITE_DMG(SpriteDoorTile2, doorTile2)\
_SPRITE_DMG(SpriteDoorTile3, doorTile3)\
_SPRITE_DMG(SpriteDoorTile4, doorTile4)\
_SPRITE_DMG(SpriteDoorButton, doorButton)\
_SPRITE_DMG(SpriteTimeDoorClosed, timeDoorClosed)\
_SPRITE_DMG(SpriteSpinOrbActivable, plataforma1)\
_SPRITE_DMG(SpritePlayerDeath, playerDeath)\
_SPRITE_DMG(SpritePlayerVfx, playerVFX)\
_SPRITE_DMG(SpriteOnOffBtn, onOffButton)\
_SPRITE_DMG(SpriteSpinOrbFall, plataforma1)\
_SPRITE_DMG(SpriteSpinOrbStoppable, plataforma1)\
_SPRITE_DMG(SpriteSpinOrbStoppable2, plataforma1)\
_SPRITE_DMG(SpriteSpinOrbStoppable3, plataforma1)\
_SPRITE_DMG(SpriteBossElec, elecBoss)\
_SPRITE_DMG(SpriteElectBossFx, elecBossFx)\
_SPRITE_DMG(SpriteCrystalBoss, crystalBoss)\
_SPRITE_DMG(SpriteCrystalAttack, crystalAttack)\
_SPRITE_DMG(SpritePlayerNoCape, playerNoCape)\
_SPRITE_DMG(SpriteIntroBigShine, introBigShine)\
_SPRITE_DMG(SpriteIntroMiniShine, introMiniShine)\
_SPRITE_DMG(SpriteIntroFx, introFx)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif