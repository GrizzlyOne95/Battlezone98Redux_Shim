
void __thiscall FUN_00812bd0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859da1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_007fb800(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_006d0d10();
  iVar2 = forward<>(0x18,uVar1);
  local_8 = 0;
  if (iVar2 != 0) {
    uVar1 = FUN_00417780(param_2);
    basic_string<>(uVar1);
  }
  local_8 = 0xffffffff;
  FUN_0045ba10(*(undefined4 *)(param_1 + 4));
  ExceptionList = local_10;
  return;
}

