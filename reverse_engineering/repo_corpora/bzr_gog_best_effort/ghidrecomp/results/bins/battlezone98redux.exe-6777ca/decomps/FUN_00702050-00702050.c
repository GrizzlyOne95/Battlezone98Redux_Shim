
void FUN_00702050(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined4 uVar3;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  basic_string<>("Sec-WebSocket-Origin");
  local_8 = 0;
  uVar3 = extraout_var;
  uVar2 = FUN_006b7490(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,uVar3,uVar2);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

