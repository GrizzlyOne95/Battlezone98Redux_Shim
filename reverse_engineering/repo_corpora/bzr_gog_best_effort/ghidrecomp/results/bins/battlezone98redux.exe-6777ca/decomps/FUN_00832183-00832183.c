
void FUN_00832183(int param_1,int param_2)

{
  int *piVar1;
  bool bVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  double *pdVar6;
  uint uVar7;
  double *pdVar8;
  int iVar9;
  double *pdVar10;
  uint *puVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  char *pcVar15;
  undefined4 local_44 [2];
  undefined4 local_3c;
  undefined4 local_34 [2];
  undefined4 local_2c;
  double *local_24;
  undefined4 *local_20;
  double *local_1c;
  int local_18;
  double *local_14;
  int local_10;
  uint *local_c;
  int local_8;
  
LAB_0083218e:
  local_8 = *(int *)(param_1 + 0xc);
  local_c = *(uint **)(param_1 + 0x18);
  local_18 = **(int **)(*(int *)(param_1 + 0x14) + 4);
  local_10 = *(int *)(*(int *)(local_18 + 0x10) + 8);
switchD_00832209_default:
  local_14 = (double *)*local_c;
  local_c = local_c + 1;
  if ((*(byte *)(param_1 + 0x38) & 0xc) != 0) {
    piVar1 = (int *)(param_1 + 0x40);
    *piVar1 = *piVar1 + -1;
    if ((*piVar1 == 0) || ((*(byte *)(param_1 + 0x38) & 4) != 0)) {
      FUN_008333ea(param_1,local_c);
      if (*(char *)(param_1 + 6) == '\x01') {
        *(uint **)(param_1 + 0x18) = local_c + -1;
        return;
      }
      local_8 = *(int *)(param_1 + 0xc);
    }
  }
  local_20 = (undefined4 *)((uint)local_14 >> 6 & 0xff);
  local_1c = (double *)((int)local_20 * 0x10);
  pdVar10 = (double *)(local_8 + (int)local_1c);
  switch((uint)local_14 & 0x3f) {
  case 0:
    puVar4 = (undefined4 *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    goto LAB_00832219;
  case 1:
    puVar4 = (undefined4 *)(((uint)local_14 >> 0xe) * 0x10 + local_10);
LAB_00832219:
    *(undefined4 *)pdVar10 = *puVar4;
    *(undefined4 *)((int)pdVar10 + 4) = puVar4[1];
    uVar5 = puVar4[2];
LAB_00832226:
    *(undefined4 *)(pdVar10 + 1) = uVar5;
    goto switchD_00832209_default;
  case 2:
    *(undefined4 *)(pdVar10 + 1) = 1;
    *(uint *)pdVar10 = (uint)local_14 >> 0x17;
    if (((uint)local_14 & 0x7fc000) != 0) goto LAB_00832acc;
    goto switchD_00832209_default;
  case 3:
    pdVar8 = (double *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    do {
      *(undefined4 *)(pdVar8 + 1) = 0;
      pdVar8 = pdVar8 + -2;
    } while (pdVar10 <= pdVar8);
    goto switchD_00832209_default;
  case 4:
    puVar4 = *(undefined4 **)(*(int *)(local_18 + 0x14 + ((uint)local_14 >> 0x17) * 4) + 8);
    *(undefined4 *)pdVar10 = *puVar4;
    *(undefined4 *)((int)pdVar10 + 4) = puVar4[1];
    uVar5 = puVar4[2];
    goto LAB_0083228b;
  case 5:
    iVar3 = ((uint)local_14 >> 0xe) * 0x10 + local_10;
    local_34[0] = *(undefined4 *)(local_18 + 0xc);
    puVar4 = local_34;
    local_2c = 5;
    *(uint **)(param_1 + 0x18) = local_c;
    goto LAB_00832459;
  case 6:
    uVar7 = (uint)local_14 >> 0xe;
    *(uint **)(param_1 + 0x18) = local_c;
    iVar3 = (uVar7 & 0x1ff) * 0x10 + local_8;
    if ((uVar7 & 0x100) != 0) {
      iVar3 = (uVar7 & 0xff) * 0x10 + local_10;
    }
    puVar4 = (undefined4 *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    goto LAB_00832459;
  case 7:
    iVar3 = ((uint)local_14 >> 0xe) * 0x10 + local_10;
    local_44[0] = *(undefined4 *)(local_18 + 0xc);
    puVar4 = local_44;
    local_3c = 5;
    *(uint **)(param_1 + 0x18) = local_c;
    goto LAB_008323be;
  case 8:
    iVar3 = *(int *)(local_18 + 0x14 + ((uint)local_14 >> 0x17) * 4);
    puVar4 = *(undefined4 **)(iVar3 + 8);
    *puVar4 = *(undefined4 *)pdVar10;
    puVar4[1] = *(undefined4 *)((int)pdVar10 + 4);
    puVar4[2] = *(undefined4 *)(pdVar10 + 1);
    if (((3 < *(int *)(pdVar10 + 1)) && ((*(byte *)(*(int *)pdVar10 + 5) & 3) != 0)) &&
       ((*(byte *)(iVar3 + 5) & 4) != 0)) {
      FUN_0083001b(param_1,iVar3,*(int *)pdVar10);
    }
    goto switchD_00832209_default;
  case 9:
    uVar7 = (uint)local_14 >> 0xe;
    *(uint **)(param_1 + 0x18) = local_c;
    local_14 = (double *)((uint)local_14 >> 0x17);
    pdVar10 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar10 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    iVar3 = (int)local_14 * 0x10 + local_8;
    if (((uint)local_14 & 0x100) != 0) {
      iVar3 = ((uint)local_14 & 0xff) * 0x10 + local_10;
    }
    puVar4 = (undefined4 *)((int)local_1c + local_8);
LAB_008323be:
    FUN_0083321b(param_1,puVar4,iVar3,pdVar10);
    break;
  case 10:
    uVar5 = FUN_0082e863((uint)local_14 >> 0xe & 0x1ff);
    uVar5 = FUN_0082e863((uint)local_14 >> 0x17,uVar5);
    uVar5 = FUN_00830f66(param_1,uVar5);
    *(undefined4 *)((int)local_1c + local_8) = uVar5;
    *(undefined4 *)((int)local_1c + local_8 + 8) = 5;
    *(uint **)(param_1 + 0x18) = local_c;
    goto LAB_00832e67;
  case 0xb:
    puVar4 = (undefined4 *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    *(undefined4 *)(pdVar10 + 2) = *puVar4;
    *(undefined4 *)((int)pdVar10 + 0x14) = puVar4[1];
    *(undefined4 *)(pdVar10 + 3) = puVar4[2];
    local_14 = (double *)((uint)local_14 >> 0xe);
    *(uint **)(param_1 + 0x18) = local_c;
    iVar3 = ((uint)local_14 & 0x1ff) * 0x10 + local_8;
    if (((uint)local_14 & 0x100) != 0) {
      iVar3 = ((uint)local_14 & 0xff) * 0x10 + local_10;
    }
LAB_00832459:
    FUN_008330e3(param_1,puVar4,iVar3,pdVar10);
    break;
  case 0xc:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    if ((*(int *)(pdVar6 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      uVar5 = 5;
      local_14 = pdVar6;
      goto LAB_0083279c;
    }
    dVar12 = *pdVar8 + *pdVar6;
LAB_008324d1:
    uVar5 = 3;
    *pdVar10 = dVar12;
    goto LAB_0083228b;
  case 0xd:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    if ((*(int *)(pdVar6 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      dVar12 = *pdVar6 - *pdVar8;
      goto LAB_008324d1;
    }
    uVar5 = 6;
    local_14 = pdVar6;
    goto LAB_0083279c;
  case 0xe:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    if ((*(int *)(pdVar6 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      dVar12 = *pdVar8 * *pdVar6;
      goto LAB_008324d1;
    }
    uVar5 = 7;
    local_14 = pdVar6;
    goto LAB_0083279c;
  case 0xf:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    if ((*(int *)(pdVar6 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      dVar12 = *pdVar6 / *pdVar8;
      goto LAB_008324d1;
    }
    uVar5 = 8;
    local_14 = pdVar6;
    goto LAB_0083279c;
  case 0x10:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar5 = 3;
    if ((*(int *)(pdVar6 + 1) != 3) || (*(int *)(pdVar8 + 1) != 3)) {
      uVar5 = 9;
      local_14 = pdVar6;
      goto LAB_0083279c;
    }
    dVar14 = *pdVar6 / *pdVar8;
    dVar13 = (double)((ulonglong)dVar14 & 0x8000000000000000);
    dVar12 = (double)(-(ulonglong)
                       ((double)((ulonglong)dVar14 ^ (ulonglong)dVar13) < 4503599627370496.0) &
                      0x4330000000000000 | (ulonglong)dVar13);
    dVar12 = (dVar14 + dVar12) - dVar12;
    *pdVar10 = *pdVar6 - (dVar12 - (double)(-(ulonglong)(dVar13 < dVar12 - dVar14) &
                                           0x3ff0000000000000)) * *pdVar8;
LAB_0083228b:
    *(undefined4 *)(pdVar10 + 1) = uVar5;
    goto switchD_00832209_default;
  case 0x11:
    uVar7 = (uint)local_14 >> 0x17;
    pdVar6 = (double *)(uVar7 * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar6 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    uVar7 = (uint)local_14 >> 0xe;
    pdVar8 = (double *)((uVar7 & 0x1ff) * 0x10 + local_8);
    if ((uVar7 & 0x100) != 0) {
      pdVar8 = (double *)((uVar7 & 0xff) * 0x10 + local_10);
    }
    local_14 = pdVar6;
    if ((*(int *)(pdVar6 + 1) == 3) && (*(int *)(pdVar8 + 1) == 3)) {
      dVar12 = *pdVar6;
      __libm_sse2_pow();
LAB_0083278a:
      *pdVar10 = dVar12;
      *(undefined4 *)(pdVar10 + 1) = 3;
      goto switchD_00832209_default;
    }
    uVar5 = 10;
LAB_0083279c:
    *(uint **)(param_1 + 0x18) = local_c;
    pdVar6 = local_14;
LAB_008327d3:
    FUN_00831a97(param_1,pdVar10,pdVar6,pdVar8,uVar5);
    break;
  case 0x12:
    pdVar8 = (double *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    uVar5 = 3;
    if (*(int *)(pdVar8 + 1) != 3) {
      uVar5 = 0xb;
      *(uint **)(param_1 + 0x18) = local_c;
      pdVar6 = pdVar8;
      goto LAB_008327d3;
    }
    *pdVar10 = -*pdVar8;
    goto LAB_00832226;
  case 0x13:
    uVar7 = (uint)local_14 >> 0x17;
    if ((*(int *)(local_8 + 8 + uVar7 * 0x10) == 0) ||
       ((*(int *)(local_8 + 8 + uVar7 * 0x10) == 1 && (*(int *)(local_8 + uVar7 * 0x10) == 0)))) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
    *(undefined4 *)pdVar10 = uVar5;
    *(undefined4 *)(pdVar10 + 1) = 1;
    goto switchD_00832209_default;
  case 0x14:
    local_14 = (double *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    if (*(int *)((int)local_14 + 8) == 4) {
      iVar3 = *(int *)(*(int *)local_14 + 0xc);
      *(undefined4 *)(pdVar10 + 1) = 3;
      *pdVar10 = (double)iVar3 + (double)(&DAT_008a2fd0)[-(iVar3 >> 0x1f)];
      goto switchD_00832209_default;
    }
    if (*(int *)((int)local_14 + 8) == 5) {
      iVar3 = FUN_00830e70(*(int *)local_14);
      dVar12 = (double)iVar3;
      goto LAB_0083278a;
    }
    *(uint **)(param_1 + 0x18) = local_c;
    iVar3 = FUN_00831d18(param_1,local_14,&DAT_0086ed18,pdVar10,0xc);
    if (iVar3 == 0) {
      FUN_0082dfec(param_1,local_14,"get length of");
    }
    break;
  case 0x15:
    *(uint **)(param_1 + 0x18) = local_c;
    uVar7 = (uint)local_14 >> 0xe & 0x1ff;
    local_24 = (double *)((uint)local_14 >> 0x17);
    FUN_00831f3a(param_1,(uVar7 - (int)local_24) + 1,uVar7);
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      FUN_00830222(param_1);
    }
    local_8 = *(int *)(param_1 + 0xc);
    *(undefined4 *)((int)local_1c + local_8) = *(undefined4 *)(local_8 + (int)local_24 * 0x10);
    *(undefined4 *)((int)local_1c + local_8 + 4) =
         *(undefined4 *)(local_8 + 4 + (int)local_24 * 0x10);
    *(undefined4 *)((int)local_1c + local_8 + 8) =
         *(undefined4 *)(local_8 + 8 + (int)local_24 * 0x10);
    goto switchD_00832209_default;
  case 0x16:
    local_c = local_c + ((uint)local_14 >> 0xe);
    goto LAB_00832c44;
  case 0x17:
    uVar7 = (uint)local_14 >> 0x17;
    iVar3 = uVar7 * 0x10 + local_8;
    if ((uVar7 & 0x100) != 0) {
      iVar3 = (uVar7 & 0xff) * 0x10 + local_10;
    }
    uVar7 = (uint)local_14 >> 0xe;
    iVar9 = (uVar7 & 0x1ff) * 0x10 + local_8;
    if ((uVar7 & 0x100) != 0) {
      iVar9 = (uVar7 & 0xff) * 0x10 + local_10;
    }
    *(uint **)(param_1 + 0x18) = local_c;
    if ((*(int *)(iVar3 + 8) == *(int *)(iVar9 + 8)) &&
       (local_14 = (double *)iVar3, iVar3 = FUN_008320e0(param_1,iVar3,iVar9), iVar3 != 0)) {
      puVar4 = (undefined4 *)0x1;
    }
    else {
      puVar4 = (undefined4 *)0x0;
    }
    goto LAB_00832a29;
  case 0x18:
    uVar7 = (uint)local_14 >> 0xe;
    *(uint **)(param_1 + 0x18) = local_c;
    local_14 = (double *)((uint)local_14 >> 0x17);
    iVar3 = (uVar7 & 0x1ff) * 0x10 + local_8;
    if ((uVar7 & 0x100) != 0) {
      iVar3 = (uVar7 & 0xff) * 0x10 + local_10;
    }
    iVar9 = (int)local_14 * 0x10 + local_8;
    if (((uint)local_14 & 0x100) != 0) {
      iVar9 = ((uint)local_14 & 0xff) * 0x10 + local_10;
    }
    puVar4 = (undefined4 *)FUN_008331b4(param_1,iVar9,iVar3);
    goto LAB_00832a29;
  case 0x19:
    uVar7 = (uint)local_14 >> 0xe;
    *(uint **)(param_1 + 0x18) = local_c;
    local_14 = (double *)((uint)local_14 >> 0x17);
    iVar3 = (uVar7 & 0x1ff) * 0x10 + local_8;
    if ((uVar7 & 0x100) != 0) {
      iVar3 = (uVar7 & 0xff) * 0x10 + local_10;
    }
    iVar9 = (int)local_14 * 0x10 + local_8;
    if (((uint)local_14 & 0x100) != 0) {
      iVar9 = ((uint)local_14 & 0xff) * 0x10 + local_10;
    }
    puVar4 = (undefined4 *)FUN_00831eb4(param_1,iVar9,iVar3);
LAB_00832a29:
    if (puVar4 == local_20) {
      local_c = local_c + ((*local_c >> 0xe) - 0x1ffff);
    }
    local_8 = *(int *)(param_1 + 0xc);
LAB_00832ced:
    local_c = local_c + 1;
    goto switchD_00832209_default;
  case 0x1a:
    if ((*(int *)(pdVar10 + 1) == 0) || ((*(int *)(pdVar10 + 1) == 1 && (*(int *)pdVar10 == 0)))) {
      uVar7 = 1;
    }
    else {
      uVar7 = 0;
    }
    if (uVar7 != ((uint)local_14 >> 0xe & 0x1ff)) {
LAB_00832abe:
      local_c = local_c + ((*local_c >> 0xe) - 0x1ffff);
    }
    goto LAB_00832acc;
  case 0x1b:
    local_24 = (double *)(((uint)local_14 >> 0x17) * 0x10 + local_8);
    if ((*(int *)(local_24 + 1) == 0) || ((*(int *)(local_24 + 1) == 1 && (*(int *)local_24 == 0))))
    {
      local_20 = (undefined4 *)0x1;
    }
    else {
      local_20 = (undefined4 *)0x0;
    }
    if (local_20 != (undefined4 *)((uint)local_14 >> 0xe & 0x1ff)) {
      *(undefined4 *)pdVar10 = *(undefined4 *)local_24;
      *(undefined4 *)((int)pdVar10 + 4) = *(undefined4 *)((int)local_24 + 4);
      *(undefined4 *)(pdVar10 + 1) = *(undefined4 *)(local_24 + 1);
      goto LAB_00832abe;
    }
LAB_00832acc:
    local_c = local_c + 1;
    goto switchD_00832209_default;
  case 0x1c:
    uVar7 = (uint)local_14 >> 0x17;
    local_14 = (double *)(((uint)local_14 >> 0xe & 0x1ff) - 1);
    if (uVar7 != 0) {
      *(double **)(param_1 + 8) = pdVar10 + uVar7 * 2;
    }
    *(uint **)(param_1 + 0x18) = local_c;
    iVar3 = FUN_0082f2d3(param_1,pdVar10,local_14);
    if (iVar3 == 0) {
      param_2 = param_2 + 1;
      goto LAB_0083218e;
    }
    if (iVar3 != 1) {
      return;
    }
    if (-1 < (int)local_14) {
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 8);
    }
    break;
  case 0x1d:
    if ((uint)local_14 >> 0x17 != 0) {
      *(double **)(param_1 + 8) = pdVar10 + ((uint)local_14 >> 0x17) * 2;
    }
    *(uint **)(param_1 + 0x18) = local_c;
    iVar3 = FUN_0082f2d3(param_1,pdVar10,0xffffffff);
    if (iVar3 == 0) {
      piVar1 = *(int **)(param_1 + 0x14);
      pdVar10 = (double *)(piVar1 + -6);
      local_1c = (double *)piVar1[-5];
      local_20 = (undefined4 *)piVar1[1];
      local_24 = pdVar10;
      if (*(int *)(param_1 + 0x68) != 0) {
        FUN_0082f92f(param_1,*(undefined4 *)pdVar10);
      }
      iVar9 = 0;
      iVar3 = piVar1[-5] + (*piVar1 - (int)local_20 & 0xfffffff0U);
      *(int *)pdVar10 = iVar3;
      *(int *)(param_1 + 0xc) = iVar3;
      if (local_20 < *(undefined4 **)(param_1 + 8)) {
        iVar3 = 0;
        puVar4 = local_20;
        do {
          iVar9 = iVar9 + 1;
          *(undefined4 *)(iVar3 + (int)local_1c) = *puVar4;
          *(undefined4 *)(iVar3 + 4 + (int)local_1c) = puVar4[1];
          *(undefined4 *)(iVar3 + 8 + (int)local_1c) = puVar4[2];
          iVar3 = iVar9 * 0x10;
          puVar4 = local_20 + iVar9 * 4;
          pdVar10 = local_24;
        } while (puVar4 < *(undefined4 **)(param_1 + 8));
      }
      *(double **)(param_1 + 8) = local_1c + iVar9 * 2;
      *(double **)(pdVar10 + 1) = local_1c + iVar9 * 2;
      uVar5 = *(undefined4 *)(param_1 + 0x18);
      *(int *)((int)pdVar10 + 0x14) = *(int *)((int)pdVar10 + 0x14) + 1;
      *(undefined4 *)((int)pdVar10 + 0xc) = uVar5;
      *(int *)(param_1 + 0x14) = *(int *)(param_1 + 0x14) + -0x18;
      goto LAB_0083218e;
    }
    if (iVar3 != 1) {
      return;
    }
    break;
  case 0x1e:
    goto switchD_00832209_caseD_1e;
  case 0x1f:
    dVar12 = pdVar10[4] + *pdVar10;
    bVar2 = pdVar10[2] <= dVar12;
    if (0.0 < pdVar10[4]) {
      bVar2 = dVar12 <= pdVar10[2];
    }
    if (bVar2) {
      *pdVar10 = dVar12;
      *(undefined4 *)(pdVar10 + 1) = 3;
      local_c = local_c + (((uint)local_14 >> 0xe) - 0x1ffff);
      pdVar10[6] = dVar12;
      *(undefined4 *)(pdVar10 + 7) = 3;
    }
    goto switchD_00832209_default;
  case 0x20:
    local_1c = pdVar10 + 4;
    *(uint **)(param_1 + 0x18) = local_c;
    if ((*(int *)(pdVar10 + 1) == 3) || (iVar3 = FUN_0083332e(pdVar10,pdVar10), iVar3 != 0)) {
      if ((*(int *)(pdVar10 + 3) != 3) &&
         (iVar3 = FUN_0083332e(pdVar10 + 2,pdVar10 + 2), iVar3 == 0)) {
        pcVar15 = "\'for\' limit must be a number";
        goto LAB_00832c1a;
      }
      if ((*(int *)(local_1c + 1) != 3) &&
         (local_1c = (double *)FUN_0083332e(local_1c,local_1c), local_1c == (double *)0x0)) {
        pcVar15 = "\'for\' step must be a number";
        goto LAB_00832c1a;
      }
    }
    else {
      pcVar15 = "\'for\' initial value must be a number";
LAB_00832c1a:
      FUN_0082df5b(param_1,pcVar15);
    }
    dVar12 = *local_1c;
    *(undefined4 *)(pdVar10 + 1) = 3;
    *pdVar10 = *pdVar10 - dVar12;
    local_c = local_c + ((uint)local_14 >> 0xe);
LAB_00832c44:
    local_c = local_c + -0x1ffff;
    goto switchD_00832209_default;
  case 0x21:
    *(undefined4 *)(pdVar10 + 10) = *(undefined4 *)(pdVar10 + 4);
    *(undefined4 *)((int)pdVar10 + 0x54) = *(undefined4 *)((int)pdVar10 + 0x24);
    *(undefined4 *)(pdVar10 + 0xb) = *(undefined4 *)(pdVar10 + 5);
    *(undefined4 *)(pdVar10 + 8) = *(undefined4 *)(pdVar10 + 2);
    *(undefined4 *)((int)pdVar10 + 0x44) = *(undefined4 *)((int)pdVar10 + 0x14);
    *(undefined4 *)(pdVar10 + 9) = *(undefined4 *)(pdVar10 + 3);
    *(undefined4 *)(pdVar10 + 6) = *(undefined4 *)pdVar10;
    *(undefined4 *)((int)pdVar10 + 0x34) = *(undefined4 *)((int)pdVar10 + 4);
    *(undefined4 *)(pdVar10 + 7) = *(undefined4 *)(pdVar10 + 1);
    *(double **)(param_1 + 8) = pdVar10 + 0xc;
    *(uint **)(param_1 + 0x18) = local_c;
    FUN_0082f062(param_1,pdVar10 + 6,(uint)local_14 >> 0xe & 0x1ff);
    local_8 = *(int *)(param_1 + 0xc);
    puVar4 = (undefined4 *)(((int)local_20 + 3) * 0x10 + local_8);
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 8);
    if (puVar4[2] != 0) {
      puVar4[-4] = *puVar4;
      puVar4[-3] = puVar4[1];
      puVar4[-2] = puVar4[2];
      local_c = local_c + ((*local_c >> 0xe) - 0x1ffff);
    }
    goto LAB_00832ced;
  case 0x22:
    local_1c = (double *)((uint)local_14 >> 0x17);
    uVar7 = (uint)local_14 >> 0xe & 0x1ff;
    if (local_1c == (double *)0x0) {
      local_1c = (double *)((*(int *)(param_1 + 8) - (int)pdVar10 >> 4) + -1);
      *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 8);
    }
    if (uVar7 == 0) {
      uVar7 = *local_c;
      local_c = local_c + 1;
    }
    if (*(int *)(pdVar10 + 1) == 5) {
      local_14 = *(double **)pdVar10;
      local_20 = (undefined4 *)((int)local_1c + uVar7 * 0x32 + -0x32);
      if (*(int *)((int)local_14 + 0x1c) < (int)local_20) {
        FUN_0083108b(param_1,local_14,local_20);
      }
      if (0 < (int)local_1c) {
        pdVar10 = pdVar10 + (int)local_1c * 2;
        local_24 = pdVar10;
        do {
          puVar4 = (undefined4 *)FUN_00831114(param_1,local_14,local_20);
          local_20 = (undefined4 *)((int)local_20 + -1);
          *puVar4 = *(undefined4 *)pdVar10;
          puVar4[1] = *(undefined4 *)((int)pdVar10 + 4);
          puVar4[2] = *(undefined4 *)(pdVar10 + 1);
          if (((3 < *(int *)(pdVar10 + 1)) && ((*(byte *)(*(int *)pdVar10 + 5) & 3) != 0)) &&
             (((ulonglong)*local_14 & 0x40000000000) != 0)) {
            FUN_00830000(param_1,local_14);
          }
          pdVar10 = pdVar10 + -2;
          local_1c = (double *)((int)local_1c + -1);
        } while (0 < (int)local_1c);
      }
    }
    goto switchD_00832209_default;
  case 0x23:
    FUN_0082f92f(param_1,pdVar10);
    goto switchD_00832209_default;
  case 0x24:
    iVar3 = *(int *)(*(int *)(*(int *)(local_18 + 0x10) + 0x10) + ((uint)local_14 >> 0xe) * 4);
    local_20 = (undefined4 *)(uint)*(byte *)(iVar3 + 0x48);
    local_24 = (double *)FUN_0082fba1(param_1,local_20,*(undefined4 *)(local_18 + 0xc));
    *(int *)(local_24 + 2) = iVar3;
    if (0 < (int)local_20) {
      local_14 = (double *)((int)local_24 + 0x14);
      puVar11 = local_c;
      do {
        uVar7 = *puVar11 >> 0x17;
        if (((byte)*puVar11 & 0x3f) == 4) {
          uVar5 = *(undefined4 *)(local_18 + 0x14 + uVar7 * 4);
        }
        else {
          uVar5 = FUN_0082f9ac(param_1,uVar7 * 0x10 + local_8);
        }
        *(undefined4 *)local_14 = uVar5;
        puVar11 = puVar11 + 1;
        local_14 = (double *)((int)local_14 + 4);
        local_20 = (undefined4 *)((int)local_20 + -1);
      } while (local_20 != (undefined4 *)0x0);
      local_20 = (undefined4 *)0x0;
      local_c = puVar11;
    }
    *(double **)((int)local_1c + local_8) = local_24;
    *(undefined4 *)((int)local_1c + local_8 + 8) = 6;
    *(uint **)(param_1 + 0x18) = local_c;
LAB_00832e67:
    if (*(uint *)(*(int *)(param_1 + 0x10) + 0x40) <= *(uint *)(*(int *)(param_1 + 0x10) + 0x44)) {
      FUN_00830222(param_1);
    }
    break;
  case 0x25:
    local_24 = *(double **)(param_1 + 0x14);
    pdVar8 = (double *)(((uint)local_14 >> 0x17) - 1);
    local_14 = (double *)
               (((*(int *)local_24 - *(int *)((int)local_24 + 4) >> 4) -
                (uint)*(byte *)(*(int *)(local_18 + 0x10) + 0x49)) + -1);
    if (pdVar8 == (double *)0xffffffff) {
      *(uint **)(param_1 + 0x18) = local_c;
      local_20 = (undefined4 *)((int)local_14 * 0x10);
      if (*(int *)(param_1 + 0x1c) - *(int *)(param_1 + 8) <= (int)local_20) {
        FUN_0082f194(param_1,local_14);
      }
      local_8 = *(int *)(param_1 + 0xc);
      pdVar10 = (double *)((int)local_1c + local_8);
      *(int *)(param_1 + 8) = (int)local_20 + (int)pdVar10;
      pdVar8 = local_14;
    }
    local_20 = (undefined4 *)0x0;
    if (0 < (int)pdVar8) {
      local_1c = (double *)((int)local_14 * -0x10);
      pdVar10 = pdVar10 + 1;
      pdVar6 = local_1c;
      do {
        if ((int)local_20 < (int)local_14) {
          iVar3 = *(int *)local_24;
          *(undefined4 *)(pdVar10 + -1) = *(undefined4 *)(iVar3 + (int)pdVar6);
          *(undefined4 *)((int)pdVar10 + -4) = *(undefined4 *)(iVar3 + 4 + (int)pdVar6);
          *(undefined4 *)pdVar10 = *(undefined4 *)(iVar3 + 8 + (int)pdVar6);
        }
        else {
          *(undefined4 *)pdVar10 = 0;
        }
        local_20 = (undefined4 *)((int)local_20 + 1);
        pdVar6 = pdVar6 + 2;
        pdVar10 = pdVar10 + 2;
      } while ((int)local_20 < (int)pdVar8);
    }
  default:
    goto switchD_00832209_default;
  }
  local_8 = *(int *)(param_1 + 0xc);
  goto switchD_00832209_default;
switchD_00832209_caseD_1e:
  if ((uint)local_14 >> 0x17 != 0) {
    *(double **)(param_1 + 8) = pdVar10 + ((uint)local_14 >> 0x17) * 2 + -2;
  }
  if (*(int *)(param_1 + 0x68) != 0) {
    FUN_0082f92f(param_1,local_8);
  }
  *(uint **)(param_1 + 0x18) = local_c;
  iVar3 = FUN_0082f246(param_1,pdVar10);
  param_2 = param_2 + -1;
  if (param_2 == 0) {
    return;
  }
  if (iVar3 != 0) {
    *(undefined4 *)(param_1 + 8) = *(undefined4 *)(*(int *)(param_1 + 0x14) + 8);
  }
  goto LAB_0083218e;
}

