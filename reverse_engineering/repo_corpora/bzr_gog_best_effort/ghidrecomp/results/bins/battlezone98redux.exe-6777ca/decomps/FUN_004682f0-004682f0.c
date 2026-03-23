
undefined1 FUN_004682f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 uVar1;
  char cVar2;
  char cVar3;
  
  cVar2 = FUN_0048fca0(param_1,param_2);
  cVar3 = FUN_0048fca0(param_3,param_4);
  if (((cVar2 == '\0') || (cVar3 == '\0')) || (cVar2 != cVar3)) {
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

