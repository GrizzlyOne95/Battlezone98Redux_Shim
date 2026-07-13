
int __thiscall FUN_00816070(undefined4 param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_006d6730(&param_2,param_1);
  while (iVar1 != 0) {
    param_2 = iVar1;
    iVar1 = FUN_006d6730(&param_2);
  }
  return param_2;
}

