/*
 * Entry: 005b2610
 * Name: res2_class
 * Namespace: Global
 * Signature: long * * res2_class(vorbis_block * param_1, void * param_2, int * * param_3, int * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long ** __cdecl
res2_class(vorbis_block *param_1,void *param_2,int **param_3,int *param_4,int param_5)

{
  int iVar1;
  long **pplVar2;
  int iVar3;
  int unaff_retaddr;
  
  iVar3 = 0;
  iVar1 = 0;
  if (0 < param_5) {
    do {
      if (param_4[iVar1] != 0) {
        iVar3 = iVar3 + 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_5);
    if (iVar3 != 0) {
      pplVar2 = _2class(param_2,param_3,(int **)param_5,unaff_retaddr);
      return pplVar2;
    }
  }
  return (long **)0x0;
}
