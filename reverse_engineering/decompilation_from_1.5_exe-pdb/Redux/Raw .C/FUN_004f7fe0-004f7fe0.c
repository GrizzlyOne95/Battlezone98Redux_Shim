
void __thiscall FUN_004f7fe0(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  int local_18;
  int local_14;
  int local_c;
  
  FUN_00611610(param_2);
  if (((char)param_1[0x38] == '\0') || (cVar1 = FUN_00611840(), cVar1 == '\0')) {
    param_1[0x2a] = *(int *)(param_1[2] + 0x68);
    param_1[0x37] = 0;
    param_1[0x31] = 0;
    param_1[0x34] = 0;
  }
  else {
    iVar2 = (**(code **)(*param_1 + 0x34))(param_2);
    local_c = FUN_004da060(param_1[0x37]);
    local_14 = FUN_004da060(param_1[0x39]);
    if (local_c == 0) {
      param_1[0x37] = 0;
    }
    if (local_14 == 0) {
      param_1[0x39] = 0;
    }
    if ((iVar2 == local_c) || ((iVar2 == local_14 && (iVar2 != 0)))) {
      if (local_c != 0) {
        (**(code **)(*param_1 + 0x38))(local_c,param_2);
      }
    }
    else {
      if (iVar2 == 0) {
        local_18 = 0;
      }
      else {
        local_18 = FUN_00462380();
      }
      param_1[0x37] = local_18;
      param_1[0x31] = 0;
      param_1[0x34] = 0;
      local_c = iVar2;
    }
    while ((float)param_1[0x31] <= 0.0 && (float)param_1[0x31] != 0.0) {
      if (param_1[0x34] < 1) {
        param_1[0x31] = 0;
      }
      else {
        param_1[0x34] = param_1[0x34] + -1;
        param_1[0x31] = (int)((float)param_1[0x31] + (float)param_1[0x32]);
      }
    }
    while (((float)param_1[0x32] <= (float)param_1[0x31] &&
            (float)param_1[0x31] != (float)param_1[0x32] &&
           (param_1[0x34] < *(int *)(param_1[2] + 0xb8) + -1))) {
      param_1[0x34] = param_1[0x34] + 1;
      param_1[0x31] = (int)((float)param_1[0x31] - (float)param_1[0x32]);
      if (param_1[0x34] == *(int *)(param_1[2] + 0xb8) + -1) {
        local_14 = local_c;
        param_1[0x39] = param_1[0x37];
      }
    }
    if (local_c == 0) {
      if (local_14 == 0) {
        param_1[0x2a] = *(int *)(param_1[2] + 0x68);
      }
      else {
        param_1[0x2a] = *(int *)(*(int *)(param_1[2] + 0xbc) + -4 + *(int *)(param_1[2] + 0xb8) * 4)
        ;
      }
    }
    else {
      param_1[0x2a] = *(int *)(*(int *)(param_1[2] + 0xbc) + param_1[0x34] * 4);
    }
  }
  return;
}

