
undefined4 * __thiscall
FUN_00426b10(undefined4 *param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084548b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  FUN_00428310(uVar1);
  local_8 = 0;
  vector<>();
  *(undefined1 *)(param_1 + 7) = param_2;
  *(undefined1 *)((int)param_1 + 0x1d) = param_3;
  *(undefined1 *)((int)param_1 + 0x1e) = param_4;
  *(undefined1 *)((int)param_1 + 0x1f) = 1;
  param_1[8] = 0;
  ExceptionList = local_10;
  return param_1;
}

