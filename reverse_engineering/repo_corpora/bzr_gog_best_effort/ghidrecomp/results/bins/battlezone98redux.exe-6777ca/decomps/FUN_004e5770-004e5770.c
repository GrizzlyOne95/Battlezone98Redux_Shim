
void FUN_004e5770(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_3c [12];
  undefined4 local_30;
  void *local_2c;
  undefined4 local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084a3c4;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_005fe690(param_1,0);
  local_8 = 0;
  *local_24 = GotoTask::vftable;
  local_24[2] = 1;
  local_24[3] = 1;
  local_2c = operator_new(0x18);
  local_8._0_1_ = 1;
  if (local_2c == (void *)0x0) {
    local_28 = 0;
  }
  else {
    uVar2 = (**(code **)(*(int *)(param_1 + 0x18) + 0xc))(param_2,uVar1);
    local_28 = FUN_00460490(uVar2,param_2);
  }
  local_30 = local_28;
  local_8 = (uint)local_8._1_3_ << 8;
  local_24[0x4d] = local_28;
  *(undefined1 *)(local_24 + 0x4f) = 1;
  local_24[0x4e] = 0;
  puVar3 = (undefined4 *)
           FUN_004e5270(local_3c,*(undefined4 *)
                                  (*(int *)(local_24[0x4d] + 8) + -8 +
                                  *(int *)(local_24[0x4d] + 4) * 8),
                        *(undefined4 *)
                         (*(int *)(local_24[0x4d] + 8) + -4 + *(int *)(local_24[0x4d] + 4) * 8));
  local_20 = *puVar3;
  local_1c = puVar3[1];
  local_18 = puVar3[2];
  local_24[0x50] = local_20;
  local_24[0x51] = local_1c;
  local_24[0x52] = local_18;
  *(undefined1 *)((int)local_24 + 0x13d) = 1;
  *(undefined1 *)((int)local_24 + 0x13e) = 0;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

