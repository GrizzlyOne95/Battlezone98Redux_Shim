
float10 __thiscall FUN_0069e200(int *param_1,int param_2)

{
  float10 fVar1;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  uint local_10;
  float local_c;
  
  if (((((param_1[0x14] == 0) && ((float)param_1[0x19] == 0.0)) && (param_1[0x17] == 0)) &&
      (((float)param_1[0x18] == 0.0 && (param_1[0x1a] == 0)))) &&
     ((*(int *)(*(int *)(*(int *)(param_1[0xf] + 0x88) + param_1[0x10] * 4) + param_1[0x11] * 4) !=
       1 && (*(int *)(*(int *)(*(int *)(param_1[0xf] + 0x90) + param_1[0x10] * 4) +
                     param_1[0x11] * 4) == 1)))) {
    fVar1 = (float10)-1e+09;
  }
  else {
    fVar1 = (float10)(**(code **)(*param_1 + 0x10))(param_2);
    if ((*(int *)(param_1[0xe] + 0x90) == 0) &&
       (*(int *)(*(int *)(*(int *)(param_1[0xf] + 0x90) + param_1[0x10] * 4) + param_1[0x11] * 4) ==
        0)) {
      local_24 = (uint)(*(int *)(param_2 + 0x28) != 0);
      local_20 = (uint)(*(int **)(param_2 + 0x28) != param_1);
      local_c = (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0xc) * (float)fVar1 +
                (float)(int)(-*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x1c) * local_20 * local_24)
                + (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x20);
    }
    else {
      local_10 = (uint)(*(int *)(*(int *)(*(int *)(param_1[0xf] + 0x90) + param_1[0x10] * 4) +
                                param_1[0x11] * 4) == 2);
      local_14 = (uint)(*(int *)(*(int *)(*(int *)(param_1[0xf] + 0x88) + param_1[0x10] * 4) +
                                param_1[0x11] * 4) == 1);
      local_1c = (uint)(*(int *)(param_2 + 0x28) != 0);
      local_18 = (uint)(*(int **)(param_2 + 0x28) != param_1);
      local_c = (float)(*(int *)(*(int *)(param_1[0xf] + 0x60) + 8) * param_1[0x12]) +
                (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0xc) * (float)fVar1 +
                (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x14) * (float)param_1[0x19] +
                (float)(*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x2c) * param_1[0x17]) +
                (float)*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x18) * (float)param_1[0x18] +
                (float)(int)(*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x20) * local_10) +
                (float)(*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x24) * param_1[0x1a]) +
                (float)(int)(*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x28) * local_14) +
                (float)(int)(-*(int *)(*(int *)(param_1[0xf] + 0x60) + 0x1c) * local_18 * local_1c);
    }
    if ((float)param_1[7] <= local_c && local_c != (float)param_1[7]) {
      param_1[7] = (int)local_c;
    }
    fVar1 = (float10)local_c;
  }
  return fVar1;
}

