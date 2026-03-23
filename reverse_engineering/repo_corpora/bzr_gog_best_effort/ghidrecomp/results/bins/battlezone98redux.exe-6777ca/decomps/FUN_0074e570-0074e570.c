
void FUN_0074e570(void)

{
  undefined4 uStack_54;
  undefined1 *puStack_50;
  undefined4 uStack_4c;
  undefined4 uStack_48;
  uint uStack_44;
  undefined1 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  int *local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844a78;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uStack_48 = 0x74e5a0;
  local_14 = uStack_44;
  local_30 = (int *)FUN_0074db30();
  if (local_30 != (int *)0x0) {
    uStack_48 = 0xffa;
    uStack_4c = 0;
    puStack_50 = local_2c;
    uStack_54 = 0x74e5bc;
    local_38 = FUN_0045e1d0();
    local_8 = 0;
    uStack_48 = 0x74e5d4;
    local_34 = local_38;
    uStack_48 = FUN_0041f870();
    uStack_4c = 0x74e5dd;
    uStack_4c = FUN_0041f870();
    local_3c = (undefined1 *)&uStack_54;
    FUN_0073a9b0(&uStack_54);
    (**(code **)(*local_30 + 0x50))();
    local_8 = 0xffffffff;
    uStack_48 = 0x74e60b;
    ~basic_string<>();
  }
  ExceptionList = local_10;
  uStack_44 = 0x74e620;
  FUN_0083e885();
  return;
}

