/*
 * Entry: 00405039
 * Name: CellIsSteep
 * Namespace: Global
 * Signature: bool CellIsSteep(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellIsSteep(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = param_1 + 1;
  iVar1 = GetTerY(iVar4,param_2);
  iVar2 = GetTerY(param_1,param_2);
  uVar5 = iVar2 - iVar1 >> 0x1f;
  if ((int)((iVar2 - iVar1 ^ uVar5) - uVar5) < 0x47) {
    iVar1 = param_2 + 1;
    iVar2 = GetTerY(iVar4,iVar1);
    iVar3 = GetTerY(iVar4,param_2);
    uVar5 = iVar3 - iVar2 >> 0x1f;
    if ((int)((iVar3 - iVar2 ^ uVar5) - uVar5) < 0x47) {
      iVar4 = GetTerY(iVar4,iVar1);
      iVar2 = GetTerY(param_1,iVar1);
      uVar5 = iVar4 - iVar2 >> 0x1f;
      if ((int)((iVar4 - iVar2 ^ uVar5) - uVar5) < 0x47) {
        iVar4 = GetTerY(param_1,iVar1);
        iVar1 = GetTerY(param_1,param_2);
        uVar5 = iVar4 - iVar1 >> 0x1f;
        if ((int)((iVar4 - iVar1 ^ uVar5) - uVar5) < 0x47) {
          return false;
        }
      }
    }
  }
  return true;
}
