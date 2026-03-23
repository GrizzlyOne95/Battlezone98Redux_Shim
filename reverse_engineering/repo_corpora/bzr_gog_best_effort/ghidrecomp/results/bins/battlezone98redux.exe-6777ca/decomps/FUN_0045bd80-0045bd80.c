
undefined4 __thiscall FUN_0045bd80(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (DAT_00978fa8 < 1) {
    iVar3 = FUN_004a7370(param_1);
    if (iVar3 == 0) {
      uVar2 = 0;
    }
    else if (iVar3 == 1) {
      uVar2 = 3;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    piVar1 = (int *)FUN_004da060(DAT_00978e3c);
    uVar2 = (**(code **)(*piVar1 + 0x30))(param_2);
  }
  return uVar2;
}

