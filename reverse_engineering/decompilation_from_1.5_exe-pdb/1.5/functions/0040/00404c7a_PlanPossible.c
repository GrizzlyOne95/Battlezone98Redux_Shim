/*
 * Entry: 00404c7a
 * Name: PlanPossible
 * Namespace: Global
 * Signature: bool PlanPossible(float param_1, float param_2, float param_3, float param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl PlanPossible(float param_1,float param_2,float param_3,float param_4)

{
  uchar uVar1;
  uchar uVar2;
  
  uVar1 = CellRegion(param_1,param_2);
  uVar2 = CellRegion(param_3,param_4);
  if (((uVar1 != '\0') && (uVar2 != '\0')) && (uVar1 == uVar2)) {
    return true;
  }
  return false;
}
