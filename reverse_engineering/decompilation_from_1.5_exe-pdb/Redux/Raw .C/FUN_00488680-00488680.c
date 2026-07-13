
undefined4 FUN_00488680(void)

{
  uint uVar1;
  undefined4 uVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00848fa8;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar2 = FUN_0048a2b0(&stack0x00000004);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1);
  ExceptionList = local_10;
  return uVar2;
}

