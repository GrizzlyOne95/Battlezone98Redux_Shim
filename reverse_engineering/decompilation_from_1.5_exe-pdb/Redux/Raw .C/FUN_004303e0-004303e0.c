
void __fastcall FUN_004303e0(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uStack_4c;
  undefined1 local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845890;
  local_10 = ExceptionList;
  uStack_4c = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_4c;
  ExceptionList = &local_10;
  uVar3 = 1;
  Getal(&local_15);
  uVar1 = allocate(uVar3);
  local_8 = 0;
  uVar2 = FUN_00417780(uVar1);
  Getal(&local_16);
  uVar3 = param_1;
  uVar2 = FUN_00417780(uVar2,param_1);
  construct<>(uVar2,uVar3);
  uVar2 = FUN_004242e0(uVar1);
  Getal(&local_17);
  uVar3 = param_1;
  uVar2 = FUN_00417780(uVar2,param_1);
  construct<>(uVar2,uVar3);
  uVar3 = FUN_004242f0(uVar1);
  Getal(&local_18);
  uVar3 = FUN_00417780(uVar3,param_1);
  construct<>(uVar3,param_1);
  FUN_004304fd();
  return;
}

