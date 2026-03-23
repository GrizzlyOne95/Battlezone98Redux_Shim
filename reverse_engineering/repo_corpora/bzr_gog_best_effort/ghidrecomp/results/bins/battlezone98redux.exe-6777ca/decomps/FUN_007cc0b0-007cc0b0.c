
undefined4 __thiscall FUN_007cc0b0(int param_1,int param_2,int param_3,int param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  cVar1 = FUN_007d2810((float)param_2,(float)param_3);
  if (((cVar1 == '\0') || (param_4 != 0)) || (*(char *)(param_1 + 0x144) == '\0')) {
    uVar2 = 0;
  }
  else {
    if (((float)param_2 < *(float *)(param_1 + 4) + *(float *)(param_1 + 0x158)) &&
       (*(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) - 1.0,
       *(float *)(param_1 + 0x150) <= 0.0 && *(float *)(param_1 + 0x150) != 0.0)) {
      *(undefined4 *)(param_1 + 0x150) = 0;
    }
    if (((*(float *)(param_1 + 4) + *(float *)(param_1 + 0xc)) - *(float *)(param_1 + 0x158) <
         (float)param_2) &&
       (*(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + 1.0,
       *(float *)(param_1 + 0x14c) <= *(float *)(param_1 + 0x150) &&
       *(float *)(param_1 + 0x150) != *(float *)(param_1 + 0x14c))) {
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x14c);
    }
    FUN_007cc230();
    *(undefined1 *)(param_1 + 0x144) = 0;
    if (*(int *)(param_1 + 0x160) != 0) {
      (**(code **)(param_1 + 0x160))();
    }
    uVar2 = 1;
  }
  return uVar2;
}

