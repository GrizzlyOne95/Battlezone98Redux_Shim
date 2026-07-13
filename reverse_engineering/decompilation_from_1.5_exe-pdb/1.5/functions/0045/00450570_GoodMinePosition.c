/*
 * Entry: 00450570
 * Name: GoodMinePosition
 * Namespace: Global
 * Signature: bool GoodMinePosition(float param_1, float param_2, uchar param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GoodMinePosition(float param_1,float param_2,uchar param_3)

{
  int iVar1;
  uchar uVar2;
  byte bVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar4;
  
  floor((double)(Terrain.Grid_Scale * param_1));
  _ftol2_sse();
  floor((double)(Terrain.Grid_Scale * param_2));
  _ftol2_sse();
  iVar4 = extraout_EAX_00 + -1;
  if (iVar4 <= extraout_EAX_00 + 1) {
    iVar1 = extraout_EAX + -1;
    do {
      for (; iVar1 <= extraout_EAX + 1; iVar1 = iVar1 + 1) {
        uVar2 = CellRegion(iVar1,iVar4);
        if (((uVar2 == '\0') || (uVar2 != param_3)) ||
           (bVar3 = CellType(iVar1,iVar4), sGoodScrapMaterial[sMaterial[bVar3 & 0xf]] == false)) {
          return false;
        }
      }
      iVar4 = iVar4 + 1;
      iVar1 = extraout_EAX + -1;
    } while (iVar4 <= extraout_EAX_00 + 1);
  }
  return true;
}
