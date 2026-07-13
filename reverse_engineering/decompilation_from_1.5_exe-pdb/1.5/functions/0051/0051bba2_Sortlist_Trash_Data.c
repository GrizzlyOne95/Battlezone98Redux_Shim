/*
 * Entry: 0051bba2
 * Name: Sortlist_Trash_Data
 * Namespace: Global
 * Signature: void Sortlist_Trash_Data(tag_sortlist * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Sortlist_Trash_Data(tag_sortlist *param_1,int param_2)

{
  double *pdVar1;
  int iVar2;
  
  iVar2 = param_2;
  if (param_2 < param_1->count) {
    do {
      pdVar1 = param_1->key_list + iVar2;
      iVar2 = iVar2 + 1;
      *pdVar1 = pdVar1[1];
    } while (iVar2 < param_1->count);
    for (; param_2 < param_1->count; param_2 = param_2 + 1) {
      param_1->data_list[param_2] = (param_1->data_list + param_2)[1];
    }
  }
  param_1->count = param_1->count + -1;
  return;
}
