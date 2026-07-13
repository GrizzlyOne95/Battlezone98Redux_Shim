
undefined4 FUN_008138f0(undefined1 param_1,uint param_2,undefined4 param_3)

{
  char cVar1;
  
  if (param_2 < 8) {
    FUN_008140c0(param_3,param_1,0);
  }
  else {
    cVar1 = FUN_008140f0(param_3,param_1,0);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

