/*
 * Entry: 0040fedc
 * Name: CellTypeChange
 * Namespace: Global
 * Signature: bool CellTypeChange(float param_1, float param_2, float param_3, float param_4, int param_5, float * param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
CellTypeChange(float param_1,float param_2,float param_3,float param_4,int param_5,float *param_6)

{
  bool bVar1;
  Team *this;
  ulong uVar2;
  
  cellType0 = CellType(param_1,param_2);
  cellTypeMask = 0xff;
  cellTeam0 = CellTeam(param_1,param_2);
  this = Team::GetTeam(param_5);
  uVar2 = Team::GetAllies(this);
  cellTeamMask = ~(ushort)uVar2;
  bVar1 = FindChange((VECTOR_2D *)CellTypeChange,(VECTOR_2D *)param_6,
                     (_func___cdecl_int_long_long *)param_1,(float *)param_2);
  return bVar1;
}
