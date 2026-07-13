
void FUN_00676070(undefined4 param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined4 uVar3;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084efb0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  uVar1 = FUN_00672fc0();
  puVar2 = (undefined1 *)FUN_00425000(uVar1);
  *puVar2 = 0;
  puVar2 = (undefined1 *)FUN_004242d0(uVar1);
  *puVar2 = 0;
  local_8 = 0;
  uVar3 = FUN_00417780(param_1);
  uVar1 = FUN_00424300(uVar1);
  FUN_004b4350();
  uVar1 = FUN_00417780(uVar1,uVar3);
  construct<>(uVar1,uVar3);
  FUN_0067612e();
  return;
}

