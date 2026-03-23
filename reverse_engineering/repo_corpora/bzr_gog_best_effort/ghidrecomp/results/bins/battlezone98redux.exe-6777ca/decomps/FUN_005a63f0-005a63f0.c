
void __thiscall FUN_005a63f0(int param_1,undefined4 param_2,undefined4 param_3)

{
  FUN_004e7d10(param_2,param_3);
  if (*(short *)(param_1 + 0x7c) != 0) {
    DAT_00918130 = DAT_00918130 + 1;
    *(short *)(param_1 + 0x7e) = DAT_00918130;
  }
  return;
}

