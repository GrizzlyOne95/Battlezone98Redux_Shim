
undefined1 FUN_007f5680(undefined4 param_1,undefined4 param_2,undefined1 *param_3)

{
  char cVar1;
  undefined1 local_5;
  
  local_5 = 10;
  cVar1 = FUN_007f5ff0(param_1,&local_5);
  if ((cVar1 != '\0') && (cVar1 = operator==<>(param_1,*param_3), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

