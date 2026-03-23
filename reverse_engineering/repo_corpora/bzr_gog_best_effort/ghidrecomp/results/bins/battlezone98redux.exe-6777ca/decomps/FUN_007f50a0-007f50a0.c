
undefined1 __thiscall
FUN_007f50a0(undefined4 param_1,undefined4 param_2,undefined8 param_3,undefined1 param_4,
            undefined1 param_5)

{
  undefined1 uVar1;
  char cVar2;
  
  uVar1 = FUN_007f4fd0(param_3,param_4,param_5,param_5,param_1);
  cVar2 = FUN_007f2190(param_2,uVar1);
  if ((cVar2 != '\0') && (cVar2 = FUN_007f5ce0(param_2,param_3), cVar2 != '\0')) {
    return 1;
  }
  return 0;
}

