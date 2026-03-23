
undefined1 __thiscall
FUN_007f3200(undefined4 param_1,undefined4 param_2,undefined8 param_3,undefined1 param_4)

{
  undefined1 uVar1;
  char cVar2;
  
  uVar1 = FUN_007d9780(param_3,param_4,0,param_1);
  cVar2 = FUN_007f2190(param_2,0,uVar1);
  if ((cVar2 != '\0') && (cVar2 = FUN_007f3e00(param_2,&DAT_008a1b2c), cVar2 != '\0')) {
    return 1;
  }
  return 0;
}

