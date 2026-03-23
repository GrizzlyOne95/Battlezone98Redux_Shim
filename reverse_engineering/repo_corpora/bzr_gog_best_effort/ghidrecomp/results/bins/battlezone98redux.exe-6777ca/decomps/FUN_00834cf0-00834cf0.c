
undefined4 FUN_00834cf0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int local_8;
  
  iVar1 = FUN_0082ba59(param_1,1,&local_8);
  uVar2 = FUN_0082ba1c(param_1,2,local_8);
  iVar3 = FUN_00835ff6(uVar2);
  uVar2 = FUN_0082c1fd(param_1,3,0xffffffff,local_8);
  iVar4 = FUN_00835ff6(uVar2);
  if (iVar3 < 1) {
    iVar3 = 1;
  }
  if (local_8 < iVar4) {
    iVar4 = local_8;
  }
  if (iVar4 < iVar3) {
    iVar4 = 0;
    puVar5 = &DAT_008a1ad8;
  }
  else {
    iVar4 = (iVar4 - iVar3) + 1;
    puVar5 = (undefined1 *)(iVar1 + -1 + iVar3);
  }
  FUN_0082cd08(param_1,puVar5,iVar4);
  return 1;
}

