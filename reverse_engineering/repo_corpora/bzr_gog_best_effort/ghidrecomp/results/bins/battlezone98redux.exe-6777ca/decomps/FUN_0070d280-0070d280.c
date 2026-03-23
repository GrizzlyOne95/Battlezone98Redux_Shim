
undefined4 __thiscall
FUN_0070d280(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008550e8;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00417780(param_5,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  uVar2 = FUN_00417780(param_4,uVar1);
  uVar3 = FUN_00417780(param_3,uVar2);
  FUN_0070cac0(uVar3,uVar2,uVar1);
  local_8 = 0;
  uVar1 = FUN_00417780(param_2);
  FUN_00717250(uVar1);
  ExceptionList = local_10;
  return param_1;
}

