
undefined4 FUN_00446460(char *param_1,undefined4 param_2)

{
  int iVar1;
  char *local_8;
  
  if (param_1 == (char *)0x0) {
    param_2 = 0;
  }
  else {
    for (local_8 = param_1; *local_8 != '\0'; local_8 = local_8 + 1) {
      iVar1 = tolower((int)*local_8);
      param_2 = FUN_00446440(iVar1,param_2);
    }
  }
  return param_2;
}

