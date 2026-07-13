/*
 * Entry: 005afe90
 * Name: vorbis_lpc_predict
 * Namespace: Global
 * Signature: void vorbis_lpc_predict(float * param_1, float * param_2, int param_3, float * param_4, long param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void __cdecl
vorbis_lpc_predict(float *param_1,float *param_2,int param_3,float *param_4,long param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  
  iVar2 = param_3;
  iVar1 = (param_5 + param_3) * -4;
  puVar9 = (undefined4 *)(&stack0xffffffe4 + iVar1);
  pfVar5 = (float *)(&stack0xffffffe4 + iVar1);
  if (param_2 == (float *)0x0) {
    if (0 < param_3) {
      for (; param_3 != 0; param_3 = param_3 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
    }
  }
  else if (0 < param_3) {
    for (; param_3 != 0; param_3 = param_3 + -1) {
      *pfVar5 = *param_2;
      param_2 = param_2 + 1;
      pfVar5 = pfVar5 + 1;
    }
  }
  param_2 = (float *)0x0;
  if (0 < param_5) {
    pfVar5 = (float *)(&stack0xffffffec + iVar1);
    do {
      iVar8 = 0;
      param_3 = 0;
      pfVar4 = param_2;
      iVar10 = iVar2;
      if (3 < iVar2) {
        iVar3 = (iVar2 - 4U >> 2) + 1;
        iVar8 = iVar3 * 4;
        pfVar4 = param_2 + iVar3;
        iVar10 = iVar2 + iVar3 * -4;
        pfVar6 = pfVar5;
        pfVar7 = param_1 + iVar2 + -2;
        do {
          iVar3 = iVar3 + -1;
          param_3 = (int)(((((float)param_3 - pfVar7[1] * pfVar6[-2]) - pfVar6[-1] * *pfVar7) -
                          pfVar7[-1] * *pfVar6) - pfVar7[-2] * pfVar6[1]);
          pfVar6 = pfVar6 + 4;
          pfVar7 = pfVar7 + -4;
        } while (iVar3 != 0);
      }
      if (iVar8 < iVar2) {
        pfVar6 = param_1 + iVar10;
        iVar8 = iVar2 - iVar8;
        do {
          iVar10 = (int)pfVar4 * 4;
          pfVar6 = pfVar6 + -1;
          pfVar4 = (float *)((int)pfVar4 + 1);
          iVar8 = iVar8 + -1;
          param_3 = (int)((float)param_3 - *(float *)(&stack0xffffffe4 + iVar10 + iVar1) * *pfVar6);
        } while (iVar8 != 0);
      }
      *(int *)(&stack0xffffffe4 + (int)pfVar4 * 4 + iVar1) = param_3;
      param_4[(int)param_2] = (float)param_3;
      param_2 = (float *)((int)param_2 + 1);
      pfVar5 = pfVar5 + 1;
    } while ((int)param_2 < param_5);
  }
  return;
}
