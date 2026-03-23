
void __thiscall FUN_007d3480(int param_1,float param_2,float param_3,char param_4)

{
  float fVar1;
  undefined1 local_24 [4];
  undefined1 local_20 [4];
  undefined1 local_1c [4];
  undefined1 local_18 [4];
  int local_14 [3];
  int local_8;
  
  local_8 = param_1;
  if ((param_2 != -1.0) && (*(float *)(param_1 + 4) = param_2, param_4 == '\0')) {
    if ((*(uint *)(param_1 + 0x14) & 0x40) == 0) {
      if ((*(uint *)(param_1 + 0x14) & 0x80) == 0) {
        if ((*(uint *)(param_1 + 0x14) & 0x20) == 0) {
          *(float *)(param_1 + 4) = *(float *)(param_1 + 4) * *(float *)(param_1 + 0x18);
        }
        else {
          *(float *)(param_1 + 4) = *(float *)(param_1 + 4) * *(float *)(param_1 + 0x1c);
        }
      }
      else {
        (**(code **)(**(int **)(DAT_00920ea0 + 0xc) + 0x148))
                  (local_14,local_24,local_20,local_1c,local_18);
        fVar1 = (float)((double)local_14[0] + (double)(&DAT_008a2fd0)[-(local_14[0] >> 0x1f)]) /
                1920.0;
        if ((*(uint *)(local_8 + 0x14) & 0x20) == 0) {
          *(float *)(local_8 + 4) = (1920.0 - *(float *)(local_8 + 0xf4)) * fVar1;
        }
        else {
          *(float *)(local_8 + 4) = (1920.0 - *(float *)(local_8 + 0xf4)) * fVar1;
        }
      }
    }
    else {
      *(float *)(param_1 + 4) = *(float *)(param_1 + 0x18) * 720.0;
      *(float *)(param_1 + 4) = *(float *)(param_1 + 4) - *(float *)(param_1 + 0xc) / 2.0;
    }
  }
  if ((param_3 != -1.0) && (*(float *)(local_8 + 8) = param_3, param_4 == '\0')) {
    *(float *)(local_8 + 8) = *(float *)(local_8 + 8) * *(float *)(local_8 + 0x1c);
  }
  return;
}

