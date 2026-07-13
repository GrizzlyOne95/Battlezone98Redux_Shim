
void FUN_006fcb70(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 auStack_50 [8];
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  uint uStack_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 *local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855cd9;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_40 = param_3;
  uStack_44 = 0x6fcba1;
  local_38 = FUN_00417780();
  uStack_40 = param_3;
  uStack_44 = 0xd8;
  uStack_48 = 0x6fcbb5;
  uStack_40 = FUN_0070cd40();
  local_30 = 0;
  local_8 = 0;
  uStack_44 = 0xd8;
  uStack_48 = 0x6fcbd7;
  local_34 = uStack_40;
  local_14 = forward<>();
  local_8._0_1_ = 1;
  if (local_14 == 0) {
    local_18 = 0;
  }
  else {
    uStack_40 = param_3;
    uStack_44 = *local_1c;
    uStack_48 = param_2;
    local_28 = auStack_50;
    local_2c = shared_ptr<>(param_1);
    local_20 = FUN_00703e30();
    local_18 = local_20;
  }
  local_24 = local_18;
  local_8 = (uint)local_8._1_3_ << 8;
  local_30 = local_18;
  uStack_40 = local_18;
  uStack_44 = 0x6fcc3f;
  FUN_006b3e20();
  local_30 = 0;
  local_34 = 0;
  local_8 = 0xffffffff;
  uStack_40 = 0x6fcc5b;
  FUN_00703f00();
  ExceptionList = local_10;
  return;
}

