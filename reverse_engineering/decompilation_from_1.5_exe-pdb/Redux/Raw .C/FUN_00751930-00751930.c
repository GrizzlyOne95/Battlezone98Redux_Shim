
void FUN_00751930(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085c048;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>(&DAT_008a1ad8);
  local_8 = 0;
  uVar2 = FUN_0073a6e0(param_1 + 8);
  puVar4 = local_2c;
  uVar3 = FUN_0073a6e0(param_1);
  FUN_007408c0(uVar3,puVar4,uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

