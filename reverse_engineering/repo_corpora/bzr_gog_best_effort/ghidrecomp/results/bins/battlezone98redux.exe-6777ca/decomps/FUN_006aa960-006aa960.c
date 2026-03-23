
uint __fastcall FUN_006aa960(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  undefined4 *puVar4;
  
  iVar1 = FUN_006aa210(param_1);
  if ((iVar1 != 0) && (iVar1 = FUN_006aa1b0(), iVar1 != 0)) {
    piVar2 = (int *)FUN_006aa1b0();
    uVar3 = (**(code **)(*piVar2 + 4))();
    if ((uVar3 & 0xff) == 0) {
      return uVar3 & 0xffffff00;
    }
    puVar4 = (undefined4 *)FUN_006aa210(param_1);
    uVar3 = (**(code **)*puVar4)();
    return uVar3;
  }
  return 0;
}

