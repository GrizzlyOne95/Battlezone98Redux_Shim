
void FUN_007198e0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uStack_25c;
  undefined4 uStack_258;
  uint uStack_254;
  undefined4 uStack_250;
  uint uStack_24c;
  undefined1 *local_248;
  undefined4 local_244;
  undefined4 local_240;
  undefined4 local_238;
  int local_234;
  undefined4 local_230;
  undefined4 local_22c;
  undefined4 local_228;
  undefined4 local_224;
  byte local_21d;
  allocator<char> local_21c [520];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00858382;
  local_10 = ExceptionList;
  uStack_24c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_250 = param_4;
  uStack_254 = 0x71991a;
  local_14 = uStack_24c;
  local_22c = FUN_00417780();
  uStack_250 = param_4;
  uStack_254 = 0xa8;
  uStack_258 = 0x719931;
  uStack_250 = FUN_00724370();
  local_224 = 0;
  local_8 = 0;
  uStack_254 = 0xa8;
  uStack_258 = 0x71995c;
  local_228 = uStack_250;
  local_234 = forward<>();
  local_8._0_1_ = 1;
  if (local_234 == 0) {
    local_230 = 0;
  }
  else {
    uStack_250 = param_4;
    uStack_254 = param_2;
    local_248 = (undefined1 *)&uStack_25c;
    local_244 = shared_ptr<>(param_1 + 8);
    local_240 = FUN_0071d810();
    local_230 = local_240;
  }
  local_238 = local_230;
  local_8 = (uint)local_8._1_3_ << 8;
  local_224 = local_230;
  uStack_250 = param_2;
  uStack_254 = 0x7199eb;
  FUN_0071d6e0();
  if ((*(byte *)(param_1 + 4) & 0x10) != 0) {
    uStack_250 = 0x719a02;
    cVar1 = FUN_0071d7e0();
    if (cVar1 != '\0') {
      local_21d = 1;
      goto LAB_00719a19;
    }
  }
  local_21d = 0;
LAB_00719a19:
  uStack_250 = local_224;
  uStack_254 = (uint)local_21d;
  uStack_258 = param_3;
  uStack_25c = 0x719a37;
  uStack_25c = FUN_0071d7c0();
  uVar2 = std::allocator<char>::allocator<char>(local_21c);
  FUN_006b19a0(param_1,uVar2);
  local_224 = 0;
  local_228 = 0;
  local_8 = 0xffffffff;
  uStack_250 = 0x719a7b;
  FUN_0071d8b0();
  ExceptionList = local_10;
  uStack_24c = 0x719a90;
  FUN_0083e885();
  return;
}

