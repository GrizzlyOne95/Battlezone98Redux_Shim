
undefined4 FUN_00442fd0(float *param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*param_1 < *(float *)(param_2 + 0x50) || *param_1 == *(float *)(param_2 + 0x50)) {
    if (*(float *)(param_2 + 0x44) < param_1[3] || *(float *)(param_2 + 0x44) == param_1[3]) {
      if (param_1[1] < *(float *)(param_2 + 0x54) || param_1[1] == *(float *)(param_2 + 0x54)) {
        if (*(float *)(param_2 + 0x48) < param_1[4] || *(float *)(param_2 + 0x48) == param_1[4]) {
          if (param_1[2] < *(float *)(param_2 + 0x58) || param_1[2] == *(float *)(param_2 + 0x58)) {
            if (*(float *)(param_2 + 0x4c) < param_1[5] || *(float *)(param_2 + 0x4c) == param_1[5])
            {
              uVar1 = 1;
            }
            else {
              uVar1 = 0;
            }
          }
          else {
            uVar1 = 0;
          }
        }
        else {
          uVar1 = 0;
        }
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

