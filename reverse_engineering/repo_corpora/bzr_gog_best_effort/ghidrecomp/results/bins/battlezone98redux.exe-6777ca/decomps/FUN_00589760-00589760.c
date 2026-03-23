
undefined4
FUN_00589760(undefined4 param_1,undefined4 param_2,undefined4 *param_3,undefined4 param_4)

{
  char *_Src;
  undefined4 uVar1;
  undefined4 extraout_var;
  
  _Src = (char *)FUN_00589620(param_1,param_2);
  if (_Src == (char *)0x0) {
    if (param_3 != (undefined4 *)0x0) {
      *param_3 = param_4;
    }
    uVar1 = 0;
  }
  else {
    if (param_3 != (undefined4 *)0x0) {
      if ((*_Src == '0') && (_Src[1] == 'x')) {
        sscanf(_Src + 2,"%lx",param_3,extraout_var);
      }
      else {
        sscanf(_Src,"%ld",param_3,extraout_var);
      }
    }
    uVar1 = 1;
  }
  return uVar1;
}

