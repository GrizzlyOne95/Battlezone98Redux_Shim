
undefined4 * __fastcall FUN_0073bbd0(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008458bb;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  basic_string<>(uVar1);
  local_8 = 0;
  *(undefined1 *)(param_1 + 7) = 0;
  param_1[8] = 0;
  basic_string<>(&DAT_00873c74);
  *(undefined1 *)(param_1 + 0xf) = 0;
  *(undefined1 *)((int)param_1 + 0x3d) = 0;
  *(undefined1 *)((int)param_1 + 0x3e) = 0;
  param_1[0x10] = 0;
  param_1[0x11] = 1;
  param_1[0x12] = 2;
  *(undefined1 *)(param_1 + 0x13) = 0;
  param_1[0x14] = 0;
  *(undefined1 *)(param_1 + 0x15) = 0;
  ExceptionList = local_10;
  return param_1;
}

