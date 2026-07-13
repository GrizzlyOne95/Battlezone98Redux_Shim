/*
 * Entry: 005affc0
 * Name: _vorbis_apply_window
 * Namespace: Global
 * Signature: void _vorbis_apply_window(float * param_1, int * param_2, long * param_3, int param_4, int param_5, int param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
_vorbis_apply_window(float *param_1,int *param_2,long *param_3,int param_4,int param_5,int param_6)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  uint uVar8;
  int iVar9;
  float *pfVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  
  uVar3 = -(uint)(param_5 != 0) & param_4;
  uVar8 = -(uint)(param_5 != 0) & param_6;
  pfVar7 = vwin[param_2[uVar8]];
  pfVar6 = vwin[param_2[uVar3]];
  iVar2 = param_3[uVar3];
  iVar11 = param_3[param_5];
  iVar4 = param_3[uVar8];
  iVar9 = (int)(iVar11 + (iVar11 >> 0x1f & 3U)) >> 2;
  iVar13 = iVar9 - ((int)(iVar2 + (iVar2 >> 0x1f & 3U)) >> 2);
  iVar14 = iVar4 / 2;
  iVar9 = (iVar11 / 2 - ((int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2)) + iVar9;
  iVar12 = iVar2 / 2 + iVar13;
  iVar2 = iVar14 + iVar9;
  iVar4 = 0;
  iVar5 = iVar13;
  pfVar10 = param_1;
  if (0 < iVar13) {
    for (; iVar4 = iVar13, iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar10 = 0.0;
      pfVar10 = pfVar10 + 1;
    }
  }
  param_2 = (int *)0x0;
  if (iVar4 < iVar12) {
    if (3 < iVar12 - iVar4) {
      iVar13 = ((iVar12 - iVar4) - 4U >> 2) + 1;
      iVar5 = iVar4 + 2;
      param_2 = (int *)(iVar13 * 4);
      iVar4 = iVar4 + (int)param_2;
      pfVar10 = param_1 + iVar5;
      pfVar15 = pfVar6 + 2;
      do {
        iVar13 = iVar13 + -1;
        pfVar10[-2] = pfVar15[-2] * pfVar10[-2];
        pfVar10[-1] = pfVar15[-1] * pfVar10[-1];
        *pfVar10 = *pfVar10 * *pfVar15;
        pfVar10[1] = pfVar15[1] * pfVar10[1];
        pfVar10 = pfVar10 + 4;
        pfVar15 = pfVar15 + 4;
      } while (iVar13 != 0);
    }
    if (iVar4 < iVar12) {
      pfVar6 = pfVar6 + (int)param_2;
      do {
        iVar5 = iVar4 + 1;
        fVar1 = *pfVar6;
        pfVar6 = pfVar6 + 1;
        param_1[iVar4] = param_1[iVar4] * fVar1;
        iVar4 = iVar5;
      } while (iVar5 < iVar12);
    }
  }
  iVar4 = iVar14 + -1;
  if (iVar9 < iVar2) {
    if (3 < iVar2 - iVar9) {
      iVar12 = ((iVar2 - iVar9) - 4U >> 2) + 1;
      iVar5 = iVar9 + 2;
      iVar9 = iVar9 + iVar12 * 4;
      iVar4 = iVar4 + iVar12 * -4;
      pfVar6 = param_1 + iVar5;
      pfVar10 = pfVar7 + iVar14 + -3;
      do {
        iVar12 = iVar12 + -1;
        pfVar6[-2] = pfVar10[2] * pfVar6[-2];
        pfVar6[-1] = pfVar10[1] * pfVar6[-1];
        *pfVar6 = *pfVar6 * *pfVar10;
        pfVar6[1] = pfVar10[-1] * pfVar6[1];
        pfVar6 = pfVar6 + 4;
        pfVar10 = pfVar10 + -4;
      } while (iVar12 != 0);
    }
    if (iVar9 < iVar2) {
      pfVar7 = pfVar7 + iVar4;
      iVar4 = iVar9;
      do {
        fVar1 = *pfVar7;
        iVar9 = iVar4 + 1;
        pfVar7 = pfVar7 + -1;
        param_1[iVar4] = fVar1 * param_1[iVar4];
        iVar4 = iVar9;
      } while (iVar9 < iVar2);
    }
  }
  if (iVar9 < iVar11) {
    pfVar6 = param_1 + iVar9;
    for (iVar11 = iVar11 - iVar9; iVar11 != 0; iVar11 = iVar11 + -1) {
      *pfVar6 = 0.0;
      pfVar6 = pfVar6 + 1;
    }
  }
  return;
}
