/*
 * Entry: 004d06f4
 * Name: LensFlare::PreLoad
 * Namespace: LensFlare
 * Signature: void PreLoad(LensFlare * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall LensFlare::PreLoad(LensFlare *this)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  do {
    iVar1 = GetSpriteIndex(*(char **)((int)&RING_MAPS[0].name + uVar2));
    *(int *)((int)&RING_MAPS[0].index + uVar2) = iVar1;
    uVar2 = uVar2 + 0xc;
  } while (uVar2 < 0x48);
  return;
}
