
void __thiscall FUN_004c3780(int param_1,undefined4 param_2)

{
  int local_18;
  int local_10;
  uint local_c;
  
  local_c = (uint)(DAT_00919850 != '\0');
  if (DAT_00919851 != '\0') {
    local_c = 0xffffffff;
  }
  switch(param_2) {
  case 0xd:
    *(uint *)(param_1 + 0xec) = *(int *)(param_1 + 0xec) + local_c;
    if (*(int *)(param_1 + 0xec) < 0) {
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    if (0x3f < *(int *)(param_1 + 0xec)) {
      *(undefined4 *)(param_1 + 0xec) = 0x3f;
    }
    break;
  case 0xe:
    if (DAT_00919852 == '\0') {
      *(float *)(param_1 + 0xf4) = (float)(int)local_c + *(float *)(param_1 + 0xf4);
    }
    else {
      *(float *)(param_1 + 0xf4) = (float)(int)(local_c * 10) + *(float *)(param_1 + 0xf4);
    }
    if (*(float *)(param_1 + 0xf4) <= 0.0 && *(float *)(param_1 + 0xf4) != 0.0) {
      *(undefined4 *)(param_1 + 0xf4) = 0;
    }
    if (DAT_00992364 < *(float *)(param_1 + 0xf4)) {
      *(float *)(param_1 + 0xf4) = DAT_00992364;
    }
    break;
  case 0xf:
    local_18 = 1;
    for (local_10 = 1; local_10 < 7; local_10 = local_10 + 1) {
      if (*(float *)(param_1 + 0xf8) <= *(float *)(&DAT_008e8180 + local_10 * 4)) {
        local_18 = local_10 + local_c;
        break;
      }
    }
    *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(&DAT_008e8180 + local_18 * 4);
    break;
  case 0x13:
    *(uint *)(param_1 + 0xf0) = *(int *)(param_1 + 0xf0) + local_c;
    if (*(int *)(param_1 + 0xf0) < 0) {
      *(undefined4 *)(param_1 + 0xf0) = 0;
    }
    if (0x3f < *(int *)(param_1 + 0xf0)) {
      *(undefined4 *)(param_1 + 0xf0) = 0x3f;
    }
    break;
  case 0x14:
    *(float *)(param_1 + 0xfc) = (float)(int)local_c * 0.05 + *(float *)(param_1 + 0xfc);
    if (*(float *)(param_1 + 0xfc) <= 0.05 && *(float *)(param_1 + 0xfc) != 0.05) {
      *(undefined4 *)(param_1 + 0xfc) = 0x3d4ccccd;
    }
    if (1.0 < *(float *)(param_1 + 0xfc)) {
      *(undefined4 *)(param_1 + 0xfc) = 0x3f800000;
    }
  }
  return;
}

