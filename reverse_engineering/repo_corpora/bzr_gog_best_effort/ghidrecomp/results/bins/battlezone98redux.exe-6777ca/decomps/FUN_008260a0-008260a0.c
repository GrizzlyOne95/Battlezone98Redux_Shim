
bool __thiscall FUN_008260a0(undefined4 param_1,char *param_2,char *param_3)

{
  int iVar1;
  bool bVar2;
  
  if (((*param_3 == '?') || (*param_3 == '*')) && (*param_2 == '.')) {
    bVar2 = false;
  }
  else {
    iVar1 = FUN_00825e20(param_2,param_3,param_1);
    bVar2 = iVar1 == 1;
  }
  return bVar2;
}

