/*
 * Entry: 0059aff0
 * Name: _add_serialno
 * Namespace: Global
 * Signature: void _add_serialno(ogg_page * param_1, long * * param_2, int * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl _add_serialno(ogg_page *param_1,long **param_2,int *param_3)

{
  long lVar1;
  long *plVar2;
  
  lVar1 = ogg_page_serialno(param_1);
  *param_3 = *param_3 + 1;
  if (*param_2 == (long *)0x0) {
    plVar2 = malloc(4);
    *param_2 = plVar2;
  }
  else {
    plVar2 = realloc(*param_2,*param_3 << 2);
    *param_2 = plVar2;
  }
  (*param_2)[*param_3 + -1] = lVar1;
  return;
}
