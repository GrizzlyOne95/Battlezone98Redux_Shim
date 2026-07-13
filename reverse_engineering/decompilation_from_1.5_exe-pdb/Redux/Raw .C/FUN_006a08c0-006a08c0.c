
int __thiscall FUN_006a08c0(undefined4 param_1,double param_2)

{
  int iVar1;
  
  iVar1 = FUN_0046eaf0(param_2 * 0.2,param_1);
  if (iVar1 < DAT_00931018) {
    iVar1 = 0;
  }
  else if (iVar1 < DAT_009310ac) {
    iVar1 = iVar1 - DAT_00931018;
  }
  else {
    iVar1 = (DAT_009310ac - DAT_00931018) + -1;
  }
  return iVar1;
}

