
undefined4 FUN_007bdae0(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00861a61;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = 0;
  local_8 = 1;
  FUN_006676e0(&stack0x00000008);
  local_8 = local_8 & 0xffffff00;
  FUN_00667660(uVar1,uVar2 | 1);
  ExceptionList = local_10;
  return param_1;
}

