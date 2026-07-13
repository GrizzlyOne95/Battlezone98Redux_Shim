/*
 * Entry: 005b2550
 * Name: res1_class
 * Namespace: Global
 * Signature: long * * res1_class(vorbis_block * param_1, void * param_2, int * * param_3, int * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long ** __cdecl
res1_class(vorbis_block *param_1,void *param_2,int **param_3,int *param_4,int param_5)

{
  int **ppiVar1;
  long **pplVar2;
  int **ppiVar3;
  int unaff_ESI;
  
  ppiVar3 = (int **)0x0;
  if (0 < param_5) {
    ppiVar1 = param_3;
    do {
      if (*(int *)(((int)param_4 - (int)param_3) + (int)ppiVar1) != 0) {
        param_3[(int)ppiVar3] = *ppiVar1;
        ppiVar3 = (int **)((int)ppiVar3 + 1);
      }
      ppiVar1 = ppiVar1 + 1;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
    if (ppiVar3 != (int **)0x0) {
      pplVar2 = _01class(param_2,param_3,ppiVar3,unaff_ESI);
      return pplVar2;
    }
  }
  return (long **)0x0;
}
