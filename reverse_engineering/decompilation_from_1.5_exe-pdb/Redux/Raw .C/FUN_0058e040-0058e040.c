
undefined4 FUN_0058e040(float *param_1,float *param_2)

{
  undefined4 uVar1;
  
  if (*param_1 == param_2[2]) {
    uVar1 = 0;
  }
  else if (param_1[1] == param_2[3]) {
    uVar1 = 1;
  }
  else if (param_1[2] == *param_2) {
    uVar1 = 2;
  }
  else {
    uVar1 = 3;
  }
  return uVar1;
}

