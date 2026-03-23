
void __fastcall FUN_006c8b90(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008526c8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_0066ae30(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  local_8 = 0;
  FUN_006cd7b0(param_1);
  local_8 = 0xffffffff;
  FUN_006676c0();
  ExceptionList = local_10;
  return;
}

