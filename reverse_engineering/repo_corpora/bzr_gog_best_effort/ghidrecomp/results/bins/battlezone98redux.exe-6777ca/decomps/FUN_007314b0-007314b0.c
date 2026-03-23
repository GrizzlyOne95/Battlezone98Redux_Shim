
void __thiscall FUN_007314b0(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00859da1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_006d0c90(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar1 = FUN_006d0d10();
  puVar2 = (undefined1 *)forward<>(1,uVar1);
  local_8 = 0;
  if (puVar2 != (undefined1 *)0x0) {
    puVar3 = (undefined1 *)FUN_00417780(param_2);
    *puVar2 = *puVar3;
  }
  local_8 = 0xffffffff;
  FUN_0045ba10(*(undefined4 *)(param_1 + 4));
  ExceptionList = local_10;
  return;
}

