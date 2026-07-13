
undefined4 FUN_0069d590(int *param_1,int param_2)

{
  undefined4 uVar1;
  int local_c;
  undefined4 *local_8;
  
  if ((param_2 < 0) || (param_1[2] <= param_2)) {
    uVar1 = 0;
  }
  else {
    if (param_2 == *param_1 + -1) {
      local_8 = *(undefined4 **)(param_1[1] + 8);
    }
    else if (param_2 == *param_1 + 1) {
      local_8 = *(undefined4 **)(param_1[1] + 4);
    }
    else {
      local_8 = (undefined4 *)param_1[3];
      for (local_c = 0; local_c < param_2; local_c = local_c + 1) {
        local_8 = (undefined4 *)local_8[1];
      }
    }
    *param_1 = param_2;
    param_1[1] = (int)local_8;
    uVar1 = *local_8;
  }
  return uVar1;
}

