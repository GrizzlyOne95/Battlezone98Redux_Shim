
int __thiscall FUN_006d3710(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00852d28;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006d60e0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  uVar1 = FUN_006de380(param_2);
  *(undefined4 *)(param_1 + 0x40) = uVar1;
  FUN_006d60c0(param_1);
  ExceptionList = local_10;
  return param_1;
}

