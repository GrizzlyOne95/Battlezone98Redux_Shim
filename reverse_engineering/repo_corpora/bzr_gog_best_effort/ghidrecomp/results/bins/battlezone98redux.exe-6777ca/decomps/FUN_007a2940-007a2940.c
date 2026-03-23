
undefined4 __thiscall FUN_007a2940(int param_1,int param_2,undefined2 param_3)

{
  undefined4 uVar1;
  
  if (param_2 == 0x1b) {
    if (*(char *)(param_1 + 0x1fc) == '\0') {
      FUN_0079dd60();
    }
    else {
      FUN_0079d7e0();
    }
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_007d2490(param_2,param_3);
  }
  return uVar1;
}

