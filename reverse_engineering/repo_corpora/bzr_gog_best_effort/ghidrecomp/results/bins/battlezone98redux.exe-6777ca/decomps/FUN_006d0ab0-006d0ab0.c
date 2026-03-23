
void FUN_006d0ab0(void)

{
  uint uVar1;
  undefined4 extraout_var;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00853068;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d4a20(0);
  local_8 = 0xffffffff;
  FUN_006d12c0(uVar1,extraout_var);
  ExceptionList = local_10;
  return;
}

