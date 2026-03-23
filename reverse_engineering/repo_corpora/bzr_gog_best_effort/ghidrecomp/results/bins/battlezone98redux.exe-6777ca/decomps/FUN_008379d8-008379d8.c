
undefined4 FUN_008379d8(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  FUN_0082c82c(param_1,0xffffd8ef,"preload");
  iVar2 = FUN_0082d490(param_1,0xffffffff);
  if (iVar2 != 5) {
    FUN_0082bc39(param_1,"\'package.preload\' must be a table");
  }
  FUN_0082c82c(param_1,0xffffffff,uVar1);
  iVar2 = FUN_0082d490(param_1,0xffffffff);
  if (iVar2 == 0) {
    FUN_0082cc9e(param_1,"\n\tno field package.preload[\'%s\']",uVar1);
  }
  return 1;
}

