
void __fastcall FUN_00673140(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084ee80;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar3 = 1;
  FUN_004b4350(1);
  uVar1 = FUN_0066e550(uVar3);
  local_8 = 0;
  uVar2 = FUN_00417780(uVar1);
  FUN_004b4350();
  uVar3 = param_1;
  uVar2 = FUN_00417780(uVar2,param_1);
  construct<>(uVar2,uVar3);
  uVar2 = FUN_004242e0(uVar1);
  FUN_004b4350();
  uVar3 = param_1;
  uVar2 = FUN_00417780(uVar2,param_1);
  construct<>(uVar2,uVar3);
  uVar3 = FUN_004242f0(uVar1);
  FUN_004b4350();
  uVar3 = FUN_00417780(uVar3,param_1);
  construct<>(uVar3,param_1);
  FUN_00673249();
  return;
}

