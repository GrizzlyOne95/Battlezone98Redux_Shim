/*
 * Entry: 0044e590
 * Name: MaterialCost
 * Namespace: Global
 * Signature: float MaterialCost(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float __cdecl MaterialCost(int param_1)

{
  float fVar1;
  
  fVar1 = materialCost[param_1 & 0xff];
  if ((ushort)((ushort)((uint)param_1 >> 0x10) & (ushort)_curPathingEnemies) != 0) {
    fVar1 = fVar1 + 2.0;
  }
  return fVar1;
}
