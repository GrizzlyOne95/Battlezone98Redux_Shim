
bool __thiscall FUN_00449db0(int *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = FUN_00448b70(param_1 + 1);
  if (iVar1 == param_2) {
    *param_1 = *param_1 + 1;
  }
  return iVar1 == param_2;
}

