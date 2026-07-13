/*
 * Entry: 004f3b07
 * Name: Font_Set_Tabs
 * Namespace: Global
 * Signature: void Font_Set_Tabs(int param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Font_Set_Tabs(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = 0;
  if (0 < param_1) {
    do {
      tabdefs[iVar1] = param_2[iVar1];
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_1);
    if (7 < iVar1) {
      return;
    }
  }
  piVar3 = tabdefs + iVar1;
  for (iVar2 = 8 - iVar1; iVar2 != 0; iVar2 = iVar2 + -1) {
    *piVar3 = -1;
    piVar3 = piVar3 + 1;
  }
  return;
}
