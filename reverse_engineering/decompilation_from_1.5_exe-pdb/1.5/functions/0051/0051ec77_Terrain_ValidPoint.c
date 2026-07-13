/*
 * Entry: 0051ec77
 * Name: Terrain_ValidPoint
 * Namespace: Global
 * Signature: int Terrain_ValidPoint(double param_1, double param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Terrain_ValidPoint(double param_1,double param_2)

{
  param_1._0_4_ = SUB84((double)((float)param_1 * Terrain.Grid_Scale + (float)Float2Int),0);
  if (param_1._0_4_ + 0xbffU < 0x3ffe) {
    param_2._0_4_ = SUB84((double)(Terrain.Grid_Scale * (float)param_2 + (float)Float2Int),0);
    if ((param_2._0_4_ + 0xbffU < 0x3ffe) && ((param_1._0_4_ != 0 || (param_2._0_4_ != 0)))) {
      return 1;
    }
  }
  return 0;
}
