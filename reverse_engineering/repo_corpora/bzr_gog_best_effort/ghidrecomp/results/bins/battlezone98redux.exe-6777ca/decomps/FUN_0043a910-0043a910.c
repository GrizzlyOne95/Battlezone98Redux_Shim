
void FUN_0043a910(uint param_1,uint param_2,uint param_3)

{
  if (param_1 == 0xffffffff) {
    param_1 = FUN_004376b0();
    param_1 = param_1 & 0xff;
  }
  if (param_2 == 0xffffffff) {
    param_2 = FUN_00439e40();
    param_2 = param_2 & 0xff;
  }
  if (param_3 == 0xffffffff) {
    param_3 = FUN_00439e50();
    param_3 = param_3 & 0xff;
  }
  if (param_1 != 0xfffffffe) {
    FUN_00437800(param_1);
  }
  if (DAT_00915594 != 0) {
    if (param_2 != 0xfffffffe) {
      *(uint *)(DAT_00915594 + 8) = param_2;
    }
    if (param_3 != 0xfffffffe) {
      *(uint *)(DAT_00915594 + 0xc) = param_3;
    }
  }
  return;
}

