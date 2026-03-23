
undefined4 * __fastcall FUN_0073ce90(undefined4 *param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085aaa1;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = cUser::vftable;
  FUN_0073a6b0(uVar1);
  FUN_0073a6b0();
  basic_string<>();
  local_8 = 0;
  basic_string<>();
  local_8._0_1_ = 1;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  *(undefined1 *)(param_1 + 0x23) = 0;
  param_1[0x21] = 0;
  param_1[0x22] = 0;
  param_1[0x24] = 0;
  *(undefined2 *)(param_1 + 0x25) = 0;
  param_1[0x20] = 0xffffffff;
  *(undefined2 *)(param_1 + 10) = 0;
  *(undefined1 *)(param_1 + 0x1f) = 0;
  FUN_0056f7e0();
  FUN_0056f7e0();
  *(undefined1 *)(param_1 + 0x11) = 0;
  *(undefined1 *)(param_1 + 0x18) = 0;
  *(undefined1 *)((int)param_1 + 0x61) = 0;
  ExceptionList = local_10;
  return param_1;
}

