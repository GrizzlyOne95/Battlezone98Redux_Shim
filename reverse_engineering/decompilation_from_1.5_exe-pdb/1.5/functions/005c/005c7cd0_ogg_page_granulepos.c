/*
 * Entry: 005c7cd0
 * Name: ogg_page_granulepos
 * Namespace: Global
 * Signature: undefined ogg_page_granulepos()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* ogg_page_granulepos */

undefined8 __cdecl ogg_page_granulepos(int *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  iVar1 = *param_1;
  uVar2 = *(int *)(iVar1 + 10) << 8;
  uVar3 = (uVar2 | *(byte *)(iVar1 + 9)) << 8;
  uVar4 = (uVar3 | *(byte *)(iVar1 + 8)) << 8;
  return CONCAT44((((uint)*(byte *)(iVar1 + 0xd) << 8 | uVar2 >> 0x18) << 8 | uVar3 >> 0x18) << 8 |
                  uVar4 >> 0x18,(uVar4 | *(byte *)(iVar1 + 7)) << 8 | (uint)*(byte *)(iVar1 + 6));
}
