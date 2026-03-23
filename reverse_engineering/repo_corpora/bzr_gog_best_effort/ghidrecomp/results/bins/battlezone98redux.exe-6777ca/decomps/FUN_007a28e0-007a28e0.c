
undefined4 __thiscall FUN_007a28e0(int param_1,char param_2)

{
  undefined4 uVar1;
  
  if (*(char *)(param_1 + 0x1fc) == '\0') {
    uVar1 = FUN_007cfa70(param_2);
  }
  else if (param_2 == '\r') {
    FUN_0079d850();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_007d0500(param_2);
  }
  return uVar1;
}

