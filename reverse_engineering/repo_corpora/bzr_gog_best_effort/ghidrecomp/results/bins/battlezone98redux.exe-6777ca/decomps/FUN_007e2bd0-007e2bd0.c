
void __thiscall FUN_007e2bd0(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_007e6d40(param_2,param_1 + 2);
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1ba1;
  }
  return;
}

