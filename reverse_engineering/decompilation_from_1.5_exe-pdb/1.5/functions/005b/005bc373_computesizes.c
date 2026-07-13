/*
 * Entry: 005bc373
 * Name: computesizes
 * Namespace: Global
 * Signature: int computesizes(int * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl computesizes(int *param_1,int *param_2)

{
  int iVar1;
  int *in_EAX;
  int *in_ECX;
  int iVar2;
  int iVar3;
  int local_10;
  int local_c;
  int *local_8;
  
  iVar2 = 0;
  iVar1 = *in_ECX;
  iVar3 = 1;
  local_10 = 0;
  local_c = 0;
  local_8 = in_EAX;
  if (0 < iVar1) {
    do {
      if ((0 < *local_8) && (iVar2 = iVar2 + *local_8, iVar3 / 2 < iVar2)) {
        local_10 = iVar2;
        local_c = iVar3;
      }
      if (iVar2 == iVar1) break;
      local_8 = local_8 + 1;
      iVar3 = iVar3 * 2;
    } while (iVar3 / 2 < iVar1);
  }
  *in_ECX = local_c;
  return local_10;
}
