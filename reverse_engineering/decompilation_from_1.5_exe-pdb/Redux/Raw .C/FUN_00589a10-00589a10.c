
undefined4
FUN_00589a10(undefined4 param_1,undefined4 param_2,char *param_3,int param_4,char *param_5)

{
  char *_Source;
  undefined4 uVar1;
  
  _Source = (char *)FUN_00589620(param_1,param_2);
  if (_Source == (char *)0x0) {
    if (param_3 != (char *)0x0) {
      if (param_5 == (char *)0x0) {
        *param_3 = '\0';
      }
      else {
        strncpy(param_3,param_5,param_4 - 1);
        param_3[param_4 + -1] = '\0';
      }
    }
    uVar1 = 0;
  }
  else {
    if (param_3 != (char *)0x0) {
      strncpy(param_3,_Source,param_4 - 1);
      param_3[param_4 + -1] = '\0';
    }
    uVar1 = 1;
  }
  return uVar1;
}

