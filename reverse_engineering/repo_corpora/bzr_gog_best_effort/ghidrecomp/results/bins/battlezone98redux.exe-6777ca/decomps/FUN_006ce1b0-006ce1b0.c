
undefined4 FUN_006ce1b0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_006d1e40(param_1);
  if (cVar1 == '\0') {
    cVar1 = FUN_006d1dc0(param_1);
    if (cVar1 == '\0') {
      cVar1 = FUN_006d1e00(param_1);
      if (cVar1 == '\0') {
        uVar2 = 5;
      }
      else {
        uVar2 = 2;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

