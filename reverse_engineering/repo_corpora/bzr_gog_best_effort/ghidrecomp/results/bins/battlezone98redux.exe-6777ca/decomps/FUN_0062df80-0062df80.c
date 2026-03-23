
undefined4 FUN_0062df80(int param_1)

{
  undefined4 local_8;
  
  if (param_1 == 0) {
    local_8 = 0;
  }
  else if ((((*(int *)(param_1 + 0x84) == 6) || (*(int *)(param_1 + 0x84) == 1)) ||
           (*(int *)(param_1 + 0x84) == 4)) || (*(int *)(param_1 + 0x84) == 3)) {
    local_8 = 1;
  }
  else {
    local_8 = 0;
  }
  return local_8;
}

