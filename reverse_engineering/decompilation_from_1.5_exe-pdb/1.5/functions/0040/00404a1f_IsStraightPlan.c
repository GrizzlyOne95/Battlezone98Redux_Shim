/*
 * Entry: 00404a1f
 * Name: IsStraightPlan
 * Namespace: Global
 * Signature: bool IsStraightPlan(float param_1, float param_2, float param_3, float param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl IsStraightPlan(float param_1,float param_2,float param_3,float param_4,int param_5)

{
  VECTOR_3D_LONG VVar1;
  VECTOR_3D VVar2;
  uchar uVar3;
  uchar uVar4;
  int iVar5;
  Team *this;
  ulong uVar6;
  float local_8;
  
  uVar3 = CellRegion(param_1,param_2);
  uVar4 = CellRegion(param_3,param_4);
  if (uVar3 == uVar4) {
    cellType0 = CellType(param_3,param_4);
    cellTypeMask = 0xff;
    iVar5 = Material((uint)cellType0);
    if ((iVar5 != 6) && (iVar5 != 5)) {
      cellTeam0 = CellTeam(param_3,param_4);
      this = Team::GetTeam(param_5);
      uVar6 = Team::GetAllies(this);
      cellTeamMask = ~(ushort)uVar6;
      local_8 = 1.0;
      VVar1.y = 0.0;
      VVar1.x = (double)param_3;
      VVar1.z = (double)param_4;
      VVar2.y = 0.0;
      VVar2.x = param_1 - param_3;
      VVar2.z = param_2 - param_4;
      iVar5 = Terrain_FindChange(VVar1,VVar2,CellTypeChange,&local_8);
      return (bool)('\x01' - (iVar5 != 0));
    }
  }
  return false;
}
