
undefined4 FUN_0043ad20(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_c;
  undefined4 local_8;
  
  local_c = 0;
  iVar1 = FUN_0043cfe0(param_1);
  if ((iVar1 == 0) && (iVar1 = FUN_0043b360(param_1), iVar1 == 0)) {
    local_c = 0;
  }
  else {
    if (*(int *)(param_1 + 0x3c) == 0) {
      local_8 = 0;
    }
    else {
      if (*(int *)(param_1 + 0x3c) == 2) {
        *(undefined1 *)(param_1 + 0x6c) = 1;
      }
      local_8 = 1;
    }
    *(float *)(param_1 + 0x1c) = (float)*(int *)(param_1 + 0x40);
    *(float *)(param_1 + 0x18) = (float)*(int *)(param_1 + 0x48);
    if (*(int *)(param_1 + 0x44) != 0) {
      iVar1 = rand();
      *(float *)(param_1 + 0x18) =
           *(float *)(param_1 + 0x18) * *(float *)(&DAT_008e7604 + (iVar1 % 10) * 4);
    }
    if ((*(int *)(param_1 + 0x24) == 0) ||
       (iVar1 = (**(code **)(param_1 + 0x24))(param_1,1), iVar1 != 0)) {
      *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) | 0x3c0;
      FUN_0043b720(param_1,param_2);
      FUN_0043d010(param_1,local_8);
      *(uint *)(param_1 + 0x70) = *(uint *)(param_1 + 0x70) | 4;
      local_c = 1;
    }
  }
  return local_c;
}

