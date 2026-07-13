/*
 * Entry: 004cb8c6
 * Name: EditTerrain::CmdBlur
 * Namespace: EditTerrain
 * Signature: void CmdBlur(EditTerrain * this, ushort * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall
EditTerrain::CmdBlur(EditTerrain *this,ushort *param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  float fVar2;
  double dVar3;
  ushort *puVar4;
  int iVar5;
  int iVar6;
  uint local_24;
  float (*local_14) [17];
  float (*local_10) [17];
  int local_c;
  int local_8;
  
  fVar2 = 0.0;
  iVar1 = this->blurWidth;
  iVar6 = param_2 - iVar1 / 2;
  local_c = param_3 - iVar1 / 2;
  iVar5 = iVar1 + local_c;
  if (local_c <= iVar5) {
    local_14 = this->blur;
    do {
      if (iVar6 <= iVar1 + iVar6) {
        local_10 = local_14;
        local_8 = iVar6;
        do {
          puVar4 = GetZonePtr(local_8,local_c);
          local_8 = local_8 + 1;
          fVar2 = (float)(*puVar4 & 0xfff) * (*local_10)[0] + fVar2;
          local_10 = (float (*) [17])(*local_10 + 1);
        } while (local_8 <= iVar1 + iVar6);
      }
      local_c = local_c + 1;
      local_14 = local_14 + 1;
    } while (local_c <= iVar5);
  }
  dVar3 = Float2Int + (double)fVar2 + 0.5;
  local_24 = SUB84(dVar3,0);
  if ((*param_1 & 0xfff) != local_24) {
    PushUndoGrid(this,param_2,param_3,(uint)*param_1,param_4,0);
    *param_1 = SUB82(dVar3,0);
    RecomputeTerrainValues(param_2 + -2,param_3 + -2,param_2 + 2,param_3 + 2);
  }
  return;
}
