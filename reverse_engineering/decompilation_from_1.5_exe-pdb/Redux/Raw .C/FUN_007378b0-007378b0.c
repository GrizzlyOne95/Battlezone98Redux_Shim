
void __thiscall FUN_007378b0(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_74 [96];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00855d78;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00737cd0(param_2);
  local_8 = 0;
  FUN_00738100(param_1 + 4,local_74);
  FUN_00417c60(uVar1);
  local_8 = 0xffffffff;
  FUN_006ff7f0();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

