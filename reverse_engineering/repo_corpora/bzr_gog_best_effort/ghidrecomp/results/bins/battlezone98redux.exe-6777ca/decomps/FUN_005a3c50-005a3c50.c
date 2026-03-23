
uint __thiscall FUN_005a3c50(int param_1,uint param_2)

{
  if (param_2 == 3) {
    param_2 = FUN_005a3b40(*(undefined4 *)(param_1 + 0x34));
    *(uint *)(param_1 + 0x80) = param_2;
    if (*(int *)(param_1 + 0x80) == 0) {
      param_2 = FUN_00583a50();
    }
    else {
      param_2 = param_2 & 0xffffff00;
    }
  }
  else if (param_2 == 0x10) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 & 0xffffff00;
  }
  return param_2;
}

