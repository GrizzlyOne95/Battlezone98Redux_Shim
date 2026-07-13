/*
 * Entry: 005214fe
 * Name: CycleTileVariant
 * Namespace: Global
 * Signature: void CycleTileVariant(ushort * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CycleTileVariant(ushort *param_1,int param_2)

{
  ushort uVar1;
  uchar (*pauVar2) [2];
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int local_8;
  
  uVar1 = *param_1;
  uVar7 = (uint)uVar1;
  uVar4 = (int)uVar7 >> 8 & 0xf;
  uVar3 = uVar7 & 3;
  uVar6 = (int)uVar7 >> 7 & 1;
  local_8 = 0;
  pauVar2 = TileIndex[(int)uVar7 >> 0xc][uVar4] + uVar3;
  while( true ) {
    uVar3 = uVar3 + param_2;
    if (3 < (int)uVar3) {
      uVar3 = 0;
    }
    if ((int)uVar3 < 0) {
      uVar3 = 3;
    }
    uVar5 = (uint)TileIndex[(int)uVar7 >> 0xc][uVar4][uVar3][uVar6];
    if ((uVar5 != 0) && (TileTexturePtr[uVar5] != TileTexturePtr[(*pauVar2)[uVar6]])) break;
    local_8 = local_8 + 1;
    if (3 < local_8) {
      return;
    }
  }
  *param_1 = (uVar1 ^ (ushort)uVar3) & 3 ^ uVar1;
  return;
}
