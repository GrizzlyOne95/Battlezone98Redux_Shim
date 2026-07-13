/*
 * Entry: 0040feb3
 * Name: CellIsBuilding
 * Namespace: Global
 * Signature: bool CellIsBuilding(float param_1, float param_2, float param_3, float param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellIsBuilding(float param_1,float param_2,float param_3,float param_4,int param_5)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = CellType(param_3,param_4);
  iVar2 = Material((uint)bVar1);
  return iVar2 == 5;
}
