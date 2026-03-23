
void FUN_007df900(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  uint uStack_3c;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863710;
  local_10 = ExceptionList;
  uStack_3c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_3c;
  ExceptionList = &local_10;
  uVar1 = FUN_004600d0();
  puVar2 = (undefined1 *)FUN_00425000(uVar1);
  *puVar2 = 0;
  puVar2 = (undefined1 *)FUN_004242d0(uVar1);
  *puVar2 = 0;
  local_8 = 0;
  uVar3 = FUN_00417780(param_1);
  uVar1 = FUN_00424300(uVar1);
  Getal(&local_15);
  uVar1 = FUN_00417780(uVar1,uVar3);
  construct<>(uVar1,uVar3);
  FUN_007df9c2();
  return;
}

