
undefined4 * FUN_00837eff(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  
  FUN_0082cc9e(param_1,&DAT_0088d944,"LOADLIB: ",param_2);
  FUN_0082c8d1(param_1,0xffffd8f0);
  iVar1 = FUN_0082d490(param_1,0xffffffff);
  if (iVar1 == 0) {
    FUN_0082d226(param_1,0xfffffffe);
    puVar2 = (undefined4 *)FUN_0082cac6(param_1,4);
    *puVar2 = 0;
    FUN_0082c82c(param_1,0xffffd8f0,"_LOADLIB");
    FUN_0082d16f(param_1,0xfffffffe);
    FUN_0082cc9e(param_1,&DAT_0088d944,"LOADLIB: ",param_2);
    FUN_0082cdd2(param_1,0xfffffffe);
    FUN_0082d1fa(param_1,0xffffd8f0);
  }
  else {
    puVar2 = (undefined4 *)FUN_0082d465(param_1,0xffffffff);
  }
  return puVar2;
}

