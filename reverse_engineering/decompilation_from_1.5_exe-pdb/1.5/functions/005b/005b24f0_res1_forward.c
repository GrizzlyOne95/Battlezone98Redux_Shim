/*
 * Entry: 005b24f0
 * Name: res1_forward
 * Namespace: Global
 * Signature: int res1_forward(oggpack_buffer * param_1, vorbis_block * param_2, void * param_3, int * * param_4, int * param_5, int param_6, long * * param_7, int param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
res1_forward(oggpack_buffer *param_1,vorbis_block *param_2,void *param_3,int **param_4,int *param_5,
            int param_6,long **param_7,int param_8)

{
  int **ppiVar1;
  int iVar2;
  
  iVar2 = 0;
  if (0 < param_6) {
    ppiVar1 = param_4;
    do {
      if (*(int *)(((int)param_5 - (int)param_4) + (int)ppiVar1) != 0) {
        param_4[iVar2] = *ppiVar1;
        iVar2 = iVar2 + 1;
      }
      ppiVar1 = ppiVar1 + 1;
      param_6 = param_6 + -1;
    } while (param_6 != 0);
    if (iVar2 != 0) {
      iVar2 = _01forward(param_1,param_3,param_4,iVar2,param_7,_encodepart);
      return iVar2;
    }
  }
  return 0;
}
