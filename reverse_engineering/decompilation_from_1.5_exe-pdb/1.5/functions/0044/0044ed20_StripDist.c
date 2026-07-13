/*
 * Entry: 0044ed20
 * Name: StripDist
 * Namespace: Global
 * Signature: float StripDist(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float __cdecl StripDist(Strip *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int in_ECX;
  
  fVar1 = materialCost[*(uint *)(in_ECX + 0x14) & 0xff];
  if ((ushort)((ushort)(*(uint *)(in_ECX + 0x14) >> 0x10) & (ushort)_curPathingEnemies) != 0) {
    fVar1 = fVar1 + 2.0;
  }
  if (fVar1 == 99999.0) {
    return 3.4028235e+38;
  }
  fVar1 = *(float *)(in_ECX + 4) * Terrain.Grid_Size + 1.0;
  fVar2 = *(float *)(in_ECX + 0xc) * Terrain.Grid_Size - 1.0;
  if ((fVar1 <= compareStart.x) && (fVar1 = fVar2, compareStart.x <= fVar2)) {
    fVar1 = compareStart.x;
  }
  fVar3 = *(float *)(in_ECX + 8) * Terrain.Grid_Size + 1.0;
  fVar2 = *(float *)(in_ECX + 0x10) * Terrain.Grid_Size - 1.0;
  if (fVar3 <= compareStart.z) {
    if (fVar2 < compareStart.z) {
      fVar2 = fVar2 - compareStart.z;
      return fVar2 * fVar2 + (fVar1 - compareStart.x) * (fVar1 - compareStart.x);
    }
    return (compareStart.z - compareStart.z) * (compareStart.z - compareStart.z) +
           (fVar1 - compareStart.x) * (fVar1 - compareStart.x);
  }
  fVar3 = fVar3 - compareStart.z;
  return fVar3 * fVar3 + (fVar1 - compareStart.x) * (fVar1 - compareStart.x);
}
