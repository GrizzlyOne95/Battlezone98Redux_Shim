
uint __thiscall FUN_007f1d30(uint param_1,undefined4 param_2)

{
  if (*(char *)(param_1 + 0x14) == '\0') {
    param_1 = param_1 & 0xffffff00;
  }
  else {
    FUN_007f1bf0(param_2);
    FUN_007f2880(param_2);
    param_1 = FUN_007f28a0(param_2);
  }
  return param_1;
}

