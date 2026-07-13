/*
 * Entry: 0052925f
 * Name: zixMatchWild
 * Namespace: Global
 * Signature: char * zixMatchWild(char * param_1, int * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

char * __cdecl zixMatchWild(char *param_1,int *param_2)

{
  int iVar1;
  ZIX_FENTRY_TYPE *pZVar2;
  
  if ((param_1 != (char *)0x0) && (iVar1 = *param_2, -1 < iVar1)) {
    while (iVar1 < num_fentries) {
      iVar1 = wildmat(fentry[*param_2].name,param_1);
      if (iVar1 != 0) {
        pZVar2 = fentry + *param_2;
        *param_2 = *param_2 + 1;
        return pZVar2->name;
      }
      *param_2 = *param_2 + 1;
      iVar1 = *param_2;
    }
  }
  return (char *)0x0;
}
