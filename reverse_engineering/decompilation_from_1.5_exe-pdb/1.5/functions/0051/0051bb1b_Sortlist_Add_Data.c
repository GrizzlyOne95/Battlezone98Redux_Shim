/*
 * Entry: 0051bb1b
 * Name: Sortlist_Add_Data
 * Namespace: Global
 * Signature: int Sortlist_Add_Data(tag_sortlist * param_1, void * param_2, double param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Sortlist_Add_Data(tag_sortlist *param_1,void *param_2,double param_3)

{
  double *pdVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = param_1->count;
  if (param_1->max_count <= iVar3) {
    return -1;
  }
  iVar4 = 0;
  iVar5 = iVar3 + -1;
  iVar2 = iVar5;
  while (-1 < iVar2) {
    iVar2 = (iVar5 + iVar4) / 2;
    if (param_1->key_list[iVar2] <= param_3) {
      iVar4 = iVar2 + 1;
    }
    else {
      iVar5 = iVar2 + -1;
    }
    iVar2 = iVar5 - iVar4;
  }
  for (; iVar4 < iVar3; iVar3 = iVar3 + -1) {
    param_1->data_list[iVar3] = (param_1->data_list + iVar3)[-1];
  }
  for (iVar3 = param_1->count; iVar4 < iVar3; iVar3 = iVar3 + -1) {
    pdVar1 = param_1->key_list + iVar3;
    *pdVar1 = pdVar1[-1];
  }
  param_1->key_list[iVar4] = param_3;
  param_1->data_list[iVar4] = param_2;
  param_1->count = param_1->count + 1;
  return 0;
}
