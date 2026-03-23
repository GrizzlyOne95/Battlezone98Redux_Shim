
uint __fastcall FUN_00608490(uint param_1)

{
  if (*(int *)(param_1 + 0x10) == 0) {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    param_1 = FUN_004aef60();
  }
  return param_1;
}

