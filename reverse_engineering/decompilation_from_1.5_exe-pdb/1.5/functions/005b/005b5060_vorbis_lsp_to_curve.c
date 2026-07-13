/*
 * Entry: 005b5060
 * Name: vorbis_lsp_to_curve
 * Namespace: Global
 * Signature: void vorbis_lsp_to_curve(float * param_1, int * param_2, int param_3, int param_4, float * param_5, int param_6, float param_7, float param_8)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
vorbis_lsp_to_curve(float *param_1,int *param_2,int param_3,int param_4,float *param_5,int param_6,
                   float param_7,float param_8)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float10 fVar5;
  
  iVar3 = 0;
  if (0 < param_6) {
    do {
      fVar5 = (float10)__CIcos();
      iVar4 = iVar3 + 1;
      param_5[iVar3] = (float)(fVar5 + fVar5);
      iVar3 = iVar4;
    } while (iVar4 < param_6);
  }
  iVar3 = 0;
  if (0 < param_3) {
    iVar4 = 0;
    iVar1 = *param_2;
    do {
      __CIcos();
      iVar2 = 1;
      if (1 < param_6) {
        do {
          iVar2 = iVar2 + 2;
        } while (iVar2 < param_6);
      }
      __CIsqrt();
      fVar5 = (float10)__CIexp();
      *(float *)(iVar4 + (int)param_1) = (float)fVar5 * *(float *)(iVar4 + (int)param_1);
      iVar2 = param_2[iVar3 + 1];
      iVar3 = iVar3 + 1;
      while (iVar4 = iVar3 * 4, iVar2 == iVar1) {
        param_1[iVar3] = param_1[iVar3] * (float)fVar5;
        iVar2 = param_2[iVar3 + 1];
        iVar3 = iVar3 + 1;
      }
      iVar1 = iVar2;
    } while (iVar3 < param_3);
  }
  return;
}
