
undefined1 __thiscall FUN_005bf8d0(undefined4 param_1,int *param_2)

{
  char cVar1;
  
  cVar1 = (**(code **)(*param_2 + 0x68))(param_1);
  if ((cVar1 == '\0') && (cVar1 = (**(code **)(*param_2 + 0x6c))(), cVar1 == '\0')) {
    return 1;
  }
  return 0;
}

