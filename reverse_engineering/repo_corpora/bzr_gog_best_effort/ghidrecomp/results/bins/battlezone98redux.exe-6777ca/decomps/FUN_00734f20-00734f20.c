
void __thiscall FUN_00734f20(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_d4 [192];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a25b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00735cc0(param_2);
  local_8 = 0;
  FUN_00736320(param_1 + 4,local_d4);
  FUN_00417c60(uVar1);
  local_8 = 0xffffffff;
  FUN_00735720();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

