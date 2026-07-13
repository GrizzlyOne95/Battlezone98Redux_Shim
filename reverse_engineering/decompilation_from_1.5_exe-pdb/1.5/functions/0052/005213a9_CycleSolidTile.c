/*
 * Entry: 005213a9
 * Name: CycleSolidTile
 * Namespace: Global
 * Signature: void CycleSolidTile(ushort * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CycleSolidTile(ushort *param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (uint)(*param_1 >> 0xc);
  iVar2 = 0;
  while( true ) {
    uVar1 = uVar1 + param_2;
    if (7 < (int)uVar1) {
      uVar1 = 0;
    }
    if ((int)uVar1 < 0) {
      uVar1 = 7;
    }
    if (*(char *)((int)TileIndex + uVar1 * 0x48) != '\0') break;
    iVar2 = iVar2 + 1;
    if (7 < iVar2) {
      return;
    }
  }
  *param_1 = (ushort)((uVar1 & 0xf | uVar1 << 4) << 8) | *param_1 & 0x7c;
  return;
}
