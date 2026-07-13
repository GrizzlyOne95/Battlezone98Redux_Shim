
undefined4 FUN_00837be8(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  iVar2 = FUN_0082c8f6(param_1);
  FUN_0082c82c(param_1,0xffffd8f0,"_LOADED");
  FUN_0082c82c(param_1,iVar2 + 1,uVar1);
  iVar3 = FUN_0082d490(param_1,0xffffffff);
  if (iVar3 != 5) {
    FUN_0082d226(param_1,0xfffffffe);
    iVar3 = FUN_0082bc6c(param_1,0xffffd8ee,uVar1,1);
    if (iVar3 != 0) {
      uVar1 = FUN_0082bc39(param_1,"name conflict for module \'%s\'",uVar1);
      return uVar1;
    }
    FUN_0082cdd2(param_1,0xffffffff);
    FUN_0082d102(param_1,iVar2 + 1,uVar1);
  }
  FUN_0082c82c(param_1,0xffffffff,"_NAME");
  iVar3 = FUN_0082d490(param_1,0xffffffff);
  if (iVar3 == 0) {
    FUN_0082d226(param_1,0xfffffffe);
    FUN_00838159(param_1,uVar1);
  }
  else {
    FUN_0082d226(param_1,0xfffffffe);
  }
  FUN_0082cdd2(param_1,0xffffffff);
  FUN_00838231(param_1);
  iVar3 = 2;
  if (1 < iVar2) {
    do {
      FUN_0082cdd2(param_1,iVar3);
      FUN_0082cdd2(param_1,0xfffffffe);
      FUN_0082c585(param_1,1,0);
      iVar3 = iVar3 + 1;
    } while (iVar3 <= iVar2);
  }
  return 0;
}

