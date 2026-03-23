
void __thiscall FUN_006b0c30(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 local_1c [8];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008504b8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = param_1;
  FUN_006c8ce0(param_1 + 0x18);
  local_8 = 0;
  FUN_006d8cc0(0x3e3,0);
  FUN_006b1240(param_2,local_1c);
  local_8 = 0xffffffff;
  FUN_006c8d50(uVar1);
  ExceptionList = local_10;
  return;
}

