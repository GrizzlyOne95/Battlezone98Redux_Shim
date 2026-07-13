
void FUN_0074b9f0(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_var;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  uVar2 = FUN_0073a9f0(local_2c);
  local_8 = 0;
  get(uVar2,uVar1,uVar2,extraout_var);
  FUN_006c49f0(uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

