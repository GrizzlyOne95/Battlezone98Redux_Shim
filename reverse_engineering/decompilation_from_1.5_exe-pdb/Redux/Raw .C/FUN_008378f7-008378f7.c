
undefined4 FUN_008378f7(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  uVar1 = FUN_0082ba59(param_1,1,0);
  iVar2 = FUN_00837d46(param_1,uVar1,"cpath");
  if (iVar2 != 0) {
    uVar1 = FUN_0083810b(param_1,uVar1);
    iVar3 = FUN_00837e92(param_1,iVar2,uVar1);
    if (iVar3 != 0) {
      FUN_00837f99(param_1,iVar2);
    }
  }
  return 1;
}

