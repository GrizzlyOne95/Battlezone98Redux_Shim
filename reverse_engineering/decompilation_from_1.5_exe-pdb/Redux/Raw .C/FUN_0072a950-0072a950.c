
void FUN_0072a950(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  uint uStack_54;
  undefined4 uStack_50;
  uint uStack_4c;
  allocator<char> local_48 [12];
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined1 *local_2c;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  byte local_11;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859779;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_50 = param_4;
  uStack_54 = 0x72a981;
  local_3c = FUN_00417780();
  uStack_50 = param_4;
  uStack_54 = 0x90;
  uStack_58 = 0x72a995;
  uStack_50 = FUN_0072f990();
  local_34 = 0;
  local_8 = 0;
  uStack_54 = 0x90;
  uStack_58 = 0x72a9b7;
  local_38 = uStack_50;
  local_18 = forward<>();
  local_8._0_1_ = 1;
  if (local_18 == 0) {
    local_1c = 0;
  }
  else {
    uStack_50 = param_4;
    uStack_54 = param_2;
    local_2c = (undefined1 *)&uStack_5c;
    local_30 = shared_ptr<>(param_1 + 8);
    local_20 = FUN_0072c620(*(undefined1 *)(param_1 + 4));
    local_1c = local_20;
  }
  local_24 = local_1c;
  local_8 = (uint)local_8._1_3_ << 8;
  local_34 = local_1c;
  uStack_50 = param_2;
  uStack_54 = 0x72aa24;
  FUN_00703cb0();
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    uStack_50 = 0x72aa38;
    cVar1 = FUN_006c9d60();
    if (cVar1 != '\0') {
      local_11 = 1;
      goto LAB_0072aa49;
    }
  }
  local_11 = 0;
LAB_0072aa49:
  uStack_50 = local_34;
  uStack_54 = (uint)local_11;
  uStack_58 = param_3;
  uStack_5c = 0x72aa5e;
  uStack_5c = FUN_006b3f60();
  uVar2 = std::allocator<char>::allocator<char>(local_48);
  FUN_006b1a90(param_1,uVar2);
  local_34 = 0;
  local_38 = 0;
  local_8 = 0xffffffff;
  uStack_50 = 0x72aa90;
  FUN_0072c6c0();
  ExceptionList = local_10;
  return;
}

