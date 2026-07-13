/*
 * Entry: 004504c0
 * Name: GoodScrapPosition
 * Namespace: Global
 * Signature: bool GoodScrapPosition(float param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl GoodScrapPosition(float param_1,float param_2)

{
  uchar uVar1;
  byte bVar2;
  
  uVar1 = CellRegion(param_1,param_2);
  if (uVar1 == '\0') {
    return false;
  }
  bVar2 = CellType(param_1,param_2);
  return sGoodScrapMaterial[sMaterial[bVar2 & 0xf]];
}
