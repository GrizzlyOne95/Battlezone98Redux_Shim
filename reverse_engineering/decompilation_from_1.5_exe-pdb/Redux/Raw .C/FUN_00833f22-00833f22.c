
undefined4 FUN_00833f22(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_0082ca93(param_1);
  iVar2 = FUN_0082d490(param_1,1);
  if (iVar2 == 6) {
    iVar2 = FUN_0082c99e(param_1,1);
    if (iVar2 == 0) goto LAB_00833f61;
  }
  FUN_0082b8e4(param_1,1,"Lua function expected");
LAB_00833f61:
  FUN_0082cdd2(param_1,1);
  FUN_0082d4cc(param_1,uVar1,1);
  return 1;
}

