
undefined1
FUN_00810ad0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            char param_5,char param_6)

{
  char cVar1;
  undefined4 extraout_var;
  
  cVar1 = FID_conflict_operator__(param_2);
  if (cVar1 != '\0') {
    return 0;
  }
  if (((param_5 == '\0') ||
      (cVar1 = FUN_00811eb0(param_1,param_2,param_3,extraout_var), cVar1 == '\0')) &&
     ((param_6 != '\0' || (cVar1 = FUN_00811f00(param_1,param_2,param_3), cVar1 == '\0')))) {
    return 0;
  }
  return 1;
}

