
undefined4 __fastcall FUN_006c2e90(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851c71;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0073a6b0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_0073a6b0();
  basic_string<>();
  local_8 = 0;
  FUN_006ca5f0();
  local_8._0_1_ = 1;
  basic_string<>();
  local_8 = CONCAT31(local_8._1_3_,2);
  FUN_00422260();
  ExceptionList = local_10;
  return param_1;
}

