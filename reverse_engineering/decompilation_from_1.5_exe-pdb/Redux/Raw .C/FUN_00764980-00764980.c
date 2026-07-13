
undefined4 __fastcall FUN_00764980(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_00915568 == 0) {
    if ((DAT_00945463 == '\0') || (iVar2 = FUN_006aa1d0(param_1), iVar2 == 0)) {
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

