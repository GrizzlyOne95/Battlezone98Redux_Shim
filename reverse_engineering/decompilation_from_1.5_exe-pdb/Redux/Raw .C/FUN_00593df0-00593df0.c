
char * __thiscall FUN_00593df0(char *param_1,undefined4 *param_2)

{
  char cVar1;
  int local_1c;
  char *local_14;
  char *local_10;
  
  DAT_009181a8 = param_1;
  *(undefined4 **)(param_1 + 0x38) = param_2;
  DAT_02a13cbc = FUN_0046f0f0(param_2);
  local_14 = (char *)*param_2;
  local_10 = param_1;
  do {
    cVar1 = *local_14;
    *local_10 = cVar1;
    local_14 = local_14 + 1;
    local_10 = local_10 + 1;
  } while (cVar1 != '\0');
  if (DAT_02a13cbc == 0) {
    param_1[0x28] = '\0';
    param_1[0x29] = '\0';
    param_1[0x2a] = '\x01';
    param_1[0x2c] = '\0';
    param_1[0x2d] = '\0';
    param_1[0x2e] = '\0';
    param_1[0x2f] = '\0';
    param_1[0x30] = '\0';
    param_1[0x31] = '\0';
    param_1[0x32] = '\0';
    param_1[0x33] = '\0';
    param_1[0x34] = '\x01';
  }
  else {
    param_1[0x28] = '\x01';
    param_1[0x29] = *(char *)(DAT_02a13cbc + 8);
    param_1[0x2a] = *(char *)(DAT_02a13cbc + 9);
    *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(DAT_02a13cbc + 0xc);
    param_1[0x34] = *(int *)(DAT_02a13cbc + 0x10) < 100;
    if (param_1[0x34] == '\0') {
      local_1c = 100;
    }
    else {
      local_1c = 0;
    }
    *(int *)(param_1 + 0x30) = *(int *)(DAT_02a13cbc + 0x10) - local_1c;
  }
  param_1[0x35] = '\x01';
  return param_1;
}

