/*
 * Entry: 00405221
 * Name: HazardCells
 * Namespace: Global
 * Signature: void HazardCells(float param_1, float param_2, float param_3, int param_4, bool param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HazardCells(float param_1,float param_2,float param_3,int param_4,bool param_5)

{
  ushort *puVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  ushort *puVar10;
  int extraout_EAX;
  int iVar11;
  int extraout_EAX_00;
  int iVar12;
  int extraout_EAX_01;
  int iVar13;
  int extraout_EAX_02;
  int iVar14;
  int iVar15;
  char *pcVar16;
  int iVar17;
  int iVar18;
  
  iVar14 = GridMinX;
  iVar15 = GridMaxX - GridMinX;
  iVar13 = iVar15 + -1;
  iVar17 = 0;
  cVar2 = param_5 * '\x02';
  iVar11 = iVar13;
  floor((double)((param_1 - param_3) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar11 = Clamp(extraout_EAX - iVar14,iVar17,iVar11);
  iVar17 = 0;
  floor((double)((param_1 + param_3) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar17 = Clamp(extraout_EAX_00 - iVar14,iVar17,iVar13);
  iVar14 = GridMinZ;
  iVar12 = (GridMaxZ - GridMinZ) + -1;
  iVar18 = 0;
  iVar13 = iVar12;
  floor((double)((param_2 - param_3) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar13 = Clamp(extraout_EAX_01 - iVar14,iVar18,iVar13);
  iVar18 = 0;
  floor((double)((param_2 + param_3) * Terrain.Grid_Scale));
  _ftol2_sse();
  iVar12 = Clamp(extraout_EAX_02 - iVar14,iVar18,iVar12);
  puVar10 = cellTeam;
  fVar3 = param_1 * Terrain.Grid_Scale;
  fVar8 = (float)GridMinX;
  fVar4 = Terrain.Grid_Scale * param_2;
  fVar9 = (float)GridMinZ;
  iVar14 = iVar15 * iVar13 + iVar11;
  fVar5 = Terrain.Grid_Scale * param_3;
  for (; iVar13 <= iVar12; iVar13 = iVar13 + 1) {
    if (iVar11 <= iVar17) {
      fVar6 = (float)iVar13 - ((fVar4 - fVar9) - 0.5);
      _param_5 = iVar11;
      do {
        fVar7 = (float)_param_5 - ((fVar3 - fVar8) - 0.5);
        if (fVar7 * fVar7 + fVar6 * fVar6 < fVar5 * fVar5) {
          pcVar16 = cellTeamRef[param_4] + iVar14;
          *pcVar16 = *pcVar16 + cVar2 + -1;
          if (cellTeamRef[param_4][iVar14] < '\x01') {
            puVar1 = puVar10 + iVar14;
            *puVar1 = *puVar1 & ~(ushort)(1 << ((byte)param_4 & 0x1f));
          }
          else {
            puVar1 = puVar10 + iVar14;
            *puVar1 = *puVar1 | (ushort)(1 << ((byte)param_4 & 0x1f));
          }
        }
        iVar14 = iVar14 + 1;
        _param_5 = _param_5 + 1;
      } while (_param_5 <= iVar17);
    }
    iVar14 = iVar14 + (iVar15 - iVar17) + -1 + iVar11;
  }
  InvalidateStrips(param_1 - param_3,param_2 - param_3,param_1 + param_3,param_2 + param_3);
  return;
}
