
undefined4
FUN_00467440(uint param_1,uint param_2,uint param_3,uint param_4,uint param_5,undefined4 param_6,
            undefined4 *param_7)

{
  undefined4 uVar1;
  float *pfVar2;
  uint local_14;
  uint local_c;
  uint local_8;
  
  if ((param_1 & param_2) == param_2) {
    if ((param_1 & param_3) == 0) {
      if (param_4 == 0xffffffff) {
        pfVar2 = (float *)FUN_004624b0();
        if ((param_5 == 0) || (param_5 == 2)) {
          if (*pfVar2 <= 0.0) {
            local_c = 3;
          }
          else {
            local_c = 1;
          }
          param_4 = local_c;
        }
        else {
          if (pfVar2[2] <= 0.0) {
            local_14 = 1;
          }
          else {
            local_14 = 3;
          }
          param_4 = local_14;
        }
        if ((param_5 == 3) || (param_5 == 2)) {
          param_4 = param_4 + 2 & 3;
        }
      }
      if (param_4 == 0) {
        local_8 = param_5;
      }
      else if (param_4 == 1) {
        local_8 = param_5 + 1;
      }
      else {
        local_8 = param_5 + 3;
      }
      switch(local_8 & 3) {
      case 0:
        *param_7 = 0;
        param_7[2] = 0x41a00000;
        break;
      case 1:
        *param_7 = 0x41a00000;
        param_7[2] = 0;
        break;
      case 2:
        *param_7 = 0;
        param_7[2] = 0xc1a00000;
        break;
      case 3:
        *param_7 = 0xc1a00000;
        param_7[2] = 0;
      }
      uVar1 = 1;
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

