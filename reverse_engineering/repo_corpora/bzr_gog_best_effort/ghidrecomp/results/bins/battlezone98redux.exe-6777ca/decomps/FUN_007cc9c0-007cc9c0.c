
undefined4 __thiscall FUN_007cc9c0(int param_1,int param_2,int param_3)

{
  char cVar1;
  
  if (((*(char *)(param_1 + 0x92c) != '\0') && ((*(uint *)(param_1 + 0x14) & 0x400) != 0)) &&
     (cVar1 = FUN_007d2810((float)param_2,(float)param_3), cVar1 != '\0')) {
    *(undefined1 *)(param_1 + 0x92d) = 1;
    return 1;
  }
  return 0;
}

