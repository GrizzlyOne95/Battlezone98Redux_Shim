
undefined4 FUN_00826100(uint param_1,uint *param_2,uint param_3)

{
  undefined4 uVar1;
  
  if ((param_3 == 0) || (param_1 < param_3)) {
    *param_2 = param_1 + *(int *)(param_1 + 4);
    if ((param_3 == 0) || (*param_2 < param_3)) {
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

