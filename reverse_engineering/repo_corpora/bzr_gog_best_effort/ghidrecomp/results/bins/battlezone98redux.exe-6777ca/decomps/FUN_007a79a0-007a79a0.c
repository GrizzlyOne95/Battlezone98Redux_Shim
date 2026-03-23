
undefined4 __thiscall FUN_007a79a0(int param_1,int param_2,undefined2 param_3)

{
  char cVar1;
  undefined4 uVar2;
  
  if (((param_2 == 0x1b) && (*(char *)(param_1 + 0x144) != '\0')) &&
     (cVar1 = FUN_007d3360(), cVar1 != '\0')) {
    FUN_007a6ae0();
    return 1;
  }
  uVar2 = FUN_007d2490(param_2,param_3);
  return uVar2;
}

