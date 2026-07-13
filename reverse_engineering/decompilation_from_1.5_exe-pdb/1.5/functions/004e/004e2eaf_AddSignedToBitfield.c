/*
 * Entry: 004e2eaf
 * Name: AddSignedToBitfield
 * Namespace: Global
 * Signature: void AddSignedToBitfield(int param_1, void * param_2, uint param_3, uint param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl AddSignedToBitfield(int param_1,void *param_2,uint param_3,uint param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 1 << ((char)param_4 - 1U & 0x1f);
  iVar2 = -iVar1;
  if ((iVar2 <= param_1) && (iVar1 = iVar1 + -1, iVar2 = param_1, iVar1 < param_1)) {
    iVar2 = iVar1;
  }
  AddToBitfield(iVar2,param_2,param_3,param_4);
  return;
}
