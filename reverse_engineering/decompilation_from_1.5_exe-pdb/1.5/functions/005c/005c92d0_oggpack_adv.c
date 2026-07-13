/*
 * Entry: 005c92d0
 * Name: oggpack_adv
 * Namespace: Global
 * Signature: undefined oggpack_adv()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_adv */

void __cdecl oggpack_adv(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = param_2 + param_1[1];
  if (param_1[4] - ((int)(uVar2 + 7) >> 3) < *param_1) {
    param_1[3] = 0;
    param_1[1] = 1;
    *param_1 = param_1[4];
    return;
  }
  iVar1 = (int)(uVar2 + ((int)uVar2 >> 0x1f & 7U)) >> 3;
  param_1[3] = param_1[3] + iVar1;
  param_1[1] = uVar2 & 7;
  *param_1 = iVar1 + *param_1;
  return;
}
