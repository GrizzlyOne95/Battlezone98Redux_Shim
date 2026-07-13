
undefined4 __fastcall FUN_004186f0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00844ab3;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  vector<>();
  local_8 = CONCAT31(local_8._1_3_,1);
  FUN_00418760();
  ExceptionList = local_10;
  return param_1;
}

