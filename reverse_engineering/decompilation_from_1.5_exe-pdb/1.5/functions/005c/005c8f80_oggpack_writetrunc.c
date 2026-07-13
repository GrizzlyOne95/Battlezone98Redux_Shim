/*
 * Entry: 005c8f80
 * Name: oggpack_writetrunc
 * Namespace: Global
 * Signature: undefined oggpack_writetrunc()
 * Symbol source: ANALYSIS
 * Export status: ok
 */

/* oggpack_writetrunc */

void __cdecl oggpack_writetrunc(int *param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  
  iVar1 = param_2 >> 3;
  if (param_1[3] != 0) {
    param_2 = param_2 + iVar1 * -8;
    pbVar2 = (byte *)(param_1[2] + iVar1);
    param_1[1] = param_2;
    param_1[3] = (int)pbVar2;
    *param_1 = iVar1;
    *pbVar2 = *pbVar2 & (&DAT_00623708)[param_2 * 4];
  }
  return;
}
