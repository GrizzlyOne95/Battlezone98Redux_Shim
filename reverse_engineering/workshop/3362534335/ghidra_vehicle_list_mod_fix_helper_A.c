
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void FUN_1000d0d0(byte *param_1)

{
  uint *puVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  byte *pbVar8;
  undefined4 ****ppppuVar9;
  byte *pbVar10;
  uint uVar11;
  code *pcVar12;
  uint uVar13;
  undefined4 *puVar14;
  undefined1 auStack_7c [16];
  undefined4 uStack_6c;
  undefined4 auStack_64 [3];
  undefined4 uStack_58;
  undefined4 *local_30;
  undefined4 ***local_2c [4];
  uint local_1c;
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_100219fd;
  local_10 = ExceptionList;
  local_14 = DAT_1002a040 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar11 = 0;
  *(undefined4 *)(DAT_1002ac30 + 0x38) = 0xffffffff;
  iVar6 = DAT_1002ac30;
  iVar2 = *(int *)(DAT_1002ac30 + 0x18);
  uVar3 = *(uint *)(iVar2 + 0x10);
  if (uVar3 != 0) {
    iVar4 = *(int *)(iVar2 + 0xc);
    iVar5 = *(int *)(iVar2 + 4);
    iVar2 = *(int *)(iVar2 + 8);
    do {
      pbVar10 = *(byte **)(iVar5 + (iVar4 + uVar11 & iVar2 - 1U) * 4);
      pbVar8 = param_1;
      if (0xf < *(uint *)(param_1 + 0x14)) {
        pbVar8 = *(byte **)param_1;
      }
      puVar1 = (uint *)(pbVar10 + 0x10);
      if (0xf < *(uint *)(pbVar10 + 0x14)) {
        pbVar10 = *(byte **)pbVar10;
      }
      uStack_58 = 0x1000d158;
      bVar7 = FUN_10014e50(pbVar10,*puVar1,pbVar8,*(uint *)(param_1 + 0x10));
      if (bVar7) {
        *(uint *)(iVar6 + 0x38) = uVar11;
        pcVar12 = DAT_1002add8;
        iVar2 = *(int *)(DAT_1002ac30 + 0x18);
        local_30 = *(undefined4 **)
                    (*(int *)(iVar2 + 4) +
                    (*(int *)(iVar2 + 8) - 1U & *(int *)(iVar2 + 0xc) + uVar11) * 4);
        if (local_30 != (undefined4 *)0x0) {
          uStack_6c = 0x1000d217;
          FUN_10018a00(auStack_64,local_30);
          local_8 = 0;
          puVar14 = local_30 + 0xf;
          goto LAB_1000d19a;
        }
        break;
      }
      uVar11 = uVar11 + 1;
    } while (uVar11 < uVar3);
  }
  pcVar12 = DAT_1002add8;
  local_30 = auStack_64;
  uStack_6c = 0x1000d189;
  FUN_10018a00(auStack_64,&DAT_1002a21c);
  local_8 = 1;
  puVar14 = &DAT_1002a204;
LAB_1000d19a:
  FUN_10018a00(auStack_7c,puVar14);
  local_8 = 0xffffffff;
  (*pcVar12)();
  FUN_10018a00(local_2c,(undefined4 *)param_1);
  local_8 = 2;
  if (local_1c != 0) {
    uVar3 = local_1c - 4;
    if (local_1c < uVar3) {
                    /* WARNING: Subroutine does not return */
      FUN_10003650();
    }
    uVar11 = local_1c;
    if (4 < local_1c) {
      uVar11 = 4;
    }
    ppppuVar9 = local_2c;
    if (0xf < local_18) {
      ppppuVar9 = (undefined4 ****)local_2c[0];
    }
    uVar13 = local_1c - uVar11;
    memmove((void *)((int)ppppuVar9 + uVar3),(void *)((int)((int)ppppuVar9 + uVar3) + uVar11),
            (uVar13 - uVar3) + 1);
    if (local_18 - uVar13 < 4) {
      local_1c = uVar13;
      FUN_100184e0(local_2c,4,local_30,&DAT_10024a24,4);
    }
    else {
      local_1c = uVar13 + 4;
      ppppuVar9 = local_2c;
      if (0xf < local_18) {
        ppppuVar9 = (undefined4 ****)local_2c[0];
      }
      *(undefined4 *)((int)ppppuVar9 + uVar13) = 0x7478762e;
      *(undefined1 *)((int)ppppuVar9 + uVar13 + 4) = 0;
    }
    (*DAT_1002ade4)(local_2c);
  }
  (*DAT_1002ade8)();
  (*DAT_1002adec)();
  (*DAT_1002addc)();
  if (0xf < local_18) {
    ppppuVar9 = (undefined4 ****)local_2c[0];
    if (0xfff < local_18 + 1) {
      ppppuVar9 = (undefined4 ****)local_2c[0][-1];
      if (0x1f < (uint)((int)local_2c[0] + (-4 - (int)ppppuVar9))) {
                    /* WARNING: Subroutine does not return */
        _invalid_parameter_noinfo_noreturn();
      }
    }
    FUN_1001f9a8(ppppuVar9);
  }
  ExceptionList = local_10;
  return;
}

