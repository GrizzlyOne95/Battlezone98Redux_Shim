/*
 * Entry: 005a4310
 * Name: seed_curve
 * Namespace: Global
 * Signature: void seed_curve(float * param_1, float * * param_2, float param_3, int param_4, int param_5, int param_6, float param_7)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
seed_curve(float *param_1,float **param_2,float param_3,int param_4,int param_5,int param_6,
          float param_7)

{
  float fVar1;
  float fVar2;
  uint extraout_EAX;
  uint uVar3;
  int extraout_EAX_00;
  int extraout_EAX_01;
  int extraout_EAX_02;
  int iVar4;
  float *pfVar5;
  int iVar6;
  int unaff_EDI;
  float10 extraout_ST0;
  
  _ftol2_sse();
  uVar3 = extraout_EAX & ((int)extraout_EAX < 1) - 1;
  if (6 < (int)uVar3) {
    uVar3 = 7;
  }
  fVar2 = param_1[uVar3];
  _ftol2_sse();
  _ftol2_sse();
  _ftol2_sse();
  if (extraout_EAX_02 < extraout_EAX_00) {
    iVar4 = extraout_EAX_02;
    iVar6 = extraout_EAX_01;
    if (3 < extraout_EAX_00 - extraout_EAX_02) {
      pfVar5 = (float *)((int)fVar2 + 0x10 + extraout_EAX_02 * 4);
      do {
        if ((0 < iVar6) &&
           (*(float *)(unaff_EDI + iVar6 * 4) < (float)((float10)pfVar5[-2] + extraout_ST0))) {
          *(float *)(unaff_EDI + iVar6 * 4) = (float)((float10)pfVar5[-2] + extraout_ST0);
        }
        iVar6 = iVar6 + param_5;
        if (param_4 <= iVar6) {
          return;
        }
        if ((0 < iVar6) &&
           (*(float *)(unaff_EDI + iVar6 * 4) < (float)((float10)pfVar5[-1] + extraout_ST0))) {
          *(float *)(unaff_EDI + iVar6 * 4) = (float)((float10)pfVar5[-1] + extraout_ST0);
        }
        iVar6 = iVar6 + param_5;
        if (param_4 <= iVar6) {
          return;
        }
        if ((0 < iVar6) &&
           (*(float *)(unaff_EDI + iVar6 * 4) < (float)((float10)*pfVar5 + extraout_ST0))) {
          *(float *)(unaff_EDI + iVar6 * 4) = (float)((float10)*pfVar5 + extraout_ST0);
        }
        iVar6 = iVar6 + param_5;
        if (param_4 <= iVar6) {
          return;
        }
        if ((0 < iVar6) &&
           (*(float *)(unaff_EDI + iVar6 * 4) < (float)((float10)pfVar5[1] + extraout_ST0))) {
          *(float *)(unaff_EDI + iVar6 * 4) = (float)((float10)pfVar5[1] + extraout_ST0);
        }
        iVar6 = iVar6 + param_5;
        if (param_4 <= iVar6) {
          return;
        }
        iVar4 = iVar4 + 4;
        pfVar5 = pfVar5 + 4;
      } while (iVar4 < extraout_EAX_00 + -3);
    }
    for (; iVar4 < extraout_EAX_00; iVar4 = iVar4 + 1) {
      if ((0 < iVar6) &&
         (fVar1 = (float)((float10)*(float *)((int)fVar2 + 8 + iVar4 * 4) + extraout_ST0),
         *(float *)(unaff_EDI + iVar6 * 4) < fVar1)) {
        *(float *)(unaff_EDI + iVar6 * 4) = fVar1;
      }
      iVar6 = iVar6 + param_5;
      if (param_4 <= iVar6) {
        return;
      }
    }
  }
  return;
}
