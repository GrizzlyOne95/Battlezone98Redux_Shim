/*
 * Entry: 0051f933
 * Name: FogAndLumaLighting
 * Namespace: Global
 * Signature: float FogAndLumaLighting(long param_1, long param_2, long param_3, long param_4, VECTOR_3D * param_5, tagLIGHTING * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl
FogAndLumaLighting(long param_1,long param_2,long param_3,long param_4,VECTOR_3D *param_5,
                  tagLIGHTING *param_6)

{
  long lVar1;
  ushort *puVar2;
  int extraout_EAX;
  int iVar3;
  int iVar4;
  int unaff_ESI;
  int unaff_EDI;
  int local_2c;
  uint local_24;
  long local_8;
  
  iVar4 = groundFogStart;
  if (groundFogTop == 0) {
    for (; param_2 <= param_4; param_2 = param_2 + 1) {
      for (local_8 = param_1; local_8 <= param_3; local_8 = local_8 + 1) {
        local_24 = SUB84((double)(param_5->x + (float)Float2Int),0);
        local_2c = SUB84((double)((float)Float2Int + param_5->z),0);
        local_2c = ((int)((local_24 ^ (int)local_24 >> 0x1f) - ((int)local_24 >> 0x1f)) >> 1) +
                   local_2c;
        iVar4 = GetNormal(unaff_EDI,unaff_ESI);
        lVar1 = TerrainView.Fog_End;
        (param_6->l).intensity = (uchar)iVar4;
        if (local_2c < lVar1) {
          if (TerrainView.Fog_Start < local_2c) {
            (param_6->l).fogginess = (uchar)fogTable256[local_2c];
          }
          else {
            (param_6->l).fogginess = 0xff;
          }
        }
        else {
          (param_6->l).fogginess = '\0';
        }
        param_5 = param_5 + 1;
        param_6 = param_6 + 1;
      }
    }
  }
  else {
    if ((groundFogTop - groundFogBottom < 1) || (NormalView.Fog_End - NormalView.Fog_Start < 1)) {
      groundFogScale = 0.0;
    }
    else {
      groundFogScale =
           ((float)(NormalView.Fog_End - NormalView.Fog_Start) * visibilityScale * 10.0) /
           (float)(groundFogTop - groundFogBottom);
    }
    for (; param_2 <= param_4; param_2 = param_2 + 1) {
      for (local_8 = param_1; local_8 <= param_3; local_8 = local_8 + 1) {
        local_24 = SUB84((double)(param_5->x + (float)Float2Int),0);
        local_2c = SUB84((double)((float)Float2Int + param_5->z),0);
        local_2c = ((int)((local_24 ^ (int)local_24 >> 0x1f) - ((int)local_24 >> 0x1f)) >> 1) +
                   local_2c;
        puVar2 = GetZonePtr(local_8,param_2);
        if ((0 < (int)(groundFogTop - (*puVar2 & 0xfff))) && ((iVar4 < local_2c || (0 < local_2c))))
        {
          _ftol2_sse();
          local_2c = extraout_EAX;
        }
        iVar3 = GetNormal(unaff_EDI,unaff_ESI);
        lVar1 = TerrainView.Fog_End;
        (param_6->l).intensity = (uchar)iVar3;
        if (local_2c < lVar1) {
          if (TerrainView.Fog_Start < local_2c) {
            (param_6->l).fogginess = (uchar)fogTable256[local_2c];
          }
          else {
            (param_6->l).fogginess = 0xff;
          }
        }
        else {
          (param_6->l).fogginess = '\0';
        }
        param_5 = param_5 + 1;
        param_6 = param_6 + 1;
      }
    }
  }
  return 0.0;
}
