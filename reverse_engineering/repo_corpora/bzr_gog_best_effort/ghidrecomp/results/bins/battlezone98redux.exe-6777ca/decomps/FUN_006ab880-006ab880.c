
int * __thiscall FUN_006ab880(int *param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if (iVar1 != *param_1) {
    if (iVar1 != 0) {
      FUN_006ab4f0();
    }
    if (*param_1 != 0) {
      Decwref();
    }
    *param_1 = iVar1;
  }
  return param_1;
}

