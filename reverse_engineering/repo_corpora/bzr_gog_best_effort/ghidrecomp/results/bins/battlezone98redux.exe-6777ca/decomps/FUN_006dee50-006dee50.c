
void FUN_006dee50(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 uVar2;
  undefined1 auStack_fc [164];
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined1 *local_48;
  undefined1 local_44 [24];
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00853bcb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00574400(3,1);
  local_8 = 0;
  if (&stack0x00000000 == (undefined1 *)0x10c) {
    local_48 = (undefined1 *)0x0;
  }
  else {
    local_48 = auStack_fc;
  }
  local_54 = FUN_004486a0(local_2c);
  local_8._0_1_ = 1;
  local_50 = local_54;
  uVar2 = FUN_004bc590(local_48,param_2," error: ",*param_3,param_3[1],&DAT_00884900,local_54,
                       &DAT_008848a8,uVar1);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_006da310(uVar2);
  uVar2 = FUN_004bc590(uVar2);
  uVar2 = FUN_00574730(uVar2);
  FUN_004bc590(uVar2);
  local_8._0_1_ = 0;
  ~basic_string<>();
  local_58 = GetPolicy(local_44);
  local_8._0_1_ = 2;
  local_4c = local_58;
  FUN_006d46a0(param_1,local_58);
  local_8 = (uint)local_8._1_3_ << 8;
  ~basic_string<>();
  local_8 = 0xffffffff;
  FUN_00417f10();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

