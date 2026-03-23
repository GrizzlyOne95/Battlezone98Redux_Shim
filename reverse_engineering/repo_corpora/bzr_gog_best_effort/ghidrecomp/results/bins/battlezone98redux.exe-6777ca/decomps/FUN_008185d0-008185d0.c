
undefined4 FUN_008185d0(undefined1 param_1,uint param_2,undefined4 param_3)

{
  char cVar1;
  
  if (param_2 < 7) {
    FUN_00818630(param_3,param_1,0);
  }
  else {
    cVar1 = FUN_00818660(param_3,param_1,0);
    if (cVar1 == '\0') {
      return 0;
    }
  }
  return 1;
}

