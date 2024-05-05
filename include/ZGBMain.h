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
_SPRITE_DMG(SpritePlayerNoCape, playerNoCape)\
_SPRITE_DMG(SpriteIntroBigShine, introBigShine)\
_SPRITE_DMG(SpriteIntroMiniShine, introMiniShine)\
_SPRITE_DMG(SpriteIntroFx, introFx)\
_SPRITE_DMG(SpriteWindEnemy, windEnemy)\
_SPRITE_DMG(SpriteSpinOrbEvent, plataforma1)\
_SPRITE_DMG(SpriteJumpBoxEvent, plataforma2)\
_SPRITE_DMG(SpritePlayerCutscenes, playerNCinematic)\
_SPRITE_DMG(SpriteViewerH, viewerHair)\
_SPRITE_DMG(SpriteCapeCuts, capeCuts)\
_SPRITE_DMG(SpriteExplosionCuts, explosionCuts)\
_SPRITE_DMG(SpritePlayerStars, playerStars)\
_SPRITE_DMG(SpritePlayerCutsTemple, playerTempleCuts)\
_SPRITE_DMG(SpriteSpinOrbStoppable4, plataforma1)\
_SPRITE_DMG(SpriteSpinOrbStoppable5, plataforma1)\
_SPRITE_DMG(SpriteCrusherUp, crusherDown)\
_SPRITE_DMG(SpriteSpinOrbRooftop, plataforma1)\
_SPRITE_DMG(SpriteCrusherLeft, crusherLeft)\
_SPRITE_DMG(SpriteSplitBox, plataforma2)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif