
void FUN_0083b7e1(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  undefined8 local_14;
  int local_c;
  uint *local_8;
  
  iVar1 = FUN_0083bbeb(param_1);
  iVar6 = 0;
  if (iVar1 + 1U < 0x10000000) {
    uVar2 = FUN_00838869(*param_1,0,0,iVar1 << 4);
  }
  else {
    uVar2 = FUN_008388ab(*param_1);
  }
  *(undefined4 *)(param_2 + 8) = uVar2;
  *(int *)(param_2 + 0x28) = iVar1;
  if (0 < iVar1) {
    iVar3 = 0;
    iVar5 = iVar1;
    do {
      *(undefined4 *)(iVar3 + 8 + *(int *)(param_2 + 8)) = 0;
      iVar5 = iVar5 + -1;
      iVar3 = iVar3 + 0x10;
    } while (iVar5 != 0);
    if (0 < iVar1) {
      local_c = 0;
      do {
        local_8 = (uint *)(*(int *)(param_2 + 8) + local_c);
        iVar3 = FUN_0083b7c4(param_1);
        if (iVar3 == 0) {
          local_8[2] = 0;
        }
        else if (iVar3 == 1) {
          iVar3 = FUN_0083b7c4(param_1);
          *local_8 = (uint)(iVar3 != 0);
          local_8[2] = 1;
        }
        else if (iVar3 == 3) {
          FUN_0083b798(param_1,&local_14,8);
          *(undefined8 *)local_8 = local_14;
          local_8[2] = 3;
        }
        else if (iVar3 == 4) {
          uVar4 = FUN_0083bc1d(param_1);
          *local_8 = uVar4;
          local_8[2] = 4;
        }
        else {
          FUN_0083bc6e(param_1,"bad constant");
        }
        local_c = local_c + 0x10;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  iVar1 = FUN_0083bbeb(param_1);
  if (iVar1 + 1U < 0x40000000) {
    uVar2 = FUN_00838869(*param_1,0,0,iVar1 << 2);
  }
  else {
    uVar2 = FUN_008388ab(*param_1);
  }
  *(undefined4 *)(param_2 + 0x10) = uVar2;
  iVar3 = 0;
  *(int *)(param_2 + 0x34) = iVar1;
  if (0 < iVar1) {
    do {
      *(undefined4 *)(*(int *)(param_2 + 0x10) + iVar3 * 4) = 0;
      iVar3 = iVar3 + 1;
    } while (iVar3 < iVar1);
    if (0 < iVar1) {
      do {
        uVar2 = FUN_0083bac1(param_1,*(undefined4 *)(param_2 + 0x20));
        *(undefined4 *)(*(int *)(param_2 + 0x10) + iVar6 * 4) = uVar2;
        iVar6 = iVar6 + 1;
      } while (iVar6 < iVar1);
    }
  }
  return;
}

