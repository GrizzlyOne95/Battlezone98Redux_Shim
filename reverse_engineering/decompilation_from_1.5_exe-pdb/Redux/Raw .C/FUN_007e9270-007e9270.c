
undefined1
FUN_007e9270(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  uVar2 = FUN_006b0020(param_3);
  cVar1 = FUN_007eaa50(param_1,param_2,uVar2,param_4);
  if ((cVar1 != '\0') && (cVar1 = operator==<>(param_1,*param_3), cVar1 != '\0')) {
    return 1;
  }
  return 0;
}

