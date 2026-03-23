
undefined4 * __fastcall FUN_0041bf20(undefined4 *param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844dc4;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004b6260(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  *param_1 = ButtonSystem::vftable;
  vector<>();
  local_8._0_1_ = 1;
  vector<>();
  local_8._0_1_ = 2;
  basic_string<>();
  local_8._0_1_ = 3;
  basic_string<>();
  local_8._0_1_ = 4;
  basic_string<>();
  local_8._0_1_ = 5;
  vector<>();
  local_8._0_1_ = 6;
  vector<>();
  local_8._0_1_ = 7;
  vector<>();
  local_8._0_1_ = 8;
  FUN_00420160();
  local_8 = CONCAT31(local_8._1_3_,9);
  vector<>();
  param_1[0x28] = 0;
  param_1[3] = 0;
  *(undefined1 *)(param_1 + 4) = 0;
  *(undefined1 *)(param_1 + 2) = 1;
  param_1[0x1d] = 1;
  param_1[0x1e] = 1;
  ExceptionList = local_10;
  return param_1;
}

