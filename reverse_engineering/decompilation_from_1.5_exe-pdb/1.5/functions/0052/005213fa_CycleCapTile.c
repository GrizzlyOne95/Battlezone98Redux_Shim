/*
 * Entry: 005213fa
 * Name: CycleCapTile
 * Namespace: Global
 * Signature: void CycleCapTile(ushort * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CycleCapTile(ushort *param_1,int param_2)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  puVar2 = param_1;
  uVar1 = *param_1;
  uVar3 = (int)(uint)uVar1 >> 0xc;
  uVar4 = (int)(uint)uVar1 >> 8 & 0xf;
  param_1 = (ushort *)0x0;
  do {
    iVar5 = 0;
    do {
      uVar4 = uVar4 + param_2;
      if (7 < (int)uVar4) {
        uVar4 = 0;
      }
      if ((int)uVar4 < 0) {
        uVar4 = 7;
      }
      if ((TileIndex[uVar3][uVar4][0][0] != '\0') && (uVar3 != uVar4)) {
        *puVar2 = (ushort)((uVar4 & 0xf | uVar3 << 4) << 8) | uVar1 & 0x7c;
        return;
      }
      iVar5 = iVar5 + 1;
    } while (iVar5 < 8);
    uVar3 = uVar3 + param_2;
    if (7 < (int)uVar3) {
      uVar3 = 0;
    }
    if ((int)uVar3 < 0) {
      uVar3 = 7;
    }
    param_1 = (ushort *)((int)param_1 + 1);
    if (7 < (int)param_1) {
      return;
    }
  } while( true );
}
