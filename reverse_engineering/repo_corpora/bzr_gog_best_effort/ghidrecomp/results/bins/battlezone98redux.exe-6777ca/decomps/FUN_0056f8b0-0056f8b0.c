
undefined4 __thiscall FUN_0056f8b0(int *param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_0073a900();
  if (cVar1 == '\0') {
    FUN_0073a6b0();
  }
  else {
    (**(code **)(*param_1 + 0x68))(param_2,param_1 + 10);
  }
  return param_2;
}

