
undefined4 __thiscall FUN_007d7480(undefined4 param_1,double param_2)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_007d9780(param_2,param_1);
  if (cVar1 == '\0') {
    floor(param_2);
    uVar2 = FUN_0083f040();
  }
  else {
    ceil(param_2);
    uVar2 = FUN_0083f040();
  }
  return uVar2;
}

