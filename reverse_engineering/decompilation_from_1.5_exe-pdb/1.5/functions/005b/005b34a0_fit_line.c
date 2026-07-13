/*
 * Entry: 005b34a0
 * Name: fit_line
 * Namespace: Global
 * Signature: int fit_line(lsfit_acc * param_1, int param_2, int * param_3, int * param_4, vorbis_info_floor1 * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
fit_line(lsfit_acc *param_1,int param_2,int *param_3,int *param_4,vorbis_info_floor1 *param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  int in_EAX;
  int *piVar15;
  undefined4 extraout_EAX;
  int extraout_EAX_00;
  int in_ECX;
  int iVar16;
  int iVar17;
  double local_48;
  
  dVar7 = 0.0;
  iVar1 = param_1[in_EAX + -1].x1;
  local_48 = 0.0;
  iVar2 = param_1->x0;
  iVar16 = 0;
  dVar9 = dVar7;
  dVar10 = dVar7;
  dVar11 = dVar7;
  dVar12 = dVar7;
  if (3 < in_EAX) {
    iVar17 = (in_EAX - 4U >> 2) + 1;
    iVar16 = iVar17 * 4;
    piVar15 = &param_1->xb;
    do {
      iVar3 = piVar15[-1];
      iVar4 = piVar15[0xd];
      dVar7 = ((double)(piVar15[5] + iVar3) * (double)*(float *)(in_ECX + 0x454)) /
              (double)(iVar3 + 1) + 1.0;
      iVar5 = piVar15[0x1b];
      dVar14 = ((double)(piVar15[0x13] + iVar4) * (double)*(float *)(in_ECX + 0x454)) /
               (double)(iVar4 + 1) + 1.0;
      dVar8 = ((double)(piVar15[0x21] + iVar5) * (double)*(float *)(in_ECX + 0x454)) /
              (double)(iVar5 + 1) + 1.0;
      iVar6 = piVar15[0x29];
      iVar17 = iVar17 + -1;
      dVar13 = ((double)(piVar15[0x2f] + iVar6) * (double)*(float *)(in_ECX + 0x454)) /
               (double)(iVar6 + 1) + 1.0;
      dVar12 = (double)piVar15[0x24] * dVar13 + (double)piVar15[0x2a] +
               (double)piVar15[0x16] * dVar8 + (double)piVar15[0x1c] +
               (double)piVar15[8] * dVar14 + (double)piVar15[0xe] +
               (double)piVar15[-6] * dVar7 + (double)*piVar15 + dVar12;
      dVar11 = (double)piVar15[0x25] * dVar13 + (double)piVar15[0x2b] +
               (double)piVar15[0x17] * dVar8 + (double)piVar15[0x1d] +
               (double)piVar15[9] * dVar14 + (double)piVar15[0xf] +
               (double)piVar15[-5] * dVar7 + (double)piVar15[1] + dVar11;
      dVar9 = (double)piVar15[0x26] * dVar13 + (double)piVar15[0x2c] +
              (double)piVar15[0x18] * dVar8 + (double)piVar15[0x1e] +
              (double)piVar15[10] * dVar14 + (double)piVar15[0x10] +
              (double)piVar15[-4] * dVar7 + (double)piVar15[2] + dVar9;
      dVar10 = (double)piVar15[0x28] * dVar13 + (double)piVar15[0x2e] +
               (double)piVar15[0x1a] * dVar8 + (double)piVar15[0x20] +
               (double)piVar15[0xc] * dVar14 + (double)piVar15[0x12] +
               (double)piVar15[-2] * dVar7 + (double)piVar15[4] + dVar10;
      dVar7 = dVar13 * (double)iVar6 + (double)piVar15[0x2f] +
              dVar8 * (double)iVar5 + (double)piVar15[0x21] +
              dVar14 * (double)iVar4 + (double)piVar15[0x13] +
              dVar7 * (double)iVar3 + (double)piVar15[5] + local_48;
      piVar15 = piVar15 + 0x38;
      local_48 = dVar7;
    } while (iVar17 != 0);
  }
  if (iVar16 < in_EAX) {
    iVar17 = in_EAX - iVar16;
    piVar15 = &param_1[iVar16].xb;
    do {
      iVar16 = piVar15[-1];
      iVar17 = iVar17 + -1;
      dVar8 = ((double)(piVar15[5] + iVar16) * (double)*(float *)(in_ECX + 0x454)) /
              (double)(iVar16 + 1) + 1.0;
      dVar12 = dVar8 * (double)piVar15[-6] + (double)*piVar15 + dVar12;
      dVar11 = (double)piVar15[-5] * dVar8 + (double)piVar15[1] + dVar11;
      dVar9 = (double)piVar15[-4] * dVar8 + (double)piVar15[2] + dVar9;
      dVar10 = (double)piVar15[-2] * dVar8 + (double)piVar15[4] + dVar10;
      dVar7 = (double)iVar16 * dVar8 + (double)piVar15[5] + dVar7;
      piVar15 = piVar15 + 0xe;
    } while (iVar17 != 0);
  }
  iVar16 = *(int *)param_2;
  if (-1 < iVar16) {
    dVar12 = (double)iVar2 + dVar12;
    dVar11 = (double)iVar16 + dVar11;
    dVar9 = (double)(iVar2 * iVar2) + dVar9;
    dVar10 = (double)(iVar16 * iVar2) + dVar10;
    dVar7 = dVar7 + 1.0;
  }
  iVar16 = *param_3;
  if (-1 < iVar16) {
    dVar12 = (double)iVar1 + dVar12;
    dVar11 = (double)iVar16 + dVar11;
    dVar9 = (double)(iVar1 * iVar1) + dVar9;
    dVar10 = (double)(iVar16 * iVar1) + dVar10;
    dVar7 = dVar7 + 1.0;
  }
  dVar8 = dVar7 * dVar9 - dVar12 * dVar12;
  if (dVar8 <= 0.0) {
    *(undefined4 *)param_2 = 0;
    *param_3 = 0;
    return 1;
  }
  dVar9 = (dVar9 * dVar11 - dVar10 * dVar12) / dVar8;
  dVar8 = (dVar7 * dVar10 - dVar11 * dVar12) / dVar8;
  floor(dVar8 * (double)iVar2 + dVar9 + 0.5);
  _ftol2_sse();
  *(undefined4 *)param_2 = extraout_EAX;
  floor((double)iVar1 * dVar8 + dVar9 + 0.5);
  _ftol2_sse();
  *param_3 = extraout_EAX_00;
  if (0x3ff < *(int *)param_2) {
    *(undefined4 *)param_2 = 0x3ff;
  }
  if (0x3ff < *param_3) {
    *param_3 = 0x3ff;
  }
  if (*(int *)param_2 < 0) {
    *(undefined4 *)param_2 = 0;
  }
  if (*param_3 < 0) {
    *param_3 = 0;
  }
  return 0;
}
