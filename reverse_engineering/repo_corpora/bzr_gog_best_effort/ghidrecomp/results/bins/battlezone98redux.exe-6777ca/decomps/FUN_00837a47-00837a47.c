
undefined4 FUN_00837a47(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar5 = 1;
  uVar1 = FUN_0082ba59(param_1,1,0);
  FUN_0082d226(param_1,1);
  FUN_0082c82c(param_1,0xffffd8f0,"_LOADED");
  FUN_0082c82c(param_1,2,uVar1);
  iVar2 = FUN_0082d2e8(param_1,0xffffffff);
  if (iVar2 == 0) {
    FUN_0082c82c(param_1,0xffffd8ef,"loaders");
    iVar2 = FUN_0082d490(param_1,0xffffffff);
    if (iVar2 != 5) {
      FUN_0082bc39(param_1,"\'package.loaders\' must be a table");
    }
    FUN_0082cd08(param_1,&DAT_008a1ad8,0);
    while( true ) {
      FUN_0082ce9d(param_1,0xfffffffe,iVar5);
      iVar2 = FUN_0082d490(param_1,0xffffffff);
      if (iVar2 == 0) {
        uVar4 = FUN_0082d377(param_1,0xfffffffe,0);
        FUN_0082bc39(param_1,"module \'%s\' not found:%s",uVar1,uVar4);
      }
      FUN_0082cd77(param_1,uVar1);
      FUN_0082c585(param_1,1,1);
      iVar2 = FUN_0082d490(param_1,0xffffffff);
      if (iVar2 == 6) break;
      iVar2 = FUN_0082c9f5(param_1,0xffffffff);
      if (iVar2 == 0) {
        FUN_0082d226(param_1,0xfffffffe);
      }
      else {
        FUN_0082c61c(param_1,2);
      }
      iVar5 = iVar5 + 1;
    }
    FUN_0082cced(param_1,&DAT_0086fecc);
    FUN_0082d102(param_1,2,uVar1);
    FUN_0082cd77(param_1,uVar1);
    FUN_0082c585(param_1,1,1);
    iVar2 = FUN_0082d490(param_1,0xffffffff);
    if (iVar2 != 0) {
      FUN_0082d102(param_1,2,uVar1);
    }
    FUN_0082c82c(param_1,2,uVar1);
    puVar3 = (undefined *)FUN_0082d465(param_1,0xffffffff);
    if (puVar3 == &DAT_0086fecc) {
      FUN_0082cbf5(param_1,1);
      FUN_0082cdd2(param_1,0xffffffff);
      FUN_0082d102(param_1,2,uVar1);
    }
  }
  else {
    puVar3 = (undefined *)FUN_0082d465(param_1,0xffffffff);
    if (puVar3 == &DAT_0086fecc) {
      FUN_0082bc39(param_1,"loop or previous error loading module \'%s\'",uVar1);
    }
  }
  return 1;
}

