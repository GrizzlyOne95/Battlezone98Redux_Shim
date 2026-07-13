
void FUN_006fa320(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 uStack_4c;
  uint uStack_48;
  allocator<char> local_44 [12];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined1 *local_28;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855b49;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_4c = param_5;
  uStack_50 = 0x6fa351;
  local_38 = FUN_00417780();
  uStack_4c = param_5;
  uStack_50 = 0x40;
  uStack_54 = 0x6fa362;
  uStack_4c = FUN_0070ae20();
  local_30 = 0;
  local_8 = 0;
  uStack_50 = 0x40;
  uStack_54 = 0x6fa381;
  local_34 = uStack_4c;
  local_14 = forward<>();
  local_8._0_1_ = 1;
  if (local_14 == 0) {
    local_18 = 0;
  }
  else {
    uStack_4c = param_5;
    uStack_50 = param_2;
    local_28 = (undefined1 *)&uStack_58;
    local_2c = shared_ptr<>(param_1 + 8);
    local_1c = FUN_00703be0(param_3);
    local_18 = local_1c;
  }
  local_20 = local_18;
  local_8 = (uint)local_8._1_3_ << 8;
  local_30 = local_18;
  uStack_4c = param_2;
  uStack_50 = 0x6fa3ea;
  FUN_00703cb0();
  uStack_4c = local_30;
  uStack_50 = 0x6fa3f6;
  uStack_50 = FUN_006b73e0();
  uStack_54 = param_4;
  uStack_58 = 0x6fa403;
  uStack_58 = FUN_006d0d10();
  uVar1 = FUN_006b3f60();
  uVar2 = std::allocator<char>::allocator<char>(local_44);
  FUN_006b1ba0(param_1,uVar2,uVar1);
  local_30 = 0;
  local_34 = 0;
  local_8 = 0xffffffff;
  uStack_4c = 0x6fa43e;
  FUN_00703c90();
  ExceptionList = local_10;
  return;
}

