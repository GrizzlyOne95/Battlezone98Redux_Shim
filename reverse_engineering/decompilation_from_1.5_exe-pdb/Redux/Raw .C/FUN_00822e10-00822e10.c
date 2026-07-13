
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall FUN_00822e10(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_00822e60(param_1);
  if ((param_2 != 0) || (iVar2 = FUN_00572a60(), iVar2 != 0)) {
    if (DAT_008fe244 == 0) {
      iVar1 = iVar1 - _DAT_00946798;
    }
    else {
      iVar1 = iVar1 + _DAT_00946798;
    }
  }
  return iVar1;
}

