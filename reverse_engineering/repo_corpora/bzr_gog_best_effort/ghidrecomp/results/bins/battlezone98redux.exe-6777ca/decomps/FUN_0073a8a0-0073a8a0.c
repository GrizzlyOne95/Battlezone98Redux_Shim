
undefined1 __fastcall FUN_0073a8a0(int *param_1)

{
  undefined8 uVar1;
  
  if (*param_1 == 2) {
    uVar1 = FUN_006c94e0();
    if ((param_1[2] == (int)uVar1) && (param_1[3] == (int)((ulonglong)uVar1 >> 0x20))) {
      return 1;
    }
  }
  return 0;
}

