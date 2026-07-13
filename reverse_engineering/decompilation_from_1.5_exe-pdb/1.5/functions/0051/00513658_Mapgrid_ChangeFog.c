/*
 * Entry: 00513658
 * Name: Mapgrid_ChangeFog
 * Namespace: Global
 * Signature: void Mapgrid_ChangeFog(int param_1, int param_2, int param_3, int param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Mapgrid_ChangeFog(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  byte *pbVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = (int)((param_1 - maxoverlayxsize) + (param_1 - maxoverlayxsize >> 0x1f & 0xfU)) >> 4;
  iVar2 = (int)(param_4 + 0xf + (param_4 + 0xf >> 0x1f & 0xfU)) >> 4;
  iVar3 = (int)((param_2 - maxoverlayysize) + (param_2 - maxoverlayysize >> 0x1f & 0xfU)) >> 4;
  iVar7 = (int)(param_3 + 0xf + (param_3 + 0xf >> 0x1f & 0xfU)) >> 4;
  if (iVar6 < 1) {
    iVar6 = 0;
  }
  if (iVar3 < 1) {
    iVar3 = 0;
  }
  if (mapgridxsize <= iVar7) {
    iVar7 = mapgridxsize;
  }
  if (mapgridysize <= iVar2) {
    iVar2 = mapgridysize;
  }
  for (; iVar3 < iVar2; iVar3 = iVar3 + 1) {
    if (iVar6 < iVar7) {
      iVar4 = iVar6 * 0x10c;
      iVar5 = iVar7 - iVar6;
      do {
        pbVar1 = (byte *)((int)mapgrid[iVar3]->firstbuilding + iVar4 + 0x48);
        *pbVar1 = *pbVar1 | (byte)param_5;
        iVar4 = iVar4 + 0x10c;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return;
}
