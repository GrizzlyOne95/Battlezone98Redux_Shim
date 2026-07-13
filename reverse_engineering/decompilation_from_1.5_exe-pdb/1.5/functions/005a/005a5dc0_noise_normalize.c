/*
 * Entry: 005a5dc0
 * Name: noise_normalize
 * Namespace: Global
 * Signature: float noise_normalize(vorbis_look_psy * param_1, int param_2, float * param_3, float * param_4, float * param_5, int * param_6, float param_7, int param_8, int param_9, int * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

float __cdecl
noise_normalize(vorbis_look_psy *param_1,int param_2,float *param_3,float *param_4,float *param_5,
               int *param_6,float param_7,int param_8,int param_9,int *param_10)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int in_EAX;
  float fVar4;
  undefined4 extraout_EAX;
  undefined4 extraout_EAX_00;
  int extraout_EAX_01;
  undefined4 extraout_EAX_02;
  undefined4 *puVar5;
  undefined1 *puVar6;
  undefined4 *puVar8;
  undefined1 *puVar9;
  int iVar11;
  int *piVar12;
  int unaff_EDI;
  float10 fVar13;
  float10 extraout_ST0;
  float10 extraout_ST1;
  float local_1c;
  int local_c;
  float local_8;
  undefined4 *puVar7;
  undefined4 *puVar10;
  
  iVar2 = *(int *)(in_EAX + 4);
  iVar3 = (int)param_7 * -4;
  puVar6 = &stack0xffffffcc + iVar3;
  local_c = 0;
  if ((*(int *)(iVar2 + 500) == 0) ||
     (fVar4 = (float)(*(int *)(iVar2 + 0x1f8) - (int)param_6), (int)param_7 < (int)fVar4)) {
    fVar4 = param_7;
  }
  param_5 = (float *)0x0;
  local_8 = 0.0;
  puVar9 = &stack0xffffffcc + iVar3;
  if (0 < (int)fVar4) {
    iVar11 = unaff_EDI;
    local_1c = fVar4;
    do {
      if ((param_4 == (float *)0x0) || (*(int *)((int)param_4 + (iVar11 - unaff_EDI)) == 0)) {
        if (0.0 <= *(float *)((param_2 - unaff_EDI) + iVar11)) {
          puVar7 = (undefined4 *)(puVar6 + -4);
          puVar6 = puVar6 + -4;
          *puVar7 = 0x5a5e99;
          fVar13 = (float10)__CIsqrt();
          *(double *)(puVar6 + -8) = (double)(fVar13 + (float10)0.5);
          *(undefined4 *)(puVar6 + -0xc) = 0x5a5eaa;
          floor();
          *(undefined4 *)(puVar6 + -4) = 0x5a5eb2;
          _ftol2_sse();
          *(undefined4 *)((param_8 - unaff_EDI) + iVar11) = extraout_EAX_00;
        }
        else {
          puVar5 = (undefined4 *)(puVar6 + -4);
          puVar6 = puVar6 + -4;
          *puVar5 = 0x5a5e71;
          fVar13 = (float10)__CIsqrt();
          *(double *)(puVar6 + -8) = (double)(fVar13 + (float10)0.5);
          *(undefined4 *)(puVar6 + -0xc) = 0x5a5e82;
          floor();
          *(undefined4 *)(puVar6 + -4) = 0x5a5e8c;
          _ftol2_sse();
          *(undefined4 *)((param_8 - unaff_EDI) + iVar11) = extraout_EAX;
        }
      }
      iVar11 = iVar11 + 4;
      local_1c = (float)((int)local_1c + -1);
      puVar9 = puVar6;
      local_8 = fVar4;
    } while (local_1c != 0.0);
  }
  if ((int)local_8 < (int)param_7) {
    piVar12 = (int *)(param_8 + (int)local_8 * 4);
    do {
      if ((param_4 == (float *)0x0) ||
         (*(int *)((int)param_4 + ((param_2 - param_8) - param_2) + (int)piVar12) == 0)) {
        pfVar1 = (float *)((unaff_EDI - param_8) + (int)piVar12);
        fVar4 = *(float *)((unaff_EDI - param_8) + (int)piVar12) /
                *(float *)(((int)param_3 - param_8) + (int)piVar12);
        if ((0.25 <= fVar4) ||
           ((param_4 != (float *)0x0 && ((int)local_8 < (int)param_1 - (int)param_6)))) {
          if (0.0 <= *(float *)((param_2 - param_8) + (int)piVar12)) {
            puVar10 = (undefined4 *)(puVar9 + -4);
            puVar9 = puVar9 + -4;
            *puVar10 = 0x5a5f80;
            fVar13 = (float10)__CIsqrt();
            *(double *)(puVar9 + -8) = (double)(fVar13 + (float10)0.5);
            *(undefined4 *)(puVar9 + -0xc) = 0x5a5f91;
            floor();
          }
          else {
            puVar8 = (undefined4 *)(puVar9 + -4);
            puVar9 = puVar9 + -4;
            *puVar8 = 0x5a5f66;
            fVar13 = (float10)__CIsqrt();
            *(double *)(puVar9 + -8) = (double)(fVar13 + (float10)0.5);
            *(undefined4 *)(puVar9 + -0xc) = 0x5a5f77;
            floor();
          }
          *(undefined4 *)(puVar9 + -4) = 0x5a5f99;
          _ftol2_sse();
          *piVar12 = extraout_EAX_01;
          *pfVar1 = (float)(extraout_EAX_01 * extraout_EAX_01) *
                    *(float *)(((int)param_3 - param_8) + (int)piVar12);
        }
        else {
          param_5 = (float *)(fVar4 + (float)param_5);
          *(float **)(&stack0xffffffcc + local_c * 4 + iVar3) = pfVar1;
          local_c = local_c + 1;
        }
      }
      local_8 = (float)((int)local_8 + 1);
      piVar12 = piVar12 + 1;
    } while ((int)local_8 < (int)param_7);
    if (local_c != 0) {
      *(code **)(puVar9 + -4) = apsort;
      *(undefined4 *)(puVar9 + -8) = 4;
      *(int *)(puVar9 + -0xc) = local_c;
      *(undefined1 **)(puVar9 + -0x10) = &stack0xffffffcc + iVar3;
      *(undefined4 *)(puVar9 + -0x14) = 0x5a5fe4;
      qsort(*(void **)(puVar9 + -0x10),*(size_t *)(puVar9 + -0xc),*(size_t *)(puVar9 + -8),
            *(_PtFuncCompare **)(puVar9 + -4));
      local_8 = 0.0;
      if (0 < local_c) {
        fVar13 = (float10)0;
        do {
          iVar11 = *(int *)(&stack0xffffffcc + (int)local_8 * 4 + iVar3) - unaff_EDI >> 2;
          if ((float)param_5 < (float)*(double *)(iVar2 + 0x200)) {
            *(undefined4 *)(param_8 + iVar11 * 4) = 0;
            *(float *)(unaff_EDI + iVar11 * 4) = (float)fVar13;
          }
          else {
            *(undefined4 *)(puVar9 + -4) = 0x5a6040;
            _ftol2_sse();
            *(undefined4 *)(param_8 + iVar11 * 4) = extraout_EAX_02;
            param_5 = (float *)(float)(extraout_ST0 - fVar13);
            *(float *)(unaff_EDI + iVar11 * 4) = param_3[iVar11];
            fVar13 = extraout_ST1;
          }
          local_8 = (float)((int)local_8 + 1);
        } while ((int)local_8 < local_c);
        return (float)param_5;
      }
    }
  }
  return (float)param_5;
}
