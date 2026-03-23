
undefined4 FUN_0083784f(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  uVar2 = FUN_0082ba59(param_1,2,0);
  iVar3 = FUN_00837e92(param_1,uVar1,uVar2);
  if (iVar3 == 0) {
    uVar1 = 1;
  }
  else {
    FUN_0082cd45(param_1);
    FUN_0082c953(param_1,0xfffffffe);
    puVar4 = &DAT_008987d0;
    if (iVar3 != 1) {
      puVar4 = &DAT_0086ff84;
    }
    FUN_0082cd77(param_1,puVar4);
    uVar1 = 3;
  }
  return uVar1;
}

