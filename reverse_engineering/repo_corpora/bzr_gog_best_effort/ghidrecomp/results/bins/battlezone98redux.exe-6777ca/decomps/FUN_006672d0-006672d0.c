
undefined4 __thiscall FUN_006672d0(uint *param_1,uint *param_2)

{
  undefined4 uVar1;
  
  if ((param_2[1] < param_1[1]) || ((param_2[1] <= param_1[1] && (*param_2 <= *param_1)))) {
    if ((param_1[1] < param_2[1]) || ((param_1[1] == param_2[1] && (*param_1 <= *param_2)))) {
      if ((param_2[3] < param_1[3]) || ((param_2[3] <= param_1[3] && (param_2[2] <= param_1[2])))) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}

