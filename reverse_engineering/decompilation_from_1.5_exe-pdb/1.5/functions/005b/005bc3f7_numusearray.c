/*
 * Entry: 005bc3f7
 * Name: numusearray
 * Namespace: Global
 * Signature: int numusearray(Table * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl numusearray(Table *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_c;
  int local_8;
  
  iVar6 = 0;
  iVar3 = 1;
  local_c = 0;
  local_8 = 1;
  do {
    iVar1 = param_1->sizearray;
    iVar4 = 0;
    iVar2 = iVar3;
    if ((iVar1 < iVar3) && (iVar2 = iVar1, iVar1 < local_8)) {
      return local_c;
    }
    if (local_8 <= iVar2) {
      iVar2 = (iVar2 - local_8) + 1;
      iVar1 = local_8 + iVar2;
      piVar5 = &param_1->array[local_8 + -1].tt;
      do {
        if (*piVar5 != 0) {
          iVar4 = iVar4 + 1;
        }
        piVar5 = piVar5 + 4;
        iVar2 = iVar2 + -1;
        local_8 = iVar1;
      } while (iVar2 != 0);
    }
    local_c = local_c + iVar4;
    param_2[iVar6] = param_2[iVar6] + iVar4;
    iVar6 = iVar6 + 1;
    iVar3 = iVar3 * 2;
  } while (iVar6 < 0x1b);
  return local_c;
}
