/*
 * Entry: 004d14db
 * Name: BestColor
 * Namespace: Global
 * Signature: int BestColor(int param_1, int param_2, int param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl BestColor(int param_1,int param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  int local_c;
  int local_8;
  
  local_c = -1;
  local_8 = 0;
  iVar3 = 0x7fffffff;
  pbVar2 = &DAT_0062c431;
  do {
    iVar1 = (param_3 - (uint)pbVar2[1]) * (param_3 - (uint)pbVar2[1]) +
            (param_2 - (uint)*pbVar2) * (param_2 - (uint)*pbVar2) +
            (param_1 - (uint)pbVar2[-1]) * (param_1 - (uint)pbVar2[-1]);
    if (iVar1 < iVar3) {
      local_c = local_8;
      iVar3 = iVar1;
    }
    local_8 = local_8 + 1;
    pbVar2 = pbVar2 + 3;
  } while ((int)pbVar2 < 0x62c731);
  return local_c;
}
