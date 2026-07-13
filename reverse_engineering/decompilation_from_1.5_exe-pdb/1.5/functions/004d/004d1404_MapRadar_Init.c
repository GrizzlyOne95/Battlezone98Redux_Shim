/*
 * Entry: 004d1404
 * Name: MapRadar::Init
 * Namespace: MapRadar
 * Signature: void Init(MapRadar * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall MapRadar::Init(MapRadar *this)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&MAP_NUMBER[0].name + uVar2));
    *(int *)((int)&MAP_NUMBER[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 8;
  } while (uVar2 < 0x50);
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&UNIT_TYPE[0].name + uVar2));
    *(int *)((int)&UNIT_TYPE[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 0x10;
  } while (uVar2 < 0x80);
  CURSOR.index = GetSpriteIndex(CURSOR.name);
  return;
}
