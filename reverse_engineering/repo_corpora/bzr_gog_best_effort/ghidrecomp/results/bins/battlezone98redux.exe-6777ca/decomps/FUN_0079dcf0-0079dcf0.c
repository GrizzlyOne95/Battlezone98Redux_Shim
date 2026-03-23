
void FUN_0079dcf0(void)

{
  uint uVar1;
  undefined4 extraout_var;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848fa8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_00745fa0(&stack0x00000004);
  FUN_007cf9f0(uVar1,extraout_var);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

