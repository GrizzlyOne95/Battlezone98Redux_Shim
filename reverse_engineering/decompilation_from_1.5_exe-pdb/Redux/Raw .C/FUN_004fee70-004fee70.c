
undefined4 __thiscall FUN_004fee70(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  
  cVar1 = FUN_004feed0(param_2);
  if (cVar1 == '\0') {
    iVar2 = FUN_00840de0();
    FUN_0042a3e0(param_2,param_1);
    if (iVar2 != 0) {
      FUN_00840e30(iVar2);
    }
  }
  return param_1;
}

