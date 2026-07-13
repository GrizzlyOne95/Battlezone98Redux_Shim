
undefined4 FUN_005ce6e0(undefined4 param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  piVar1 = (int *)FUN_00462630(param_1);
  if (piVar1 == (int *)0x0) {
    uVar2 = 0;
  }
  else {
    iVar3 = FUN_0046d060();
    iVar4 = FUN_00417c80();
    if (iVar3 - iVar4 < 1) {
      uVar2 = 0;
    }
    else {
      (**(code **)(*piVar1 + 0x18))(iVar3 - iVar4);
      uVar2 = 1;
    }
  }
  return uVar2;
}

