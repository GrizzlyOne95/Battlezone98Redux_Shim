/*
 * Entry: 00454be0
 * Name: RebuildStrips
 * Namespace: Global
 * Signature: void RebuildStrips(float param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl RebuildStrips(float param_1,float param_2,float param_3,float param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar4;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar5;
  int iVar6;
  int unaff_ESI;
  int unaff_EDI;
  
  fVar1 = param_1 * Terrain.Grid_Scale;
  fVar2 = param_3 * Terrain.Grid_Scale;
  fVar3 = param_4 * Terrain.Grid_Scale;
  floor((double)(Terrain.Grid_Scale * param_2));
  _ftol2_sse();
  iVar6 = (int)((extraout_EAX - GridMinZ) + (extraout_EAX - GridMinZ >> 0x1f & 0xfU)) >> 4;
  ceil((double)fVar3);
  _ftol2_sse();
  iVar4 = (extraout_EAX_00 - GridMinZ) + 0xf;
  iVar4 = (int)(iVar4 + (iVar4 >> 0x1f & 0xfU)) >> 4;
  floor((double)fVar1);
  _ftol2_sse();
  param_4 = (float)((int)((extraout_EAX_01 - GridMinX) + (extraout_EAX_01 - GridMinX >> 0x1f & 0xfU)
                         ) >> 4);
  ceil((double)fVar2);
  _ftol2_sse();
  iVar5 = (extraout_EAX_02 - GridMinX) + 0xf;
  iVar5 = (int)(iVar5 + (iVar5 >> 0x1f & 0xfU)) >> 4;
  if ((((-1 < iVar4) && (-1 < iVar5)) && (iVar6 < zoneHeight)) && ((int)param_4 < zoneWidth)) {
    if (iVar6 < 0) {
      iVar6 = 0;
    }
    if ((int)param_4 < 0) {
      param_4 = 0.0;
    }
    if (zoneHeight < iVar4) {
      iVar4 = zoneHeight;
    }
    if (zoneWidth < iVar5) {
      iVar5 = zoneWidth;
    }
    for (; fVar1 = param_4, iVar6 < iVar4; iVar6 = iVar6 + 1) {
      for (; (int)fVar1 < iVar5; fVar1 = (float)((int)fVar1 + 1)) {
        BuildZone(unaff_EDI,unaff_ESI);
      }
    }
  }
  return;
}
