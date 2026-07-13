/*
 * Entry: 004f1fff
 * Name: Fill_Luminance_Extras
 * Namespace: Global
 * Signature: void Fill_Luminance_Extras(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Fill_Luminance_Extras(void)

{
  uchar uVar1;
  uchar *puVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  do {
    puVar2 = &DAT_00d20480 + iVar3;
    uVar1 = Luminance_Table[0x1f][iVar3];
    iVar4 = 0x70;
    do {
      *puVar2 = uVar1;
      puVar2 = puVar2 + 0x100;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    uVar1 = Luminance_Table[0][iVar3];
    puVar2 = &DAT_00d2e380 + iVar3;
    iVar4 = 0x70;
    do {
      *puVar2 = uVar1;
      puVar2 = puVar2 + -0x100;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x100);
  return;
}
