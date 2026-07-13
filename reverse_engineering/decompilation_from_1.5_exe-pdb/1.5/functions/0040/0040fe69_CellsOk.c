/*
 * Entry: 0040fe69
 * Name: CellsOk
 * Namespace: Global
 * Signature: bool CellsOk(float param_1, float param_2, float param_3, float param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellsOk(float param_1,float param_2,float param_3,float param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  float fVar3;
  
  bVar1 = CellType(param_3,param_4);
  iVar2 = Material((uint)bVar1);
  SetPathingType(param_5,0);
  fVar3 = MaterialCost(iVar2);
  if (fVar3 == 99999.0) {
    return false;
  }
  return true;
}
