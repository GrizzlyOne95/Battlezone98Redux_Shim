
int FUN_00738e80(int param_1)

{
  uint uStack_30;
  int local_1c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a7c0;
  local_10 = ExceptionList;
  uStack_30 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_30;
  ExceptionList = &local_10;
  local_1c = FUN_0072d580();
  if (local_1c == 0) {
    local_1c = FUN_00736d50(param_1 + 0x10);
  }
  else {
    local_8 = 0;
    FUN_00738f60(&local_1c,param_1,local_15);
  }
  ExceptionList = local_10;
  return local_1c;
}

