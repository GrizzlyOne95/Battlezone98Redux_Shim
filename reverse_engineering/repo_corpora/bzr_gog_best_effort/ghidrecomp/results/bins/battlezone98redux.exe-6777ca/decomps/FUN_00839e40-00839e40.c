
void FUN_00839e40(int param_1,undefined4 *param_2)

{
  uint *puVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_30 [2];
  undefined4 local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 *local_18;
  undefined4 local_14;
  int local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  uVar2 = *(undefined4 *)(param_1 + 4);
  piVar3 = *(int **)(param_1 + 0x30);
  iVar4 = FUN_0083c5d2(piVar3,10,0,0,0);
  *param_2 = 0xb;
  param_2[4] = 0xffffffff;
  param_2[5] = 0xffffffff;
  param_2[2] = iVar4;
  local_c = 0;
  local_14 = 0;
  local_10 = 0;
  local_18 = param_2;
  local_20 = 0xffffffff;
  local_1c = 0xffffffff;
  local_30[0] = 0;
  local_28 = 0;
  FUN_0083c800(*(undefined4 *)(param_1 + 0x30),param_2);
  FUN_00839bb2(param_1,0x7b);
  do {
    if (*(int *)(param_1 + 0x10) == 0x7d) break;
    if (local_30[0] != 0) {
      FUN_0083c800(piVar3,local_30);
      local_30[0] = 0;
      if (local_c == 0x32) {
        FUN_0083cdbd(piVar3,local_18[2],local_10,0x32);
        local_c = 0;
      }
    }
    if ((*(int *)(param_1 + 0x10) == 0x5b) ||
       ((*(int *)(param_1 + 0x10) == 0x11d &&
        (FUN_00838f93(param_1), *(int *)(param_1 + 0x20) == 0x3d)))) {
      FUN_0083af59(param_1,local_30);
    }
    else {
      FUN_0083a994(param_1,local_30);
    }
    iVar5 = FUN_0083b6c3(param_1,0x2c);
  } while ((iVar5 != 0) || (iVar5 = FUN_0083b6c3(param_1,0x3b), iVar5 != 0));
  FUN_00839b38(param_1,0x7d,0x7b,uVar2);
  if (local_c != 0) {
    if ((local_30[0] == 0xd) || (local_30[0] == 0xe)) {
      FUN_0083ce76(piVar3,local_30,0xffffffff);
      FUN_0083cdbd(piVar3,local_18[2],local_10,0xffffffff);
      local_10 = local_10 + -1;
    }
    else {
      if (local_30[0] != 0) {
        FUN_0083c800(piVar3,local_30);
      }
      FUN_0083cdbd(piVar3,local_18[2],local_10,local_c);
    }
  }
  iVar5 = *(int *)(*piVar3 + 0xc);
  iVar6 = FUN_0082e87e(local_10);
  *(uint *)(iVar5 + iVar4 * 4) = iVar6 << 0x17 | *(uint *)(iVar5 + iVar4 * 4) & 0x7fffff;
  iVar5 = *(int *)(*piVar3 + 0xc);
  iVar6 = FUN_0082e87e(local_14);
  puVar1 = (uint *)(iVar5 + iVar4 * 4);
  *puVar1 = *puVar1 ^ (iVar6 << 0xe ^ *(uint *)(iVar5 + iVar4 * 4)) & 0x7fc000;
  FUN_0083e885();
  return;
}

