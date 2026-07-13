/*
 * Entry: 0051fb39
 * Name: inverseLighting
 * Namespace: Global
 * Signature: float inverseLighting(long param_1, long param_2, long param_3, long param_4, VECTOR_3D * param_5, tagLIGHTING * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
inverseLighting(long param_1,long param_2,long param_3,long param_4,VECTOR_3D *param_5,
               tagLIGHTING *param_6)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int unaff_ESI;
  int unaff_EDI;
  int local_1c;
  uint local_14;
  
  for (; iVar3 = param_1, param_2 <= param_4; param_2 = param_2 + 1) {
    for (; iVar3 <= param_3; iVar3 = iVar3 + 1) {
      local_14 = SUB84((double)(param_5->x + (float)Float2Int),0);
      local_1c = SUB84((double)((float)Float2Int + param_5->z),0);
      local_1c = ((int)((local_14 ^ (int)local_14 >> 0x1f) - ((int)local_14 >> 0x1f)) >> 1) +
                 local_1c;
      if (local_1c < TerrainView.Fog_End) {
        iVar2 = GetNormal(unaff_EDI,unaff_ESI);
        fVar1 = (float)iVar2 * TerrainView.Intensity256 + TerrainView.Ambient;
        if (TerrainView.Fog_Start < local_1c) {
          fVar1 = fVar1 * fogTable[local_1c];
        }
      }
      else {
        fVar1 = 0.0;
      }
      param_6->luma = fVar1;
      param_5 = param_5 + 1;
      param_6 = param_6 + 1;
    }
  }
  return 0.0;
}
