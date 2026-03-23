
undefined4 * FUN_004a7a20(undefined4 param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  void *local_24;
  undefined4 local_20;
  void *local_1c;
  int *local_18;
  undefined4 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00849638;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_004da0b0(param_1,param_2);
  local_8 = 0;
  *local_14 = Craft::vftable;
  local_14[6] = Craft::vftable;
  FUN_0083ead2(local_14 + 0x8f,4,8,FUN_00423890,FUN_0044dc30);
  local_8._0_1_ = 1;
  FUN_0062f5c0(local_14[0x3d],uVar1);
  local_14[0x8a] = 0;
  local_14[0x8b] = 0;
  uVar2 = FUN_0045c4f0(param_1);
  local_14[0x8c] = uVar2;
  *(undefined4 *)local_14[0x8c] = local_14[0x3c];
  local_14[0x8d] = 0;
  FUN_004dbce0(0);
  if (0.0 < *(float *)(param_2 + 0x150)) {
    local_1c = operator_new(0x14);
    local_8._0_1_ = 2;
    if (local_1c == (void *)0x0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_005c18e0(local_14);
    }
    local_2c = local_20;
    local_8._0_1_ = 1;
    local_14[0x66] = local_20;
    *(undefined4 *)local_14[0x66] = *(undefined4 *)(param_2 + 0x150);
    *(undefined4 *)(local_14[0x66] + 4) = *(undefined4 *)(param_2 + 0x154);
  }
  local_14[0xa2] = *(undefined4 *)(param_2 + 0x15c);
  if (0.0 < *(float *)(param_2 + 0x158)) {
    local_24 = operator_new(8);
    local_8._0_1_ = 3;
    if (local_24 == (void *)0x0) {
      local_28 = 0;
    }
    else {
      local_28 = FUN_004a7770(local_14);
    }
    local_30 = local_28;
    local_8._0_1_ = 1;
    local_14[0x67] = local_28;
    *(undefined4 *)local_14[0x67] = *(undefined4 *)(param_2 + 0x158);
  }
  puVar4 = (undefined4 *)local_14[0x8c];
  puVar5 = local_14 + 0x45;
  for (iVar3 = 0x12; puVar4 = puVar4 + 1, iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar5 = puVar5 + 1;
  }
  if (((local_14[0x3c] == 0) || (*(int *)(local_14[0x3c] + 0x24) != 1)) ||
     (*(int *)(local_14[0x3c] + 0x28) == 0)) {
    FUN_0062e650(local_14[0x3d],local_14[0x3d] + 0xb0,local_14[0x3d] + 0xbc);
  }
  else {
    local_18 = *(int **)(local_14[0x3c] + 0x28);
    *(int *)(local_14[0x3d] + 0xb0) = local_18[3];
    *(int *)(local_14[0x3d] + 0xb4) = local_18[7];
    *(int *)(local_14[0x3d] + 0xb8) = local_18[0xb];
    *(int *)(local_14[0x3d] + 0xbc) = local_18[*local_18 + 2];
    *(int *)(local_14[0x3d] + 0xc0) = local_18[local_18[1] + 6];
    *(int *)(local_14[0x3d] + 0xc4) = local_18[local_18[2] + 10];
  }
  *(undefined4 *)(local_14[0x8c] + 0x110) = 0xf149f2ca;
  *(undefined1 *)((int)local_14 + 0x79) = 0;
  local_14[0x8e] = 0;
  local_14[0x9f] = 0;
  FUN_004a79a0(local_14[0x3d]);
  if (local_14[0x9f] == 0) {
    local_14[local_14[0x9f] + 0x97] = local_14[0x3d];
    local_14[0x9f] = local_14[0x9f] + 1;
  }
  local_14[0xa0] = 0;
  local_14[0xa1] = 0;
  local_34 = local_14;
  FUN_0041fe40(&local_34);
  local_14[0xa6] = 0;
  *(undefined1 *)(local_14 + 0xa3) = *(undefined1 *)(param_2 + 0x300);
  local_14[0xa5] = *(undefined4 *)(param_2 + 0x304);
  local_14[0xa4] = *(undefined4 *)(param_2 + 0x308);
  *(undefined1 *)((int)local_14 + 0x28d) = 1;
  ExceptionList = local_10;
  return local_14;
}

