
undefined4 FUN_00833da3(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  FUN_0082b9f2(param_1,1);
  iVar1 = FUN_0082b9a1(param_1,1,"__tostring");
  if (iVar1 == 0) {
    iVar1 = FUN_0082d490(param_1,1);
    if (iVar1 == 0) {
      FUN_0082cd08(param_1,&PTR_LAB_0087d0ec,3);
    }
    else if (iVar1 == 1) {
      iVar1 = FUN_0082d2e8(param_1,1);
      pcVar3 = "true";
      if (iVar1 == 0) {
        pcVar3 = "false";
      }
      FUN_0082cd77(param_1,pcVar3);
    }
    else if (iVar1 == 3) {
      uVar2 = FUN_0082d377(param_1,1,0);
      FUN_0082cd77(param_1,uVar2);
    }
    else if (iVar1 == 4) {
      FUN_0082cdd2(param_1,1);
    }
    else {
      uVar2 = FUN_0082d414();
      uVar2 = FUN_0082d490(param_1,1,uVar2);
      uVar2 = FUN_0082d4b1(param_1,uVar2);
      FUN_0082cc9e(param_1,"%s: %p",uVar2);
    }
  }
  return 1;
}

