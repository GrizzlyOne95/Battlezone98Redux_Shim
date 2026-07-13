
undefined4 __thiscall FUN_0042ddb0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845378;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar2 = Getal(&local_13);
  allocator<>(uVar2);
  puVar4 = &local_11;
  uVar2 = FUN_00424670(&local_14);
  FUN_00428c80(uVar2,puVar4);
  local_8 = 0;
  local_12 = 0;
  uVar3 = 0;
  uVar2 = FUN_00417780(param_2,0,uVar1);
  FUN_004245e0(uVar2,uVar3);
  ExceptionList = local_10;
  return param_1;
}

