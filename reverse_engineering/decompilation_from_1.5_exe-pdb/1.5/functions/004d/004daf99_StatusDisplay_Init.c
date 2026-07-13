/*
 * Entry: 004daf99
 * Name: StatusDisplay::Init
 * Namespace: StatusDisplay
 * Signature: void Init(StatusDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall StatusDisplay::Init(StatusDisplay *this)

{
  int iVar1;
  uint uVar2;
  
  this->hullRatio = 0.0;
  this->ammoRatio = 0.0;
  iVar1 = GetSpriteIndex("status_left");
  this->statusLeftIndex = iVar1;
  iVar1 = GetSpriteIndex("status_right");
  this->statusRightIndex = iVar1;
  iVar1 = GetSpriteIndex("hull");
  this->hullTitleIndex = iVar1;
  iVar1 = GetSpriteIndex("hull_bar");
  this->hullGaugeIndex = iVar1;
  iVar1 = GetSpriteIndex("ammo");
  this->ammoTitleIndex = iVar1;
  iVar1 = GetSpriteIndex("ammo_bar");
  this->ammoGaugeIndex = iVar1;
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&HARDPOINT_INFO[0].name + uVar2));
    *(int *)((int)&HARDPOINT_INFO[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0x28);
  this->hullDepleted = false;
  this->ammoDepleted = false;
  return;
}
