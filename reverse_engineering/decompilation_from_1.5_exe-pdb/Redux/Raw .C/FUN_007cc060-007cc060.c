
undefined4 __thiscall FUN_007cc060(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_007d2810((float)param_2,(float)param_3);
  if ((cVar1 == '\0') || (param_4 != 0)) {
    uVar2 = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x144) = 1;
    uVar2 = 1;
  }
  return uVar2;
}

