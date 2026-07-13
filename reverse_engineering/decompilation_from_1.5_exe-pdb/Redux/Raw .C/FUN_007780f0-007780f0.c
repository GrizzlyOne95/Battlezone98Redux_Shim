
void __thiscall FUN_007780f0(int param_1,float param_2,float param_3,float param_4,float param_5)

{
  undefined4 local_10;
  undefined4 local_c;
  
  if ((((*(float *)(param_1 + 0x380) <= param_4) && (param_2 <= *(float *)(param_1 + 0x388))) &&
      (*(float *)(param_1 + 900) <= param_5)) && (param_3 <= *(float *)(param_1 + 0x38c))) {
    for (local_c = 0; local_c < 4; local_c = local_c + 1) {
      for (local_10 = 0; local_10 < 4; local_10 = local_10 + 1) {
        if (((*(float *)(param_1 + 0x280 + local_c * 0x40 + local_10 * 0x10) <= param_4) &&
            (param_2 <= *(float *)(param_1 + local_c * 0x40 + 0x288 + local_10 * 0x10))) &&
           ((*(float *)(param_1 + local_c * 0x40 + 0x284 + local_10 * 0x10) <= param_5 &&
            (param_3 <= *(float *)(param_1 + local_c * 0x40 + 0x28c + local_10 * 0x10))))) {
          *(undefined1 *)(param_1 + 0x250 + local_c * 4 + local_10) = 1;
        }
      }
    }
  }
  return;
}

