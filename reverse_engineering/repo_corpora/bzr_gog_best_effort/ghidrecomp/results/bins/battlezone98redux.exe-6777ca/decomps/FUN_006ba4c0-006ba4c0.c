
undefined4 FUN_006ba4c0(undefined4 param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_006ba470(param_1);
  if (cVar1 == '~') {
    uVar2 = 2;
  }
  else {
    cVar1 = FUN_006ba470(param_1);
    if (cVar1 == '\x7f') {
      uVar2 = 8;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}

