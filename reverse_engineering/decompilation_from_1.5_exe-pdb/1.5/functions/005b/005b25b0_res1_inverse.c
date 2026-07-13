/*
 * Entry: 005b25b0
 * Name: res1_inverse
 * Namespace: Global
 * Signature: int res1_inverse(vorbis_block * param_1, void * param_2, float * * param_3, int * param_4, int param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
res1_inverse(vorbis_block *param_1,void *param_2,float **param_3,int *param_4,int param_5)

{
  float **ppfVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_5) {
    ppfVar1 = param_3;
    do {
      if (*(int *)(((int)param_4 - (int)param_3) + (int)ppfVar1) != 0) {
        param_3[iVar2] = *ppfVar1;
        iVar2 = iVar2 + 1;
      }
      ppfVar1 = ppfVar1 + 1;
      param_5 = param_5 + -1;
    } while (param_5 != 0);
    if (iVar2 != 0) {
      iVar2 = _01inverse(param_1,param_2,param_3,iVar2,vorbis_book_decodev_add);
      return iVar2;
    }
  }
  return 0;
}
