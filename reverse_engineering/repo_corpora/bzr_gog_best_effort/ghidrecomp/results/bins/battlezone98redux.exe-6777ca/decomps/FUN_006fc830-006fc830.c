
void FUN_006fc830(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  uint uVar1;
  undefined1 *puVar2;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084f068;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  for (; param_2 != param_3; param_2 = param_2 + 0x11) {
    basic_string<>(param_2);
    local_8 = 0;
    puVar2 = local_2c;
    std::allocator<char>::allocator<char>((allocator<char> *)&param_4);
    FUN_00700960(puVar2);
    local_8 = 0xffffffff;
    ~basic_string<>(uVar1);
    std::allocator<char>::allocator<char>((allocator<char> *)&param_4);
  }
  *param_1 = param_4;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

