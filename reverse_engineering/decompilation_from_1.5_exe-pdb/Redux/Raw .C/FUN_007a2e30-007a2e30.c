
void FUN_007a2e30(undefined4 param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uStack_48;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00860190;
  local_10 = ExceptionList;
  uStack_48 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_48;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar1 = FUN_004242f0(param_1);
  Getal(&local_15);
  uVar1 = FUN_00417780(uVar1);
  destroy<>(uVar1);
  uVar1 = FUN_00417780(param_2);
  uVar2 = FUN_004242f0(param_1);
  Getal(&local_16);
  uVar2 = FUN_00417780(uVar2,uVar1);
  construct<>(uVar2,uVar1);
  FUN_007a2f70();
  return;
}

