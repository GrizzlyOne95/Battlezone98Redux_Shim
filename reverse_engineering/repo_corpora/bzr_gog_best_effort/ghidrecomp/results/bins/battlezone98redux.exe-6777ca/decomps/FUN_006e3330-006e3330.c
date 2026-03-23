
undefined4 __fastcall FUN_006e3330(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845ab8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  basic_string<>(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_00423890();
  ExceptionList = local_10;
  return param_1;
}

