
undefined4 * __thiscall FUN_00723e60(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 local_5;
  
  *param_1 = param_2;
  param_1[1] = param_3;
  cVar1 = FUN_00710380();
  if (cVar1 == '\0') {
    FUN_00718410(&local_5,&param_2);
  }
  return param_1;
}

