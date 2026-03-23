
void __fastcall FUN_0059ad10(int param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c128;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_00623ff0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_00462630(*(undefined4 *)(param_1 + 0xc4));
  FUN_005940e0(uVar1);
  local_8 = 0;
  FUN_00594270();
  FUN_00623eb0();
  local_8 = 0xffffffff;
  FUN_005941f0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

