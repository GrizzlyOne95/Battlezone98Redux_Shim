
/* WARNING: Removing unreachable block (ram,0x00841084) */

void FUN_00840f20(short *param_1)

{
  short sVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  char cVar6;
  uint uVar7;
  undefined4 *puVar8;
  short *psVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  void *local_28 [5];
  uint local_14;
  uint local_10;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  local_4 = 0xffffffff;
  puStack_8 = &LAB_00865808;
  local_c = ExceptionList;
  local_10 = DAT_008e7000 ^ (uint)local_28;
  uVar7 = DAT_008e7000 ^ (uint)&stack0xffffffc8;
  ExceptionList = &local_c;
  puVar2 = *(undefined4 **)(param_1 + 0xc);
  uVar3 = *(uint *)(param_1 + 8);
  *(uint *)(param_1 + 0xe) = *(int *)(param_1 + 0xe) + uVar3;
  iVar12 = *(int *)(param_1 + 0xe);
  iVar11 = puVar2[4];
  if (iVar12 == iVar11) {
    param_1[8] = 0;
    param_1[9] = 0;
    if (7 < *(uint *)(param_1 + 10)) {
      param_1 = *(short **)param_1;
    }
    *param_1 = 0;
    goto LAB_008410e1;
  }
  if (uVar3 < 3) {
LAB_00840fd8:
    bVar5 = false;
  }
  else {
    uVar4 = *(uint *)(param_1 + 10);
    psVar9 = param_1;
    if (7 < uVar4) {
      psVar9 = *(short **)param_1;
    }
    if ((*psVar9 != 0x2f) && (*psVar9 != 0x5c)) goto LAB_00840fd8;
    psVar9 = param_1;
    if (7 < uVar4) {
      psVar9 = *(short **)param_1;
    }
    if ((psVar9[1] != 0x2f) && (psVar9[1] != 0x5c)) goto LAB_00840fd8;
    psVar9 = param_1;
    if (7 < uVar4) {
      psVar9 = *(short **)param_1;
    }
    if ((psVar9[2] == 0x2f) || (psVar9[2] == 0x5c)) goto LAB_00840fd8;
    bVar5 = true;
  }
  puVar8 = puVar2;
  if (7 < (uint)puVar2[5]) {
    puVar8 = (undefined4 *)*puVar2;
  }
  sVar1 = *(short *)((int)puVar8 + iVar12 * 2);
  if ((sVar1 == 0x2f) || (sVar1 == 0x5c)) {
    if (!bVar5) {
      psVar9 = param_1;
      if (7 < *(uint *)(param_1 + 10)) {
        psVar9 = *(short **)param_1;
      }
      if (psVar9[uVar3 - 1] != 0x3a) {
        if (iVar12 != iVar11) {
          do {
            puVar8 = puVar2;
            if (7 < (uint)puVar2[5]) {
              puVar8 = (undefined4 *)*puVar2;
            }
            sVar1 = *(short *)((int)puVar8 + *(int *)(param_1 + 0xe) * 2);
          } while (((sVar1 == 0x2f) || (sVar1 == 0x5c)) &&
                  (iVar12 = *(int *)(param_1 + 0xe) + 1, *(int *)(param_1 + 0xe) = iVar12,
                  iVar12 != puVar2[4]));
        }
        iVar11 = puVar2[4];
        if (*(int *)(param_1 + 0xe) == iVar11) {
          iVar12 = *(int *)(param_1 + 0xe) + -1;
          cVar6 = FUN_00840b30(puVar2,iVar12,uVar7);
          if (cVar6 == '\0') {
            *(int *)(param_1 + 0xe) = iVar12;
            psVar9 = (short *)FUN_00840370();
            if (param_1 != psVar9) {
              FID_conflict_assign(psVar9,0,0xffffffff);
            }
            goto LAB_008410e1;
          }
        }
        goto LAB_00841073;
      }
    }
    FUN_0083f9c0(0x2f);
  }
  else {
LAB_00841073:
    iVar12 = *(int *)(param_1 + 0xe);
    iVar10 = FUN_008408e0(&DAT_00870c04,iVar12,2);
    if (iVar10 == -1) {
      iVar10 = iVar11;
    }
    psVar9 = (short *)FUN_008417a0(local_28,iVar12,iVar10 - iVar12);
    local_4 = 0;
    if (param_1 != psVar9) {
      FID_conflict_assign(psVar9,0,0xffffffff);
    }
    if (7 < local_14) {
      operator_delete(local_28[0]);
    }
  }
LAB_008410e1:
  ExceptionList = local_c;
  FUN_0083e885();
  return;
}

