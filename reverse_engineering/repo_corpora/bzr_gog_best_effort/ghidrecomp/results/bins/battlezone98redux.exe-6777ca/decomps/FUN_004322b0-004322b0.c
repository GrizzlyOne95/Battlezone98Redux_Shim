
void FUN_004322b0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  uint uStack_3c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008459f0;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_3c;
  ExceptionList = &local_10;
  uVar1 = FUN_00429e70(param_1,param_2);
  local_8 = 0;
  uVar2 = FUN_00417780(param_3);
  uVar1 = FUN_004242f0(uVar1);
  Getal(&local_15);
  uVar1 = FUN_00417780(uVar1,uVar2);
  construct<>(uVar1,uVar2);
  FUN_00432369(param_2);
  return;
}

