
undefined4 FUN_00442f40(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(float *)(param_1 + 0x44) < *(float *)(param_2 + 0x50) ||
      *(float *)(param_1 + 0x44) == *(float *)(param_2 + 0x50)) {
    if (*(float *)(param_2 + 0x44) < *(float *)(param_1 + 0x50) ||
        *(float *)(param_2 + 0x44) == *(float *)(param_1 + 0x50)) {
      if (*(float *)(param_1 + 0x4c) < *(float *)(param_2 + 0x58) ||
          *(float *)(param_1 + 0x4c) == *(float *)(param_2 + 0x58)) {
        if (*(float *)(param_2 + 0x4c) < *(float *)(param_1 + 0x58) ||
            *(float *)(param_2 + 0x4c) == *(float *)(param_1 + 0x58)) {
          if (*(float *)(param_1 + 0x48) < *(float *)(param_2 + 0x54) ||
              *(float *)(param_1 + 0x48) == *(float *)(param_2 + 0x54)) {
            if (*(float *)(param_2 + 0x48) < *(float *)(param_1 + 0x54) ||
                *(float *)(param_2 + 0x48) == *(float *)(param_1 + 0x54)) {
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

