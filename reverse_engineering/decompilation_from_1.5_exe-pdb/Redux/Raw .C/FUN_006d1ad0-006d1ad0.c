
undefined4 FUN_006d1ad0(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_006d5320(param_1,param_2);
  if (cVar1 == '\0') {
    cVar1 = FUN_006d5280(param_1,param_2);
    if (cVar1 == '\0') {
      cVar1 = FUN_006d52d0(param_1,param_2);
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

