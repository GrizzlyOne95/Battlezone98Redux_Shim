
undefined4 FUN_00416e10(int *param_1)

{
  undefined4 uVar1;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_14 = 0;
  local_10 = 0;
  if (param_1 == (int *)0x0) {
    uVar1 = 0x800401f0;
  }
  else {
    local_8 = FUN_004394a0(param_1,0);
    if (local_8 < 0) {
      uVar1 = 0;
    }
    else {
      local_8 = (**(code **)(*param_1 + 0x2c))
                          (param_1,0,*(undefined4 *)(local_c + 8),&local_14,&local_10,0,0,0);
      if (local_8 < 0) {
        uVar1 = 0;
      }
      else {
        FUN_00416970(local_14,local_10,0);
        (**(code **)(*param_1 + 0x4c))(param_1,local_14,local_10,0,0);
        uVar1 = 0;
      }
    }
  }
  return uVar1;
}

