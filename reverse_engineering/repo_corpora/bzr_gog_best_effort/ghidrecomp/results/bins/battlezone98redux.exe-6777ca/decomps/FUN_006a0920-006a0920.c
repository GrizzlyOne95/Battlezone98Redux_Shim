
int __thiscall FUN_006a0920(undefined4 param_1,double param_2)

{
  int iVar1;
  
  iVar1 = FUN_0046eaf0(param_2 * 0.2,param_1);
  if (iVar1 < DAT_00931020) {
    iVar1 = 0;
  }
  else if (iVar1 < DAT_00931024) {
    iVar1 = iVar1 - DAT_00931020;
  }
  else {
    iVar1 = (DAT_00931024 - DAT_00931020) + -1;
  }
  return iVar1;
}

