
void __fastcall FUN_008104a0(undefined4 param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
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
  uVar3 = 0;
  local_14 = uVar1;
  uVar2 = FUN_00810e90(0,uVar1,param_1,0);
  basic_string<>(uVar2);
  local_8 = 0;
  FUN_007fae60(local_2c);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,param_1,uVar3 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

