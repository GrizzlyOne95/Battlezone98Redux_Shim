
void __fastcall FUN_007a6a60(undefined4 param_1)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848fa8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar1 = FUN_0041f870(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  FUN_006247a0(0xfffa,uVar1);
  FUN_007cf9f0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

