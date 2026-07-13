
void __thiscall FUN_0077c750(int param_1,undefined4 param_2)

{
  char cVar1;
  int local_10;
  int local_c;
  
  cVar1 = FUN_0067ba10("DeviceLost",param_2);
  if (cVar1 == '\0') {
    cVar1 = FUN_0067ba10("DeviceRestored",param_2);
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 0x14) = 1;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x14) = 0;
    if (*(int *)(param_1 + 0x44) != 0) {
      for (local_c = 0; local_c < (int)*(float *)(param_1 + 0x48); local_c = local_c + 1) {
        for (local_10 = 0; local_10 < (int)*(float *)(param_1 + 0x4c); local_10 = local_10 + 1) {
          if (*(int *)(*(int *)(param_1 + 0x44) +
                      ((int)*(float *)(param_1 + 0x4c) * local_c + local_10) * 4) != 0) {
            FUN_00778230();
          }
        }
      }
    }
  }
  return;
}

