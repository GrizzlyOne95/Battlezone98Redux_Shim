
undefined4 __thiscall FUN_0073bca0(int *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = FUN_0073a900();
  if (cVar1 == '\0') {
    FUN_0073a6b0();
  }
  else {
    (**(code **)(*param_1 + 0x68))(param_2,param_3);
  }
  return param_2;
}

