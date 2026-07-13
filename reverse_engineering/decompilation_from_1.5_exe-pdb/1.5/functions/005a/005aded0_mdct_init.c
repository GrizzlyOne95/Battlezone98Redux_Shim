/*
 * Entry: 005aded0
 * Name: mdct_init
 * Namespace: Global
 * Signature: void mdct_init(mdct_lookup * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl mdct_init(mdct_lookup *param_1,int param_2)

{
  int *piVar1;
  float *pfVar2;
  int extraout_EAX;
  uint uVar3;
  byte bVar4;
  uint uVar5;
  uint uVar6;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  float10 fVar11;
  float10 fVar12;
  
  iVar10 = (int)(param_2 + (param_2 >> 0x1f & 3U)) >> 2;
  piVar1 = malloc(iVar10 * 4);
  pfVar2 = malloc((iVar10 + param_2) * 4);
  fVar11 = (float10)__CIlog();
  fVar12 = (float10)__CIlog();
  floor((double)((float10)(double)fVar11 / fVar12 + (float10)0.5));
  _ftol2_sse();
  param_1->bitrev = piVar1;
  iVar8 = 0;
  param_1->log2n = extraout_EAX;
  param_1->n = param_2;
  param_1->trig = pfVar2;
  if (0 < iVar10) {
    pfVar7 = pfVar2 + (param_2 >> 1);
    do {
      fVar11 = (float10)__CIcos();
      pfVar2[iVar8 * 2] = (float)fVar11;
      fVar11 = (float10)__CIsin();
      pfVar2[iVar8 * 2 + 1] = (float)-fVar11;
      fVar11 = (float10)__CIcos();
      *pfVar7 = (float)fVar11;
      fVar11 = (float10)__CIsin();
      pfVar7[1] = (float)fVar11;
      iVar8 = iVar8 + 1;
      pfVar7 = pfVar7 + 2;
    } while (iVar8 < iVar10);
  }
  iVar8 = (int)(param_2 + (param_2 >> 0x1f & 7U)) >> 3;
  if (0 < iVar8) {
    pfVar2 = pfVar2 + param_2;
    iVar10 = iVar8;
    do {
      fVar11 = (float10)__CIcos();
      *pfVar2 = (float)(fVar11 * (float10)0.5);
      fVar11 = (float10)__CIsin();
      iVar10 = iVar10 + -1;
      pfVar2[1] = (float)(fVar11 * (float10)-0.5);
      pfVar2 = pfVar2 + 2;
    } while (iVar10 != 0);
  }
  uVar9 = 1 << ((char)extraout_EAX - 2U & 0x1f);
  uVar5 = 0;
  if (0 < iVar8) {
    do {
      uVar6 = 0;
      bVar4 = 0;
      if (uVar9 != 0) {
        uVar6 = 0;
        uVar3 = uVar9;
        do {
          if ((uVar5 & uVar3) != 0) {
            uVar6 = uVar6 | 1 << (bVar4 & 0x1f);
          }
          bVar4 = bVar4 + 1;
          uVar3 = (int)uVar9 >> (bVar4 & 0x1f);
        } while (uVar3 != 0);
      }
      piVar1[uVar5 * 2] = (~uVar6 & (1 << ((char)extraout_EAX - 1U & 0x1f)) - 1U) - 1;
      piVar1[uVar5 * 2 + 1] = uVar6;
      uVar5 = uVar5 + 1;
    } while ((int)uVar5 < iVar8);
  }
  param_1->scale = 4.0 / (float)param_2;
  return;
}
