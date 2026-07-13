
undefined4 FUN_006991d0(char param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  if (param_1 == -1) {
    uVar1 = 3;
  }
  else {
    iVar2 = isalnum((int)param_1);
    if (((iVar2 == 0) && (param_1 != '.')) && (param_1 != '_')) {
      iVar2 = isspace((int)param_1);
      if (((iVar2 == 0) && (iVar2 = isgraph((int)param_1), iVar2 != 0)) && (param_1 != '\r')) {
        return 2;
      }
      uVar1 = 0;
    }
    else {
      uVar1 = 1;
    }
  }
  return uVar1;
}

