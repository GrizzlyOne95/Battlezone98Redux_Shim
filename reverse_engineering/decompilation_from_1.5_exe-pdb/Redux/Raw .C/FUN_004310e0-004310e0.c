
undefined4 FUN_004310e0(char *param_1)

{
  char cVar1;
  undefined4 uVar2;
  
  if (*param_1 == '\0') {
    uVar2 = 0;
  }
  else {
    cVar1 = FUN_004323c0(*param_1);
    if (cVar1 == '\0') {
      for (; *param_1 != '\0'; param_1 = param_1 + 1) {
        cVar1 = FUN_00432e00(*param_1);
        if (cVar1 != '\0') {
          return 1;
        }
      }
      cVar1 = FUN_004323c0(param_1[-1]);
      if (cVar1 == '\0') {
        uVar2 = 0;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 1;
    }
  }
  return uVar2;
}

