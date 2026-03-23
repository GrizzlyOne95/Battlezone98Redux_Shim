
undefined4 __fastcall FUN_006c2df0(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00851c2b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0073a6b0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_0073a6b0();
  FUN_006ca5f0();
  local_8 = 0;
  FUN_006caf80();
  ExceptionList = local_10;
  return param_1;
}

