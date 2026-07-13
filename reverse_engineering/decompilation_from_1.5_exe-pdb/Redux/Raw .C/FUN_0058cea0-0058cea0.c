
undefined4 FUN_0058cea0(float *param_1,float *param_2)

{
  undefined4 uVar1;
  
  if (*param_2 < param_1[2]) {
    if (*param_1 < param_2[2]) {
      if (param_2[1] < param_1[3]) {
        if (param_1[1] < param_2[3]) {
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
  return uVar1;
}

