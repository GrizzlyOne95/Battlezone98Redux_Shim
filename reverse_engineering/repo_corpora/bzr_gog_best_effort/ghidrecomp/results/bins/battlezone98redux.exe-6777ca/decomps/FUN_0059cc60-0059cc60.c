
int FUN_0059cc60(undefined4 *param_1)

{
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_c = 0;
  local_10 = 0;
  local_14 = 1;
  while ((local_c == 0 && (local_10 < 8))) {
    local_c = FUN_0059cb80(&local_18,&local_1c);
    if (local_c == 0) {
      local_10 = local_10 + 1;
      *(int *)(local_8 + 0x154) = local_14 * local_10 + *(int *)(local_8 + 0x154);
      if (*(int *)(local_8 + 0x154) < 0) {
        *(int *)(local_8 + 0x154) = *(int *)(local_8 + 0x154) + 8;
      }
      else if (7 < *(int *)(local_8 + 0x154)) {
        *(int *)(local_8 + 0x154) = *(int *)(local_8 + 0x154) + -8;
      }
      local_14 = -local_14;
    }
  }
  if (local_c != 0) {
    *param_1 = local_18;
    param_1[1] = 0;
    param_1[2] = local_1c;
  }
  return local_c;
}

