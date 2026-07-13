
bool __fastcall FUN_006aadf0(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_006aa1d0(param_1);
  if (iVar1 != 0) {
    piVar2 = (int *)FUN_006aa1d0(param_1);
    (**(code **)(*piVar2 + 0x70))("achievements");
  }
  return iVar1 != 0;
}

